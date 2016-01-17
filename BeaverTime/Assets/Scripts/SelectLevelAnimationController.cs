using UnityEngine;
using System.Collections;

public class SelectLevelAnimationController : MonoBehaviour {

    public GameObject[] levels;

    void Start () {
        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        int comletedLevelsCount = playerData.completedLevelsCount;
        showCompletedLevelsIconsCount(comletedLevelsCount);
        setUpAvailableLevelIcon(comletedLevelsCount);
        playStartAnimation();
    }

    void showCompletedLevelsIconsCount(int aComletedLevelsCount)
    {
        if (aComletedLevelsCount > 0)
        {
            for (int levelIndex = 0; levelIndex <= aComletedLevelsCount; levelIndex++)
            {
                levels[levelIndex].SetActive(true);
            }
        }
    }

    void setUpAvailableLevelIcon(int aAvailableLevelIndex)
    {
        GameObject availableLevel = levels[aAvailableLevelIndex];
        availableLevel.transform.localScale = new Vector3(0, 0, 0);
    }

    public void playStartAnimation()
    {
        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        if (playerData.playerExist)
        {
            Animator sceneAnimator = GetComponent<Animator>();
            sceneAnimator.enabled = true;
        }
    }


    void Update () {
        
	}

    public void animateAvailableLevel()
    {
        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        int comletedLevelsCount = playerData.completedLevelsCount;

        GameObject availableLevel = levels[comletedLevelsCount];
        Animator animatorComponent = availableLevel.GetComponent<Animator>();
        animatorComponent.enabled = true;
    }
    
}
