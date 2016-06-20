using UnityEngine;
using System.Collections.Generic;
using System;
using GameSparks;
using GameSparks.Core;
using GameSparks.Platforms;
using GameSparks.Platforms.IOS;
using GameSparks.Platforms.WebGL;
using GameSparks.Platforms.Native;

/// <summary>
/// This is the starting point for GameSparks in your Unity game.
/// Add this class to a GameObject to get started.
/// </summary>
public class GameSparksUnity : MonoBehaviour
{
	/// <summary>
	/// You can override which connection settings GameSparks uses to connect to the backend with this member.
	/// </summary>
    public GameSparksSettings settings;

	void Start()
	{
#if (UNITY_IOS || UNITY_TVOS) && !UNITY_EDITOR
		this.gameObject.AddComponent<IOSPlatform>();
#elif ((UNITY_PS4 || UNITY_XBOXONE) && !UNITY_EDITOR) || GS_FORCE_NATIVE_PLATFORM
        this.gameObject.AddComponent<NativePlatform>();
#elif UNITY_WEBGL && !UNITY_EDITOR
		this.gameObject.AddComponent<WebGLPlatform>();
#else
		this.gameObject.AddComponent<DefaultPlatform>();
#endif
	}

	void OnGUI () {
		if (GameSparksSettings.PreviewBuild == true) {
			GUILayout.BeginArea(new Rect(0, 0, Screen.width, Screen.height));

			GUILayout.BeginVertical ();

			GUILayout.FlexibleSpace ();

			GUILayout.BeginHorizontal ();

			GUILayout.Space (10);

			GUILayout.Label ("GameSparks Preview mode", GUILayout.Width (200), GUILayout.Height (25));

			GUILayout.EndHorizontal ();

			GUILayout.EndVertical ();

			GUILayout.EndArea ();
		}
	}
}
