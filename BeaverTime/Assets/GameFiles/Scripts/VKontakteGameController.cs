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

	VkApi _vkapi;
	VKUser _currentUser;
	string testFriendId = "122457260";


	void Start () {
	
		_vkapi=VkApi.VkApiInstance;
		_vkapi.LoggedIn += onVKLogin;
		_vkapi.LoggedOut += onLogout;

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
		};

		var request = new DownloadRequest
		{
			url = _currentUser.photo_50,
			onFinished = doOnFinish,
		};

		downloader.download(request);
	}

}
