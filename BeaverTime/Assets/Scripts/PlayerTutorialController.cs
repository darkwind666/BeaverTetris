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
            beaverTalk.text = talks.talks[activeTutorialIndex].talk[currentTutorialPartIndex];
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
        beaverTalk.text = talks.talks[tutorialIndex - 1].talk[currentTutorialPartIndex];
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
