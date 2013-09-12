Patches for PuTTYgen to add Leap Motion support
=================================================

Demo
-------------------------------------------------
See Youtube movie.  
<a href="http://www.youtube.com/watch?feature=player_embedded&v=xA10UN25bik
" target="_blank"><img src="http://img.youtube.com/vi/xA10UN25bik/0.jpg" 
alt="Demo movie" width="320" height="180" border="0" /></a>

Requirement
-------------------------------------------------
* Connected Leap Motion controller
* Installed Leap Motion SDK 1.0.8.7665 for Windows
* Installed Visual Studio 2012 or Visual Studio Express 2012 for Windows Desktop
* OS: Windows 8  
  (It may be  that the patched app will be runnable on other OS which supported by putty, but I have never run it on except Windows 8.)

How to build
-------------------------------------------------
1. Download official PuTTY archive.  
 http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html  
 (Source code -> Windows source code -> Release source code for Windows)
2. Extract archive to local storage. 
3. Set environment variable "LEAP_SDK" to point the "LeapSDK" (not "LeapDeveloperKit") directory of installed Leap Motion SDK.    
    Example:  
    ![Set envrionment variable](https://github.com/Yasami/Leappgen/raw/master/newenv.png "Set LEAP_SDK C:\Tools\LeapDeveloperKit\LeapSDK")
4. Open putty-src\WINDOWS\MSVC\PUTTYGEN\PUTTYGEN.sln by Visual Studio.
5. Build and run.


License
------------------------------------------------
The same license as original PuTTY.

