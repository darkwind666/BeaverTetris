using UnityEngine;
using System.Collections;
using UnityEditor;
using UnityEditor.Callbacks;
using System;
using System.Diagnostics;

public class AppodealPostProcess : MonoBehaviour
{
	[PostProcessBuild(1)]
	public static void OnPostProcessBuild (BuildTarget target, string pathToBuildProject)
	{
#if UNITY_IPHONE
		UnityEngine.Debug.Log("===================== appodeal postbuild start ====================");

		// !TODO: set this to path, where you download native Appodeal ios sdk
		string appodealSdkPath = "/Users/ploddi/Projects/Appodeal/AppodealSDK-Unity-Plugin/Build/Appodeal/";

		Process pythonProcess = new Process();
		pythonProcess.StartInfo.FileName = "python";
		pythonProcess.StartInfo.Arguments = string.Format("Assets/Editor/post_process.py \"{0}\" \"{1}\"", pathToBuildProject, appodealSdkPath);

		UnityEngine.Debug.Log(pythonProcess.StartInfo.Arguments);

		pythonProcess.StartInfo.UseShellExecute = false;
		pythonProcess.StartInfo.RedirectStandardOutput = false;
		pythonProcess.Start();
		pythonProcess.WaitForExit();

		UnityEngine.Debug.Log("====================== appodeal postbuild end =====================");
#endif
	}
}
