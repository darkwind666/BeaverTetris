using UnityEngine;
using System.Collections.Generic;
using System;
using System.IO;

using System.Runtime.Serialization;
using System.Xml.Serialization;

#if UNITY_STANDALONE_OSX || UNITY_IOS
using System.Runtime.Serialization.Formatters.Binary;
#endif

public class PlayersDatabaseController {

    string playersRecordsDataFileName;
    string _dataPath;

    List<PlayerRecordData> _records;

    public PlayersDatabaseController()
    {
		playersRecordsDataFileName = getPlayersRecordsDataFileName();
        _dataPath = Application.persistentDataPath + playersRecordsDataFileName;
        _records = new List<PlayerRecordData>();
        loadPlayersRecordsData();
    }

	string getPlayersRecordsDataFileName()
	{
		string fileName = "/playersRecords.xml";


		#if UNITY_STANDALONE_OSX || UNITY_IOS
		fileName = "/playersRecords.bt";
		#endif

		return fileName;
	}

	IFormatter getDataFormatter()
	{
		IFormatter formatter = new PlayersDatabaseXMLFormatter();

		#if UNITY_STANDALONE_OSX || UNITY_IOS
		formatter = new BinaryFormatter();
		#endif

		return formatter;
	}

    void loadPlayersRecordsData()
    {

        if (File.Exists(_dataPath))
        {
			IFormatter formatter = getDataFormatter();
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
		checkRecordInDatabase(aPlayerRecord);
		_records.Sort((x, y) => -1* x.playerScore.CompareTo(y.playerScore));
        savePlayersRecordsData();
    }

	void checkRecordInDatabase(PlayerRecordData aPlayerRecord)
	{
		PlayerRecordData currentPlayerRecord = _records.Find(x => x.playerName == aPlayerRecord.playerName);

		if (currentPlayerRecord == null) {
			_records.Add (aPlayerRecord);
		} else 
		{
			if(currentPlayerRecord.playerScore < aPlayerRecord.playerScore)
			{
				currentPlayerRecord.playerScore = aPlayerRecord.playerScore;
			}
		}
	}

    public void savePlayersRecordsData()
    {
		IFormatter formatter = getDataFormatter();
        FileStream file = File.Create(_dataPath);
        formatter.Serialize(file, _records);
        file.Close();
    }

}

[Serializable]
public class PlayerRecordData
{
	public string playerName;
	public int playerScore;

	public PlayerRecordData() {}

	public PlayerRecordData(string aPlayerName, int aPlayerScore)
	{
		playerName = aPlayerName;
		playerScore = aPlayerScore;
	}
}

public class PlayersDatabaseXMLFormatter: IFormatter
{
	public ISurrogateSelector SurrogateSelector { get; set; }
	public SerializationBinder Binder { get; set; }
	public StreamingContext Context { get; set; }

	public void Serialize(Stream serializationStream, object graph)
	{
		XmlSerializer formatter = new XmlSerializer(typeof(List<PlayerRecordData>));
		formatter.Serialize(serializationStream, graph);
	}

	public object Deserialize(Stream serializationStream)
	{
		XmlSerializer formatter = new XmlSerializer(typeof(List<PlayerRecordData>));
		List<PlayerRecordData> data = formatter.Deserialize(serializationStream) as List<PlayerRecordData>;
		return data;
	}
}
