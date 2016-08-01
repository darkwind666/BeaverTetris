using UnityEngine;
using System.Collections;
using com.playGenesis.VkUnityPlugin;

public class SocialShare : MonoBehaviour
{
    public string loseLevelImage;
    public string winLevelImage;
    public string winAllGameImage;

    public string vkPublicURL;
    public string facebookPageURL;
    public string twitterURL;
    public string gameVideoUrl;

    public string vkProgrammerProfileURL;
    public string facebookProgrammerProfileURL;
    public string twitterProgrammerProfileURL;

    string vkTemplate = "http://vk.com/share.php?title={0}&description={1}&image={2}&url={3}";
    string facebookTemplate = "https://www.facebook.com/sharer/sharer.php?u={3}";
    string twitterTemplate = "https://twitter.com/intent/tweet?text={0} {1}&url={3}";

    string titleKey = "BeaverTime.ShareTitle";
    string loseLevelKey = "BeaverTime.ShareLoseDescription";
    string winLevelKey = "BeaverTime.ShareWinDescription";
    string winAllGameKey = "BeaverTime.ShareWinAllGame";
	string endlessLevelResultKey = "BeaverTime.EndlessLevelResult";

    private enum LevelResult
    {
        Win,
        Lose,
        WinAllGame,
		EndEndlessLevel
    }

    string EscapeURL(string url)
    {
        return WWW.EscapeURL(url).Replace("+", "%20");
    }

    public void goToVkPublic()
    {
        Application.OpenURL(vkPublicURL);
    }

    public void goToFacebookPage()
    {
        Application.OpenURL(facebookPageURL);
    }

    public void goToTwitter()
    {
        Application.OpenURL(twitterURL);
    }

    public void goToProgrammerVkProfile()
    {
        Application.OpenURL(vkProgrammerProfileURL);
    }

    public void goToProgrammerFacebookProfile()
    {
        Application.OpenURL(facebookProgrammerProfileURL);
    }

    public void goToProgrammerTwitter()
    {
        Application.OpenURL(twitterProgrammerProfileURL);
    }

    public void loseLevelVK()
    {
        string url = getUrlWithTemplateAndWinResultAndPageUrl(vkTemplate, LevelResult.Lose, vkPublicURL);
        Publish(url);
    }

    public void loseLevelFacebook()
    {
        string url = getUrlWithTemplateAndWinResultAndPageUrl(facebookTemplate, LevelResult.Lose, facebookPageURL);
        Publish(url);
    }

    public void loseLevelTwitter()
    {
        string url = getUrlWithTemplateAndWinResultAndPageUrl(twitterTemplate, LevelResult.Lose, gameVideoUrl);
        Publish(url);
    }

    public void winLevelVK()
    {
        string url = getUrlWithTemplateAndWinResultAndPageUrl(vkTemplate, LevelResult.Win, vkPublicURL);
        Publish(url);
    }

    public void winLevelFacebook()
    {
        string url = getUrlWithTemplateAndWinResultAndPageUrl(facebookTemplate, LevelResult.Win, facebookPageURL);
        Publish(url);
    }

    public void winLevelTwitter()
    {
        string url = getUrlWithTemplateAndWinResultAndPageUrl(twitterTemplate, LevelResult.Win, gameVideoUrl);
        Publish(url);
    }

    public void winAllGameVK()
    {
        string url = getUrlWithTemplateAndWinResultAndPageUrl(vkTemplate, LevelResult.WinAllGame, vkPublicURL);
        Publish(url);
    }

    public void winAllGameFacebook()
    {
        string url = getUrlWithTemplateAndWinResultAndPageUrl(facebookTemplate, LevelResult.WinAllGame, facebookPageURL);
        Publish(url);
    }

    public void winAllGameTwitter()
    {
        string url = getUrlWithTemplateAndWinResultAndPageUrl(twitterTemplate, LevelResult.WinAllGame, gameVideoUrl);
        Publish(url);
    }

	public void winEndlessLevelVK()
	{
		VkApi vkapi = VkApi.VkApiInstance;
		if (vkapi.IsUserLoggedIn) {
			string url = getUrlWithTemplateAndWinResultAndPageUrl(vkTemplate, LevelResult.EndEndlessLevel, vkPublicURL);
			Publish(url);
		} else {
			vkapi.Login();
		}
	}

	public void winEndlessLevelFacebook()
	{
		string url = getUrlWithTemplateAndWinResultAndPageUrl(facebookTemplate, LevelResult.EndEndlessLevel, facebookPageURL);
		Publish(url);
	}

	public void winEndlessLevelTwitter()
	{
		string url = getUrlWithTemplateAndWinResultAndPageUrl(twitterTemplate, LevelResult.EndEndlessLevel, gameVideoUrl);
		Publish(url);
	}

    string getUrlWithTemplateAndWinResultAndPageUrl(string aTemplate, LevelResult aLevelResult, string aPage)
    {
        string levelResultDescription = "";
        string levelResultImage = "";

        switch (aLevelResult)
        {
            case LevelResult.Win:
                levelResultDescription = getLevelResultDescriptionWithKey(winLevelKey);
                levelResultImage = winLevelImage;
                break;
            case LevelResult.Lose:
                levelResultDescription = getLevelResultDescriptionWithKey(loseLevelKey);
                levelResultImage = loseLevelImage;
                break;
            case LevelResult.WinAllGame:
                levelResultDescription = SmartLocalization.LanguageManager.Instance.GetTextValue(winAllGameKey);
                levelResultImage = winAllGameImage;
                break;
			case LevelResult.EndEndlessLevel:
				levelResultDescription = getEndlessLevelDescription();
				levelResultImage = winAllGameImage;
				break;
            default:
                break;
        }

        string localizedTitle = SmartLocalization.LanguageManager.Instance.GetTextValue(titleKey);
        string url = string.Format(aTemplate, EscapeURL(localizedTitle), EscapeURL(levelResultDescription), EscapeURL(levelResultImage), EscapeURL(aPage));
        return url;
    }

    string getLevelResultDescriptionWithKey(string aKey)
    {
        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        int currentLevel = playerData.selectedLevelIndex + 1;
        int playeScore = playerData.playerScore;
        string localizedDescription = SmartLocalization.LanguageManager.Instance.GetTextValue(aKey);
        string levelResultDescription = string.Format(localizedDescription, currentLevel, playeScore);
        return levelResultDescription;
    }

	string getEndlessLevelDescription()
	{
		GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
		string playerScoreTime = EndlessLevelIndicatorController.endlessLevelTimeFromInt(playerData.endlessLevelPlayedTime);
		string localizedDescription = SmartLocalization.LanguageManager.Instance.GetTextValue(endlessLevelResultKey);
		string levelResultDescription = string.Format(localizedDescription, playerScoreTime);
		return levelResultDescription;
	}

    void Publish(string url)
    {
        Application.OpenURL(url);
    }
}