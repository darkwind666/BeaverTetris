using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class SelectLevelBeaverTalk : MonoBehaviour {

	void Start () {

        int talkIndex = getTalkIndex();
        string localizedKey = string.Format("BeaverTime.Level{0}", talkIndex);

        Text beaverTalk = GetComponent<Text>();
        beaverTalk.text = SmartLocalization.LanguageManager.Instance.GetTextValue(localizedKey);

    }

    int getTalkIndex()
    {
        int talkIndex = 1;
        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        int completedLevelsCount = playerData.completedLevelsCount;

        if (completedLevelsCount > 0)
        {
            talkIndex = playerData.completedLevelsCount + 1;
        }

        return talkIndex;
    }

    void Update () {
	
	}
}
