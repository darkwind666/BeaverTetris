## For setting xcode export postbuild you need:

1. Download latest Appodeal native ios sdk

2. Set variables in `Editor/AppodealPostProcess.cs`
    ```
    ...
    // !TODO: set this to your xcode project name
    string xcodeProjName = "IOS";
    // !TODO: set this to path, where you download native Appodeal ios sdk
    string appodealSdkPath = "/../Appodeal";
    ...
    ```

3. Run build command
