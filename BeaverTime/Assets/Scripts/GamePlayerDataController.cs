using UnityEngine;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;



public class GamePlayerDataController {

    const string playerDataFileName = "/playerData.bt";

    bool _playerExist;
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
            _playerExist = data.playerExist;
            file.Close();
        }

    }

    public void savePlayerData()
    {
        BinaryFormatter formatter = new BinaryFormatter();
        FileStream file = File.Create(_dataPath);
        PlayerData savingData = new PlayerData();
        savingData.playerExist = _playerExist;
        formatter.Serialize(file, savingData);
    }

}

[System.Serializable]
public class PlayerData
{
    public bool playerExist;
}
