using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;
using com.playGenesis.VkUnityPlugin;
using com.playGenesis.VkUnityPlugin.MiniJSON;
using System;

public class GameSocialsPopUpsController : MonoBehaviour, VKontakteInviteFriendsInterface {

    public GameGlobalSettings gameGlobalSettings;

    public int reviewLevel;
    public int reviewTimeInterval;
	public int joinGroupLevel;
	public int joinGroupTimeInterval;
	public int inviteFriendsLevel;
	public int inviteFriendsTimeInterval;

    public GameObject reviewPopUp;
    public GameSpeedController gameSpeedController;
    public GameAnaliticsController gameAnaliticsController;
    public string gameReviewPopUpAnaliticMessage;
	public string gameJoinGroupPopUpAnaliticMessage;
	public string gameInviteFriendsAnaliticMessage;

	public Text reviewPopUpText;
	public string gameReviewText;
	public string gameJoinGroupText;
	public string gameInviteFriendsText;

	public GameObject reviewButton;
	public GameObject joinBeaverTimeGroupButton;
	public GameObject inviteFriendsButton;

	public InviteFriendsController inviteFriendsController;
	public GameObject inviteFriendsPopUp;

	public GameObject acceptOperationController;
	public Button acceptButton;

    bool _showPopUpAvailable;
    int _currentTimeState;
	int _maxTimeToShowPopUp;
    GamePlayerDataController _playerData;

	VkApi _vkapi;
	Downloader _downloader;

	string inviteTextKey = "BeaverTime.InviteFriendText";

    void Start () {
		_vkapi = VkApi.VkApiInstance;
		_vkapi.LoggedIn += onVKLogin;
		_downloader = _vkapi.gameObject.GetComponent<Downloader> ();

		_showPopUpAvailable = false;
        _playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
		_currentTimeState = 0;

        if (_playerData.selectedLevelIndex == reviewLevel && _playerData.showReviewSuggestion == false)
        {
			_showPopUpAvailable = true;
			_maxTimeToShowPopUp = reviewTimeInterval;
        }

		if (_playerData.selectedLevelIndex == joinGroupLevel && _playerData.showJoinGroupSuggestion == false && _playerData.inVkGameGroup == false)
		{
			_showPopUpAvailable = true;
			_maxTimeToShowPopUp = joinGroupTimeInterval;
		}

		if (_playerData.selectedLevelIndex == inviteFriendsLevel && _playerData.showInviteFriendsSuggestion == false)
		{
			_showPopUpAvailable = true;
			_maxTimeToShowPopUp = inviteFriendsTimeInterval;
		}
    }
	
	void Update () {
		if (_showPopUpAvailable)
        {
            _currentTimeState++;
			if (_currentTimeState >= _maxTimeToShowPopUp && gameSpeedController.stopGame == false)
            {
				showSocialPopUp();
            }
        }
	}

	void showSocialPopUp()
	{
		if (_playerData.selectedLevelIndex == reviewLevel)
		{
			_playerData.showReviewSuggestion = true;
			reviewButton.SetActive(true);
			gameAnaliticsController.sendAnaliticMessage(gameReviewPopUpAnaliticMessage);
			reviewPopUpText.text = SmartLocalization.LanguageManager.Instance.GetTextValue(gameReviewText);
		}

		if (_playerData.selectedLevelIndex == joinGroupLevel)
		{
			_playerData.showJoinGroupSuggestion = true;
			joinBeaverTimeGroupButton.SetActive(true);
			gameAnaliticsController.sendAnaliticMessage(gameJoinGroupPopUpAnaliticMessage);
			reviewPopUpText.text = SmartLocalization.LanguageManager.Instance.GetTextValue(gameJoinGroupText);
		}

		if (_playerData.selectedLevelIndex == inviteFriendsLevel)
		{
			_playerData.showInviteFriendsSuggestion = true;
			inviteFriendsButton.SetActive(true);
			gameAnaliticsController.sendAnaliticMessage(gameInviteFriendsAnaliticMessage);
			reviewPopUpText.text = SmartLocalization.LanguageManager.Instance.GetTextValue(gameInviteFriendsText);
		}

		reviewPopUp.SetActive(true);
		_showPopUpAvailable = false;
		gameSpeedController.stopGame = true;
	}

