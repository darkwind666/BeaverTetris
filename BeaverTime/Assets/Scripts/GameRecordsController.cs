using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class GameRecordsController : MonoBehaviour {

    public FadingScript fadingController;
    public Text[] playersRecords;


    void Start ()
    {
        cleanRecordsPads();
        fillRecordsPads();
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
            recordLable.text = string.Format("{0} {1}", record.playerName, record.playerScore);
        }

    }

    void Update () {
	
	}

    public void goToMainMenuScreen()
    {
        fadingController.startFade("MainMenuScreen", false);
    }

}
