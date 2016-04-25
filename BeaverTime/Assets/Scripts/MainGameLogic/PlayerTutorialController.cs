using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class PlayerTutorialController : MonoBehaviour {

    public GameObject[] tutorials;
    public GameObject tutorialsBeaver;
    public Text beaverTalk;
    public BeaverTutorialTalks talks;
    public GameSpeedController gameSpeedController;
    public WinBossCondition winBossCondition;

    GamePlayerDataController _playerData;
    GameObject _activeTutorial;
    int currentTutorialPartIndex;

    void Start () {

        _playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        int tutorialIndex = getTutorialIndex();

        if (tutorialIndex > 0 && tutorialIndex >_playerData.completedTutorialsCount)
        {
            int activeTutorialIndex = tutorialIndex - 1;
            _activeTutorial = tutorials[activeTutorialIndex];
            _activeTutorial.SetActive(true);
            gameSpeedController.stopGame = true;
            tutorialsBeaver.SetActive(true);
            currentTutorialPartIndex = 0;

            string tutorialKey = string.Format("BeaverTime.Tutorial{0}{1}", (activeTutorialIndex + 1), (currentTutorialPartIndex + 1));
            string beaverText = SmartLocalization.LanguageManager.Instance.GetTextValue(tutorialKey);
            beaverTalk.text = beaverText;

        }
        else
        {
            checkBossLevel();
        }

    }

    void checkBossLevel()
    {
        LevelDataStore levelDataStore = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        GameLevel levelData = levelDataStore.getCurrentLevelData();
        if (levelData.winConditionType == 3)
        {
            winBossCondition.loadGameBoss();
        }
    }

    int getTutorialIndex()
    {
        LevelDataStore levelDataStore = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        GameLevel levelData = levelDataStore.getCurrentLevelData();
        int tutorialIndex = levelData.tutorialIndex;
        return tutorialIndex;
    }

    void Update () {
	
	}

    public void nextTutorial()
    {
        currentTutorialPartIndex++;
        int tutorialIndex = getTutorialIndex();

        string tutorialKey = string.Format("BeaverTime.Tutorial{0}{1}", tutorialIndex, (currentTutorialPartIndex + 1));
        string beaverText = SmartLocalization.LanguageManager.Instance.GetTextValue(tutorialKey);
        beaverTalk.text = beaverText;

    }

    public void endTutorial()
    {
        _playerData.completedTutorialsCount = _playerData.completedTutorialsCount + 1;
        _playerData.savePlayerData();
        gameSpeedController.stopGame = false;
        _activeTutorial.SetActive(false);

        Animator animator = tutorialsBeaver.GetComponent<Animator>();
        animator.SetTrigger("BackBeaver");
        checkBossLevel();
    }

}