	void OnDisable()
	{
		_vkapi.LoggedIn -= onVKLogin;
	}

//    public void goToGameReview()
//    {
//        Application.OpenURL(gameGlobalSettings.gameShopForReviewUrl);
//    }

    public void backToGame()
    {
        reviewPopUp.SetActive(false);
        gameSpeedController.stopGame = false;
    }
		
	void onVKLogin()
	{
		_playerData.playerScore += gameGlobalSettings.logInReward;
		_playerData.logInVk = true;
		_playerData.savePlayerData ();
		getPlayerRewardForGroup ();
		setUpCurrentUserFriends();
	}

	void getPlayerRewardForGroup()
	{
		VKRequest r1 = new VKRequest (){
			url="groups.isMember?group_id=" + gameGlobalSettings.vkGameGroupId,
			CallBackFunction=onPlayerRewardForGroup
		};
		_vkapi.Call (r1);
	}

	void onPlayerRewardForGroup(VKRequest request)
	{
		var dict = Json.Deserialize(request.response) as Dictionary<string,object>;
		bool inGroup = Convert.ToBoolean(dict ["response"]);

		if (inGroup) {
			_playerData.playerScore += gameGlobalSettings.joinGroupReward;
			_playerData.inVkGameGroup = true;
			_playerData.savePlayerData();
			joinBeaverTimeGroupButton.SetActive(false);
		}
	}

	void setUpCurrentUserFriends()
	{
		VKRequest r1 = new VKRequest (){
			url="apps.getFriendsList?extended=1&count=30&type=invite&fields=photo_50",
			CallBackFunction=getFriendsHandler
		};
		_vkapi.Call (r1);
	}

	void getFriendsHandler(VKRequest request)
	{
		if(request.error!=null)
		{
			return;
		}

		var dict = Json.Deserialize(request.response) as Dictionary<string,object>;
		var resp = (Dictionary<string,object>)dict["response"];
		var items = (List<object>)resp["items"];

		List<BeaverTimeVKFriend> friends = new List<BeaverTimeVKFriend>();

		foreach(var item in items)
		{
			BeaverTimeVKFriend friend = new BeaverTimeVKFriend();
			friend.friend = VKUser.Deserialize(item);
			friends.Add(friend);
		}

		inviteFriendsController.friendsDataSource = friends;

		if(inviteFriendsController.m_tableView.isActiveAndEnabled == true)
		{
			inviteFriendsController.m_tableView.ReloadData();
		}
	}

	public void joinBeaverTimeGroup()
	{
		if (_vkapi.IsUserLoggedIn) {
			VKRequest r1 = new VKRequest () {
				url = "groups.join?group_id=" + gameGlobalSettings.vkGameGroupId,
				CallBackFunction = joinBeaverTimeGroupHandler
			};

			acceptOperationController.SetActive(true);
			acceptButton.onClick.AddListener(() => { 
				_vkapi.Call (r1);
			});

		} else {
			_vkapi.Login();
		}
	}

	void joinBeaverTimeGroupHandler(VKRequest r)
	{
		if(r.error!=null)
		{
			return;
		}
		getPlayerRewardForGroup();
	}

	public void inviteFriends()
	{
		if (_vkapi.IsUserLoggedIn) {
			setUpCurrentUserFriends();
			inviteFriendsPopUp.SetActive(true);
		} else {
			_vkapi.Login();
		}
	}

	public void loadImageWithUrlAndCallback (string aUrl, Action<DownloadRequest> aCallback)
	{
		var request = new DownloadRequest
		{
			url = aUrl,
			onFinished = aCallback,
		};

		_downloader.download(request);
	}

	public void inviteFriend(string friendId, string friendName, Action aCallback)
	{
		string inviteTextTemplate = SmartLocalization.LanguageManager.Instance.GetTextValue(inviteTextKey);
		string inviteText = string.Format(inviteTextTemplate, friendName);

		VKRequest r1 = new VKRequest (){
			url="apps.sendRequest?user_id="+friendId+"&text=" + inviteText + "&type=invite&name=BeaverTime",
			CallBackFunction=inviteFriendHandler,
			data = new Action[] {aCallback},
		};

		_vkapi.Call (r1);
	}

	void inviteFriendHandler(VKRequest request)
	{
		if(request.error!=null)
		{
			return;
		}

		_playerData.playerScore += gameGlobalSettings.inviteFriendReward;
		_playerData.savePlayerData();
		Action callback = request.data[0] as Action;
		callback();
	}
}
