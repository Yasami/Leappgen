PuTTYgen に Leap Motion 対応を追加するパッチ
=================================================

デモ
-------------------------------------------------
動画をみてください。  
<a href="http://www.youtube.com/watch?feature=player_embedded&v=xA10UN25bik
" target="_blank"><img src="http://img.youtube.com/vi/xA10UN25bik/0.jpg" 
alt="Demo movie" width="320" height="180" border="0" /></a>

必要条件
-------------------------------------------------
* Leap Motion コントローラーが接続されていること
* Leap Motion SDK 1.0.8.7665 for Windows がインストールされていること
* Visual Studio 2012 または Visual Studio Express 2012 for Windows Desktop がインストールされていること
* OS: Windows 8 (Windows 8 でしか動作確認していません。他のOSでの動作報告は歓迎します。)

ビルド方法
-------------------------------------------------
1. まず、PuTT 公式サイトからソースファイルをダウンロードします。  
 http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html  
 (Source code -> Windows source code -> Release source code for Windows)
2. ダウンロードしたファイルを、ローカルドライブの任意の場所に展開します。 
3. 展開したファイルにパッチを当てます。やり方は2種類あります。
  1. このリポジトリの"putty-src"ディレクトリを、展開してできた"putty-src"ディレクトリに上書きします。（おすすめ）
  2. "Add-Leap-Motion-feature.patch" を patch コマンドでパッチ適用します。
3. 環境変数"LEAP_SDK"に、Leap Motion SDK の "LeapSDK"ディレクトリのパスを設定します（"LeapDeveloperKit"ディレクトリではありません）。    
    Example:  
    ![Set envrionment variable](https://github.com/Yasami/Leappgen/raw/master/newenv.png "Set LEAP_SDK C:\Tools\LeapDeveloperKit\LeapSDK")
4. putty-src\WINDOWS\MSVC\PUTTYGEN\PUTTYGEN.sln を、 Visual Studio で開きます。
5. ビルドして実行します。


ライセンス
------------------------------------------------
PuTTY  のライセンスに従います。

その他
------------------------------------------------
PuTTY のソース規模に対して修正量が非常に少ないため、パッチのみの公開としています。
公開方法やライセンスファイルの記述などが不適切である場合、ご指摘ください。


