using UnityEngine;
using UnityEditor;
using UnityEditor.Callbacks;
using Unity.Appodeal.Xcode;

using System;
using System.Diagnostics;
using System.IO;
using System.Collections;

#if UNITY_IPHONE
public class AppodealPostProcess : MonoBehaviour
{
	private static PBXProject proj;
	private static string targetGuid;
	private static string projPath;

	[PostProcessBuild(1)]
	public static void OnPostProcessBuild (BuildTarget target, string pathToBuildProject)
	{		
		
		UnityEngine.Debug.Log("===================== appodeal postbuild start ====================");
		projPath = pathToBuildProject + "/Unity-iPhone.xcodeproj/project.pbxproj";
		proj = new PBXProject();
		proj.ReadFromString(File.ReadAllText(projPath));
		targetGuid = proj.TargetGuidByName("Unity-iPhone");

		//frameworks
		string suffix = ".framework";
		proj.AddFrameworkToProject (targetGuid,"Twitter"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"AdSupport"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"AudioToolbox"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"AVFoundation"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"CoreFoundation"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"CFNetwork"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"CoreGraphics"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"CoreImage"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"CoreMedia"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"CoreLocation"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"CoreMotion"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"CoreTelephony"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"JavaScriptCore"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"EventKitUI"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"EventKit"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"MediaPlayer"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"MessageUI"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"QuartzCore"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"MobileCoreServices"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"Security"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"StoreKit"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"Social"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"SystemConfiguration"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"Twitter"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"UIKit"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"WebKit"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"CoreBluetooth"+suffix,true);
		proj.AddFrameworkToProject (targetGuid,"GLKit"+suffix,true);

		//libs
		proj.AddFileToBuild(targetGuid, proj.AddFile("usr/lib/libc++.tbd", "Frameworks/libc++.tbd", PBXSourceTree.Sdk));
		proj.AddFileToBuild(targetGuid, proj.AddFile("usr/lib/libsqlite3.tbd", "Frameworks/libsqlite3.tbd", PBXSourceTree.Sdk));
		proj.AddFileToBuild(targetGuid, proj.AddFile("usr/lib/libxml2.2.tbd", "Frameworks/libxml2.2.tbd", PBXSourceTree.Sdk));
		proj.AddFileToBuild(targetGuid, proj.AddFile("usr/lib/libz.tbd", "Frameworks/libz.tbd", PBXSourceTree.Sdk));

		//flags
		//proj.SetBuildProperty(targetGuid, "ENABLE_BITCODE", "NO");
		proj.AddBuildProperty(targetGuid, "FRAMEWORK_SEARCH_PATHS", "$(PROJECT_DIR)/Appodeal");
		proj.AddBuildProperty(targetGuid, "FRAMEWORK_SEARCH_PATHS", "$(PROJECT_DIR)/Frameworks/Plugins/iOS");
		proj.SetBuildProperty(targetGuid, "LIBRARY_SEARCH_PATHS", "$(SRCROOT)/Libraries");


		proj.AddBuildProperty(targetGuid, "OTHER_LDFLAGS", "-ObjC");

		File.WriteAllText(projPath, proj.WriteToString());

		UnityEngine.Debug.Log("====================== appodeal postbuild end =====================");	
	}

	internal static void CopyAndReplaceDirectory(string srcPath, string dstPath)
	{
		if (Directory.Exists(dstPath))
			Directory.Delete(dstPath);
		if (File.Exists(dstPath))
			File.Delete(dstPath);

		Directory.CreateDirectory(dstPath);

		foreach (var file in Directory.GetFiles(srcPath)) {
			File.Copy (file, Path.Combine (dstPath, Path.GetFileName (file)));

			//ignore useless files for 'Copy Bundle Resources'
			if(!file.Contains(".DS_Store") && !file.Contains(".framework"))
				proj.AddFileToBuild(targetGuid, proj.AddFile(Path.Combine (dstPath, Path.GetFileName (file)), Path.Combine (dstPath, Path.GetFileName (file)), PBXSourceTree.Source));
		}

		foreach (var dir in Directory.GetDirectories(srcPath)){
			CopyAndReplaceDirectory(dir, Path.Combine(dstPath, Path.GetFileName(dir)));
			if (Path.GetFileName (dir).Contains (".bundle")) {				
				proj.AddFolderReference (Path.Combine (dstPath, Path.GetFileName (dir)), Path.Combine (dstPath, Path.GetFileName (dir)), PBXSourceTree.Source);
				proj.AddFileToBuild (targetGuid, proj.AddFile (Path.Combine (dstPath, Path.GetFileName (dir)), Path.Combine (dstPath, Path.GetFileName (dir)), PBXSourceTree.Source));
			}
		}
	}
}
#endif