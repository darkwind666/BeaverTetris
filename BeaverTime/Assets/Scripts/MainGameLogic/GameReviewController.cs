using UnityEngine;
using System.Collections;

public class GameReviewController : MonoBehaviour {

    public string reviewStoreUrl;
    public int reviewLevel;
    public int reviewTimeInterval;
    public GameObject reviewPopUp;
    public GameSpeedController gameSpeedController;
    public GameAnaliticsController gameAnaliticsController;
    public string gameReviewPopUpAnaliticMessage;

    bool _reviewAvailable;
    int _currentTimeState;
    GamePlayerDataController _playerData;

    

    void Start () {

        _reviewAvailable = false;
        _playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

        if (_playerData.selectedLevelIndex == reviewLevel && _playerData.showReviewSuggestion == false)
        {
            _reviewAvailable = true;
            _currentTimeState = 0;
        }

    }
	
	void Update () {

        if (_reviewAvailable)
        {
            _currentTimeState++;

            if (_currentTimeState >= reviewTimeInterval && gameSpeedController.stopGame == false)
            {
                reviewPopUp.SetActive(true);
                _playerData.showReviewSuggestion = true;
                _reviewAvailable = false;
                gameSpeedController.stopGame = true;
                gameAnaliticsController.sendAnaliticMessage(gameReviewPopUpAnaliticMessage);
            }

        }

	}

    public void goToGameReview()
    {
        Application.OpenURL(reviewStoreUrl);
    }

    public void backToGame()
    {
        reviewPopUp.SetActive(false);
        gameSpeedController.stopGame = false;
    }
}
