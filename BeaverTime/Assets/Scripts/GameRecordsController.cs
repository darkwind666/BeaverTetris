using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class GameRecordsController : MonoBehaviour {

    public FadingScript fadingController;
    public Text[] playersRecords;
	public Text playerName;
	public Text playerTime;

    void Start ()
    {
        cleanRecordsPads();
        fillRecordsPads();
		setUpPlayerStatePad();
    }

    void cleanRecordsPads()
    {
        foreach (Text item in playersRecords)
        {
            item.text = "";
        }
    }

    void fillRecordsPads()
    {
        PlayersDatabaseController playersRecordsController = ServicesLocator.getServiceForKey(typeof(PlayersDatabaseController).Name) as PlayersDatabaseController;
        int savedRecords = playersRecordsController.getRecordsCount();
        int firstRecordsCount = Mathf.Min(playersRecords.Length, savedRecords);

        for (int recordIndex = 0; recordIndex < firstRecordsCount; recordIndex++)
        {
            Text recordLable = playersRecords[recordIndex];
            PlayerRecordData record = playersRecordsController.getRecordForIndex(recordIndex);
			string playerTime = EndlessLevelIndicatorController.endlessLevelTimeFromInt(record.playerScore);
			recordLable.text = string.Format("{0} {1}", record.playerName, playerTime);
        }

    }

	void setUpPlayerStatePad()
	{
		GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

		if (playerData.playerExist) {
			playerName.text = playerData.playerName;
			playerTime.text = EndlessLevelIndicatorController.endlessLevelTimeFromInt (playerData.endlessLevelPlayedTime);
		} 
		else {
			playerName.text = "";
			playerTime.text = "";
		}
	}

    void Update () {
	
	}

    public void goToMainMenuScreen()
    {
        fadingController.startFade("MainMenuScreen", false);
    }

}
