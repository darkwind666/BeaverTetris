using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using GooglePlayGames;
using UnityEngine.SocialPlatforms;
using System;

public class GlobalLeaderboardController : MonoBehaviour {

	public GameGlobalSettings gameSettings;
	public GameObject gameSparkLeaderboard;
	public Text[] playersRecords;
	public Text playerRank;
	public string googlePlayLeaderboardId;
	public bool startGame;

	GamePlayerDataController _playerData;

	void Start () {

		if(gameSettings.googlePlayServiceLeaderboard)
		{
			#if UNITY_ANDROID

			GooglePlayGames.PlayGamesPlatform.Activate();

			#endif
		}
			
		_playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

		if(startGame)
		{
			logInPlayer();
		}
	}

	void Update () {
	
	}

	void logInPlayer()
	{
		if (gameSettings.googlePlayServiceLeaderboard == true || gameSettings.gameCenterLeaderboard == true) 
		{
			Social.localUser.Authenticate (logInDebug);
		} 
		else 
		{
			new GameSparks.Api.Requests.DeviceAuthenticationRequest().Send((response) => {
				
				if (!response.HasErrors) {
					
					if(_playerData.playerExist)
					{
						setPlayerName();
					}

				} 

			});
		}
	}

	void logInDebug(bool success)
	{
		Debug.Log("success: " + success);
	}

	public void sendPlayerRecord()
	{
		if (gameSettings.googlePlayServiceLeaderboard == true || gameSettings.gameCenterLeaderboard == true) 
		{
			Social.ReportScore(_playerData.endlessLevelPlayedTime, googlePlayLeaderboardId, onReportScore);
		} 
		else 
		{
			string playerRecord = _playerData.endlessLevelPlayedTime.ToString ();
			new GameSparks.Api.Requests.LogEventRequest().SetEventKey("postScore").SetEventAttribute("score", playerRecord).Send((response) => {
			});
		}
	}

	private void onReportScore(bool result)
	{
		Debug.Log("success: " + result);
	}

	public void showGlobalLeaderboard()
	{
		if (gameSettings.googlePlayServiceLeaderboard == true || gameSettings.gameCenterLeaderboard == true) 
		{
			#if UNITY_ANDROID
			(Social.Active as GooglePlayGames.PlayGamesPlatform).SetDefaultLeaderboardForUI("LEADERBOARD_ID");
			#endif

			Social.ShowLeaderboardUI();
		} 
		else 
		{
			foreach (Text item in playersRecords)
			{
				item.text = "";
			}
			
			gameSparkLeaderboard.SetActive(true);
			new GameSparks.Api.Requests.LeaderboardDataRequest().SetLeaderboardShortCode("hightScoreLeaderboard").SetEntryCount(playersRecords.Length).Send((response) => {
				if (!response.HasErrors) {
					foreach(GameSparks.Api.Responses.LeaderboardDataResponse._LeaderboardData entry in response.Data) {
						int rank = (int) entry.Rank;
						string playerName = entry.UserName;
						string score = entry.JSONData["score"].ToString();
						string playerTime = EndlessLevelIndicatorController.endlessLevelTimeFromInt(Int32.Parse(score));
						playersRecords[rank - 1].text = string.Format(rank + ") " + playerName + "   " + playerTime);
					}
				}
			});
		}
	}

	public void showPlayerRank()
	{
		

		if (gameSettings.gameSparkLeaderboard == true) 
		{
			List <string> leaderBoards = new List <string>();
			leaderBoards.Add("hightScoreLeaderboard");
			new GameSparks.Api.Requests.GetLeaderboardEntriesRequest().SetLeaderboards(leaderBoards).Send((response) => {
				if (!response.HasErrors) {
					Debug.Log("Found Leaderboard Data...");
					int playerScore = (int)response.BaseData.GetGSData("hightScoreLeaderboard").GetNumber("rank");
					playerRank.text = playerScore.ToString();
				} else {
					Debug.Log("Error Retrieving Leaderboard Data...");
				}
			});
		} 
	}

	private void onLeaderboardLoadComplete(bool success)
	{
		Debug.Log("onLeaderboardLoadComplete: " + success);
	}

	public void setPlayerName()
	{
		if (gameSettings.gameSparkLeaderboard == true) 
		{
			new GameSparks.Api.Requests.ChangeUserDetailsRequest().SetDisplayName(_playerData.playerName).Send((response) => {
			});
		} 
	}

}
