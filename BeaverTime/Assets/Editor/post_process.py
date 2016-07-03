import os
import sys
from sys import argv
from mod_pbxproj import XcodeProject

path = argv[1]
fileToAddPath = argv[2]

print(
      '----------------------------------prepare for excuting our magic scripts to tweak our xcode ----------------------------------')
print('post_process.py xcode build path --> ' + path)
print('post_process.py third party files path --> ' + fileToAddPath)

# add CFBundleURLTypes for FB
urlTypes = '''
    <key>CFBundleURLTypes</key>
    <array>
    <dict>
				<key>CFBundleURLName</key>
                <string></string>
                <key>CFBundleURLSchemes</key>
                <array>
                <string>fbXXXXX</string>
                </array>
                </dict>
                </array>
                </dict>
                </plist>
    '''

print(urlTypes)


class front_appender:
    def __init__(self, fname, mode='w'):
        self.__f = open(fname, mode)
        self.__write_queue = []
    
    def write(self, s):
        self.__write_queue.insert(0, s)
    
    def close(self):
        self.__f.writelines(self.__write_queue)
        self.__f.close()


f = open(path + '/Info.plist', 'r+')
content = f.read()
#if 'fbXXXXX' in content:
#    print "*******************Append Action, skip custom script"
#    sys.exit("quit exeuction")

print "*******************Replace Action, executing our script"
f.seek(content.find('</dict>\n</plist>'))
f.write(urlTypes)
f.close()

print('Step 1: start add libraries ')
framework_list = [
                  ('framework', 'AdSupport'),
                  ('framework', 'AudioToolbox'),
                  ('framework', 'AVFoundation'),
                  ('framework', 'CFNetwork'),
                  ('framework', 'CoreFoundation'),
                  ('framework', 'CoreGraphics'),
                  ('framework', 'CoreImage'),
                  ('framework', 'CoreLocation'),
                  ('framework', 'CoreMedia'),
                  ('framework', 'CoreMotion'),
                  ('framework', 'CoreTelephony'),
                  ('framework', 'JavaScriptCore'),
                  ('framework', 'EventKit'),
                  ('framework', 'EventKitUI'),
                  ('lib', 'libc++.dylib'),
                  ('lib', 'libsqlite3.dylib'),
                  ('lib', 'libxml2.2.dylib'),
                  ('lib', 'libz.dylib'),
                  ('framework', 'MediaPlayer'),
                  ('framework', 'MessageUI'),
                  ('framework', 'MobileCoreServices'),
                  ('framework', 'QuartzCore'),
                  ('framework', 'Security'),
                  ('framework', 'Social'),
                  ('framework', 'StoreKit'),
                  ('framework', 'SystemConfiguration'),
                  ('framework', 'Twitter'),
                  ('framework', 'UIKit'),
                  ('framework', 'WebKit')
                  ]


project = XcodeProject.Load(path + '/Unity-iPhone.xcodeproj/project.pbxproj')
for item in framework_list:
    if item[0] == 'framework':
        project.add_file('System/Library/Frameworks/' + item[1] + '.framework', tree='SDKROOT')
    else:
        project.add_file('usr/lib/' + item[1] + '', tree='SDKROOT')

print('Step 2: add files to xcode, exclude any .meta file')
files_in_dir = os.listdir(fileToAddPath)

# adding Appodeal.framework and Resources from path
if os.path.isdir(fileToAddPath + "Appodeal.framework"):
    project.add_folder(fileToAddPath + "Appodeal.framework")
if os.path.isdir(fileToAddPath + "Resources"):
    project.add_folder(fileToAddPath + "Resources")

#for f in files_in_dir:
#    if not f.startswith('.'):  # ignore .DS_STORE
#        print f
#        pathname = os.path.join(fileToAddPath, f)
#        fileName, fileExtension = os.path.splitext(pathname)
#        if not fileExtension == '.meta':  # ignore .meta as it is under asset server
#            if os.path.isfile(pathname):
#                print "is file : " + pathname
#                project.add_file(pathname)
#            if os.path.isdir(pathname):
#                print "is dir : " + pathname
#                project.add_folder(pathname, excludes=["^.*\.meta$"])

project.add_framework_search_paths(["$(PROJECT_DIR)/Appodeal"], recursive=False)
project.add_other_ldflags('-ObjC')

print('Step 4: change build setting')
#project.add_other_buildsetting('GCC_ENABLE_OBJC_EXCEPTIONS', 'YES')

if project.modified:
    project.backup()
    project.save()

print(
      '----------------------------------end for excuting our magic scripts to tweak our xcode ----------------------------------')
