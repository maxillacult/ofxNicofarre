#ofxNicoFarre

Recommended oF version : v0.8.0~

**
This addon is a simulator for LED display at event space "Nicofarre" in Japan.
このアドオンは、openFrameworksを使ってニコファーレ用の映像を作るためのシミュレーターです。
**



※本アドオンは、ニコファーレでの映像出力においてリハーサル回数を抑える等の目的で補助的にシミュレートする非公式のアドオンです。
イベント演出の完全再現を保証するものではありませんのでご了承ください。

##Reference

#####void ofxNicofarre::setup(int w,int h, ofFbo* buffer);
シミュレータを初期化します。
Int型の変数w,hでプレビュー用Fboのサイズを指定します。
Opentextureモード(※後述)を使用しない場合、省略することができます。

#####void ofxNicofarre::begin();
ソース用Fboのbeginメソッドが呼び出されます。映像を描画する前に呼び出します。

#####void ofxNicofarre::end();
ソース用Fboのendメソッドが呼び出されます。映像を描画し終えた後に呼び出します。

#####void ofxNicofarre::BufUpdate();
ソース用のFboに描画されたバッファから、3Dモデルへテクスチャを更新します。

#####void ofxNicofarre::previewDraw(int x,int y, int w, int h);
シミュレートされたニコファーレの3Dモデルを表示します。

#####void ofxNicofarre::setBrightness(ofxNicofarrePanel panel,float brightness);
各パネルの輝度を調整します。brightnessの値は0.0~1.0の間です。
※この機能は、openTextureモードの時のみ動作します。


##OpenTextureMode
OpenTextureModeは、横長の連続したバッファを用いて映像を生成するためのモードです。
従来のニコファーレ規格ではフルHD内におさめた映像を出力する必要がありますが([Webサイト参照](http://nicofarre.jp/smarty.php?tmpl=led_format.html&sctn=led_format))、このモードでは壁面のパネルを
横一列に展開したテクスチャを用います。


ヘッダ部分では、以下のオブジェクトを追加します。

	ofxNicofarre	NicoFarre;
	ofFbo			buffer;

初期化では、FBOのサイズを(4938,320)とし、ofxNicoFarre::setup()を呼び出す際に、FBOのポインタを渡します。

	void testApp::setup(){

		buffer.allocate(4938, 320);
		NicoFarre.setup(1280,720,&buffer);

	}
その後、testApp::draw()メソッド内でFBOに描画し、Nicofarreフォーマットに内部で変換して使うことができます。

	void testApp::draw(){

		buffer.begin();

		ofClear(0, 0, 0);
		ofSetColor(255, 255, 255);
		/*-*-*-*-*-*-*-*-*-*- Draw something you want *-*-*-*-*-*-*-*-*/

		buffer.end();

		/*--- Send source buffer to 3D preview---*/
		NicoFarre.BufUpdate();

		/*--- Draw Nicofarre ---*/
		ofSetColor(255);
		NicoFarre.previewDraw(0, 0);

	}
ニコファーレ用のフォーマットに変換された映像はofxNicofarre::getSourceBuf()メソッドで取得することができるので、このFBOを書き出すことで従来のフォーマットに対応した画像もデータ出力することができます。