using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using com.playGenesis.VkUnityPlugin;
using com.playGenesis.VkUnityPlugin.MiniJSON;
using System.Collections.Generic;


public class VKontakteGameController : MonoBehaviour {

	public Text playerName;
	public Image playerImage;
	public GameObject logInButton;
	public GameObject logOutButton;
	string group_id = "101174315";

	VkApi _vkapi;
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
			url="users.get?&photo_50",
			CallBackFunction=OnGetUserInfo
		};
		_vkapi.Call (r);
	}

	void onLogout()
	{
		logOutButton.SetActive (false);
		logInButton.SetActive (true);
	}

	public void OnGetUserInfo (VKRequest r)
	{
		if(r.error!=null)
		{
			return;
		}
			
		var dict=Json.Deserialize(r.response) as Dictionary<string,object>;
		var users=(List<object>)dict["response"];
		var user = VKUser.Deserialize (users [0]);

		playerName.text = user.first_name + " " + user.last_name;

	}
}
