using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;
using com.playGenesis.VkUnityPlugin;
using com.playGenesis.VkUnityPlugin.MiniJSON;
using System;

public class GameSocialsPopUpsController : MonoBehaviour {

    public GameGlobalSettings gameGlobalSettings;

    public int reviewLevel;
    public int reviewTimeInterval;
	public int joinGroupLevel;
	public int joinGroupTimeInterval;

    public GameObject reviewPopUp;
    public GameSpeedController gameSpeedController;
    public GameAnaliticsController gameAnaliticsController;
    public string gameReviewPopUpAnaliticMessage;
	public string gameJoinGroupPopUpAnaliticMessage;

	public Text reviewPopUpText;
	public string gameReviewText;
	public string gameJoinGroupText;

	public GameObject reviewButton;
	public GameObject joinBeaverTimeGroupButton;
	public GameObject inviteFriendsButton;

	public GameObject acceptOperationController;
	public Button acceptButton;

    bool _showPopUpAvailable;
    int _currentTimeState;
	int _maxTimeToShowPopUp;
    GamePlayerDataController _playerData;

	VkApi _vkapi;

    void Start () {
		_vkapi = VkApi.VkApiInstance;
		_vkapi.LoggedIn += onVKLogin;

		_showPopUpAvailable = false;
        _playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
		_currentTimeState = 0;

        if (_playerData.selectedLevelIndex == reviewLevel && _playerData.showReviewSuggestion == false)
        {
			_showPopUpAvailable = true;
			_maxTimeToShowPopUp = reviewTimeInterval;
        }

		// && _playerData.inVkGameGroup == false

		if (_playerData.selectedLevelIndex == joinGroupLevel && _playerData.showJoinGroupSuggestion == false)
		{
			_showPopUpAvailable = true;
			_maxTimeToShowPopUp = joinGroupTimeInterval;
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

		reviewPopUp.SetActive(true);
		_showPopUpAvailable = false;
		gameSpeedController.stopGame = true;
	}

	void OnDisable()
	{
		_vkapi.LoggedIn -= onVKLogin;
	}

    public void goToGameReview()
    {
        Application.OpenURL(gameGlobalSettings.gameShopForReviewUrl);
    }

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
}
