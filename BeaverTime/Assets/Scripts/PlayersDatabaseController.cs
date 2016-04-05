using UnityEngine;
using System.Collections.Generic;
using System;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

[Serializable]
public class PlayerRecordData
{
    public string playerName;
    public int playerScore;

    public PlayerRecordData(string aPlayerName, int aPlayerScore)
    {
        playerName = aPlayerName;
        playerScore = aPlayerScore;
    }
}

public class PlayersDatabaseController {

    const string playersRecordsDataFileName = "/playersRecords.bt";
    string _dataPath;

    List<PlayerRecordData> _records;

    public PlayersDatabaseController()
    {
        _dataPath = Application.persistentDataPath + playersRecordsDataFileName;
        _records = new List<PlayerRecordData>();
        loadPlayersRecordsData();
    }

    void loadPlayersRecordsData()
    {

        if (File.Exists(_dataPath))
        {
            BinaryFormatter formatter = new BinaryFormatter();
            FileStream file = File.Open(_dataPath, FileMode.Open);
            _records = formatter.Deserialize(file) as List<PlayerRecordData>;
            file.Close();
        }

    }

    public int getRecordsCount()
    {
        return _records.Count;
    }

    public PlayerRecordData getRecordForIndex(int aIndex)
    {
        return _records[aIndex];
    }

    public void saveNewPlayerRecord(PlayerRecordData aPlayerRecord)
    {
        _records.Add(aPlayerRecord);
        _records.Sort((x, y) => x.playerScore.CompareTo(y.playerScore));
        savePlayersRecordsData();
    }

    public void savePlayersRecordsData()
    {
        BinaryFormatter formatter = new BinaryFormatter();
        FileStream file = File.Create(_dataPath);
        formatter.Serialize(file, _records);
        file.Close();
    }

}
