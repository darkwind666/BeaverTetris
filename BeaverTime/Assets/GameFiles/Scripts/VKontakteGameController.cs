using UnityEngine;
using UnityEngine.UI;
using com.playGenesis.VkUnityPlugin;
using com.playGenesis.VkUnityPlugin.MiniJSON;
using System.Collections.Generic;
using System;
using System.Collections;


public class VKontakteGameController : MonoBehaviour {

	public Text playerName;
	public Image playerImage;
	public GameObject logInButton;
	public GameObject logOutButton;
	public Downloader downloader;
	public InviteFriendsController inviteFriendsController;

	VkApi _vkapi;
	VKUser _currentUser;
	string testFriendId = "122457260";


	void Start () {
	
		_vkapi=VkApi.VkApiInstance;
		_vkapi.LoggedIn += onVKLogin;
		_vkapi.LoggedOut += onLogout;

		playerImage.enabled = false;

		if (_vkapi.IsUserLoggedIn) {
			logInButton.SetActive (false);
			logOutButton.SetActive (true);
			getUserInfo ();
		} 
		else 
		{
			logInButton.SetActive (true);
			logOutButton.SetActive (false);
		}
	}

	void Update () {
	
	}

	void OnDisable()
	{
		_vkapi.LoggedIn -= onVKLogin;
		_vkapi.LoggedOut -= onLogout;
	}

	public void joinGroup(string aGroup)
	{
		VKRequest r1 = new VKRequest (){
			url="groups.join?group_id="+aGroup,
			CallBackFunction=joinGroupHandler
		};
		_vkapi.Call (r1);
	}

	public void inviteFriend()
	{
		VKRequest r1 = new VKRequest (){
			url="apps.sendRequest?user_id="+testFriendId+"&text=Новая викторина Вконтакте бросает тебе вызов! Установи игру прямо сейчас!&type=request&name=test1",
			CallBackFunction=inviteFriendHandler
		};
		_vkapi.Call (r1);
	}

	public void logIn()
	{
		_vkapi.Login ();
	}

	public void logOut()
	{
		_vkapi.Logout ();
	}

	public void joinGroupHandler(VKRequest r)
	{
		if(r.error!=null)
		{
			Debug.Log(r.error.error_msg);
			return;
		}
	}

	void inviteFriendHandler(VKRequest r)
	{
		
	}

	void onVKLogin()
	{
		logInButton.SetActive (false);
		logOutButton.SetActive (true);
		getUserInfo();
	}

	void getUserInfo()
	{
		VKRequest r = new VKRequest
		{
			url="users.get?&fields=photo_50",
			CallBackFunction=OnGetUserInfo
		};
		_vkapi.Call (r);
	}

	void onLogout()
	{
		logOutButton.SetActive (false);
		logInButton.SetActive (true);
		playerName.text = "";
		DestroyObject(playerImage.sprite);
		playerImage.sprite = null;
		playerImage.enabled = false;

		inviteFriendsController.friendsDataSource = new List<VKUser>();

//		if(inviteFriendsController.m_tableView.isActiveAndEnabled == true)
//		{
//			inviteFriendsController.m_tableView.ReloadData();
//		}
	}

	public void OnGetUserInfo (VKRequest request)
	{
		if(request.error!=null)
		{
			return;
		}

		setUpCurrentUser(request);
		playerName.text = _currentUser.first_name + " " + _currentUser.last_name;
		setUpCurrentUserImage();
		setUpCurrentUserFriends();
	}

	void setUpCurrentUser(VKRequest request)
	{
		var dict=Json.Deserialize(request.response) as Dictionary<string,object>;
		var users=(List<object>)dict["response"];
		var user = VKUser.Deserialize (users [0]);
		_currentUser = user;
	}

	void setUpCurrentUserImage()
	{
		Action<DownloadRequest> doOnFinish =(downloadRequest)=>
		{
			Texture2D tex=downloadRequest.DownloadResult.texture;

			if (playerImage.sprite != null)
			{
				DestroyObject(playerImage.sprite);
			}

			playerImage.sprite=Sprite.Create(tex,new Rect(0,0,50,50),new Vector2(0.5f,0.5f));
			playerImage.enabled = true;
		};

		loadImageWithUrlAndCallback (_currentUser.photo_50, doOnFinish);
	}

	public void loadImageWithUrlAndCallback (string aUrl, Action<DownloadRequest> aCallback)
	{
		var request = new DownloadRequest
		{
			url = aUrl,
			onFinished = aCallback,
		};

		downloader.download(request);
	}

	void setUpCurrentUserFriends()
	{
		VKRequest r1 = new VKRequest (){
			url="apps.getFriendsList?extended=1&count=30&fields=photo_50",
			CallBackFunction=getFriendsHandler
		};
		_vkapi.Call (r1);
	}

	public void getFriendsHandler(VKRequest request)
	{
		if(request.error!=null)
		{
			return;
		}

		var dict = Json.Deserialize(request.response) as Dictionary<string,object>;
		var resp = (Dictionary<string,object>)dict["response"];
		var items = (List<object>)resp["items"];

		List<VKUser> friends = new List<VKUser>();

		foreach(var item in items)
		{
			friends.Add(VKUser.Deserialize(item));
		}

		inviteFriendsController.friendsDataSource = friends;

		if(inviteFriendsController.m_tableView.isActiveAndEnabled == true)
		{
			inviteFriendsController.m_tableView.ReloadData();
		}
	}

}
