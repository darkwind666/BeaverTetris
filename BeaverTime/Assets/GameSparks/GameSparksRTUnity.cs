using UnityEngine;
using System;
using System.Collections.Generic;
using GameSparks.Api.Responses;
using GameSparks.Api.Messages;
using GameSparks.RT;

public class GameSparksRTUnity : MonoBehaviour, IRTSessionListener {

	IRTSession session;
	Action<int> m_OnPlayerConnect;
	Action<int> m_OnPlayerDisconnect;
	Action<bool> m_OnReady;
	Action<RTPacket> m_OnPacket;

	// Static singleton instance
	private static GameSparksRTUnity instance;
	
	// Static singleton property
	public static GameSparksRTUnity Instance { 
		get { 
			if(instance == null) {
				instance = new GameObject("GameSparksRTUnity").AddComponent<GameSparksRTUnity>();
				DontDestroyOnLoad(instance.gameObject);
			}
			return instance; 
		}
		private set { 
			if(instance != null && instance != value)
			{
				Destroy(instance.gameObject);
			}
			instance = value;
		} 
	}

	void Awake()
	{
		instance = this;
		DontDestroyOnLoad(gameObject);
	}

	//Configure the SDK with a MatchFoundMessage
	public void Configure(MatchFoundMessage message, 
	                      Action<int> OnPlayerConnect,
	                      Action<int> OnPlayerDisconnect,
	                      Action<bool> OnReady,
	                      Action<RTPacket> OnPacket){
		
		if(!message.Port.HasValue){
			Debug.Log("Response does not contain a port, exiting.");
			return;
		}
		
		Configure(message.Host,
		          message.Port.Value,
		          message.AccessToken, 
		          OnPlayerConnect,
		          OnPlayerDisconnect,
		          OnReady, 
		          OnPacket);
	}

	//Configure the SDK with a FindMatchResponse
	public void Configure(FindMatchResponse response, 
	                      Action<int> OnPlayerConnect,
	                      Action<int> OnPlayerDisconnect,
	                      Action<bool> OnReady,
	                      Action<RTPacket> OnPacket){

		if(!response.Port.HasValue){
			Debug.Log("Response does not contain a port, exiting.");
			return;
		}

		Configure(response.Host,
		          response.Port.Value,
		          response.AccessToken, 
		          OnPlayerConnect,
		          OnPlayerDisconnect,
		          OnReady, 
		          OnPacket);
	}

	//Configure the SDK manually
	public void Configure(string host, 
	                      int port,
	                      string accessToken,
               Action<int> OnPlayerConnect,
               Action<int> OnPlayerDisconnect,
               Action<bool> OnReady,
               Action<RTPacket> OnPacket){

		m_OnPlayerConnect = OnPlayerConnect;
		m_OnPlayerDisconnect = OnPlayerDisconnect;
		m_OnReady = OnReady;
		m_OnPacket = OnPacket;

		if(session != null){
			session.Stop();
		}

		session = GameSparksRT
			.SessionBuilder()
				.SetHost(host)
				.SetPort(port)
				.SetConnectToken(accessToken)
				.SetListener(this)
				.Build();
							
	}

	//Connect to the realtime servers
	public void Connect(){
		if(session != null){
			Debug.Log("Starting Session");
			session.Start();
		} else {
			Debug.Log("Cannot start Session");
		}
	}

	//Disconnect from the realtime servers
	public void Disconnect(){
		if(session != null){
			session.Stop();
		}
	}

	//The current sessions PeerId
	public int? PeerId{
		get 
		{
			if(session != null)
				return session.PeerId;
			return null;
		}
	}

	//The list of active peers in the session
	public List<int> ActivePeers{
		get 
		{
			if(session != null)
				return session.ActivePeers;
			return null;
		}
	}

	//Whether the SDK is ready for sending and recieving data
	public bool Ready{ 
	get 
		{
			return(session != null && session.Ready);
		}
	}

	//The method to use to send data to a session.
	public int SendData (int opCode, 
	                      GameSparksRT.DeliveryIntent deliveryIntent, 
						  RTData structuredData, 
	                      params int[] targetPlayers){
		if(session != null){
			return session.SendRTData(opCode, deliveryIntent, structuredData, targetPlayers);
		}
		return -1;
	}

	//The method to use to send data to a session.
	public int SendBytes (int opCode, 
		GameSparksRT.DeliveryIntent deliveryIntent, 
		ArraySegment<byte> unstructuredData, 
		params int[] targetPlayers){
		if(session != null){
			return session.SendBytes(opCode, deliveryIntent, unstructuredData, targetPlayers);
		}
		return -1;
	}

	//The method to use to send data to a session.
	public int SendRTDataAndBytes (int opCode, 
		GameSparksRT.DeliveryIntent deliveryIntent, 
		ArraySegment<byte> unstructuredData, 
		RTData structuredData,
		params int[] targetPlayers){
		if(session != null){
			return session.SendRTDataAndBytes(opCode, deliveryIntent, unstructuredData, structuredData, targetPlayers);
		}
		return -1;
	}

	void OnDestroy(){
		Disconnect();
	}

	void Update () {
		if(session != null) {
			session.Update();
		}
	}

	public void OnPlayerConnect (int peerId){
		if(m_OnPlayerConnect != null){
			m_OnPlayerConnect(peerId);
		}
	}
	
	public void OnPlayerDisconnect (int peerId){
		if(m_OnPlayerDisconnect != null){
			m_OnPlayerDisconnect(peerId);
		}
	}
	
	public void OnReady (bool ready){
		if(m_OnReady != null) {
			m_OnReady(ready);
		}
	}

	public void OnPacket (RTPacket packet){
		if(m_OnPacket != null) {
			m_OnPacket(packet);
		}
	}

}

public static class RTDataExtensions
{
	
	public static RTData SetVector2(this RTData data, uint index, Vector2 vector2){
		data.SetRTVector(index, new RTVector(vector2.x, vector2.y));
		return data;
	}

	public static Vector2? GetVector2(this RTData data, uint index){
		if(data.GetRTVector(index) != null){
			RTVector vector = data.GetRTVector(index).Value;
			return new Vector2(vector.x.Value, vector.y.Value);
		}
		return null;
	}

	public static RTData SetVector3(this RTData data, uint index, Vector3 vector3){
		data.SetRTVector(index, new RTVector(vector3.x, vector3.y, vector3.z));
		return data;
	}

	public static Vector3? GetVector3(this RTData data, uint index){
		if(data.GetRTVector(index) != null){
			RTVector vector = data.GetRTVector(index).Value;
			if(!vector.z.HasValue){
				return null;
			}
			return new Vector3(vector.x.Value, vector.y.Value, vector.z.Value);
		}
		return null;
	}

	public static RTData SetVector4(this RTData data, uint index, Vector4 vector4){
		data.SetRTVector(index, new RTVector(vector4.x, vector4.y, vector4.z, vector4.w));
		return data;
	}

	public static Vector4? GetVector4(this RTData data, uint index){
		if(data.GetRTVector(index) != null){
			RTVector vector = data.GetRTVector(index).Value;
			if(!vector.w.HasValue){
				return null;
			}
			return new Vector4(vector.x.Value, vector.y.Value, vector.z.Value, vector.w.Value);
		}
		return null;
	}
}
