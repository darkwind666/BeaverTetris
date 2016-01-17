using UnityEngine;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;



public class GamePlayerDataController {

    const string playerDataFileName = "/playerData.bt";

    public bool playerExist { get; set; }
    public float gameMusicVolume { get; set; }
    public float gameSoundEffectsVolume { get; set; }
    public string playerName { get; set; }

    public int completedLevelsCount { get; set; }
    public int playerScore { get; set; }

    string _dataPath;

    public GamePlayerDataController()
    {
        _dataPath = Application.persistentDataPath + playerDataFileName;
        loadPlayerData();
    }

    void loadPlayerData()
    {

        if(File.Exists(_dataPath))
        {
            BinaryFormatter formatter = new BinaryFormatter();
            FileStream file = File.Open(_dataPath, FileMode.Open);
            PlayerData data = formatter.Deserialize(file) as PlayerData;

            playerExist = data.playerExist;
            gameMusicVolume = data.gameMusicVolume;
            gameSoundEffectsVolume = data.gameSoundEffectsVolume;
            playerName = data.playerName;
            completedLevelsCount = data.completedLevelsCount;
            playerScore = data.playerScore;

            file.Close();
        }

    }

    public void savePlayerData()
    {
        BinaryFormatter formatter = new BinaryFormatter();
        FileStream file = File.Create(_dataPath);
        PlayerData savingData = new PlayerData();

        savingData.playerExist = playerExist;
        savingData.gameMusicVolume = gameMusicVolume;
        savingData.gameSoundEffectsVolume = gameSoundEffectsVolume;
        savingData.playerName = playerName;
        savingData.completedLevelsCount = completedLevelsCount;
        savingData.playerScore = playerScore;

        formatter.Serialize(file, savingData);
        file.Close();
    }

    public void createNewPlayerWithName(string aPlayerName)
    {
        playerExist = true;
        playerName = aPlayerName;
        completedLevelsCount = 0;
        playerScore = 0;
        savePlayerData();
    }

    public void cleanPlayer()
    {
        playerExist = false;
        playerName = "";
        completedLevelsCount = 0;
        playerScore = 0;
        savePlayerData();
    }

}

[System.Serializable]
public class PlayerData
{
    public bool playerExist;
    public float gameMusicVolume;
    public float gameSoundEffectsVolume;
    public string playerName;
    public int completedLevelsCount;
    public int playerScore;

}
