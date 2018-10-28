#include "QR.hpp"
#include <fstream>
#include "Convert.hpp"

void Main()
{
	Webcam webcam(0);
	Image image;
	DynamicTexture texture;
	QRDecoder qrDecoder;
	QRInfo qr;
	String qrText = U"No text.";
	Field field;

	//ウィンドウサイズのリサイズ
	Window::Resize(1280, 720);

	//カメラの起動
	webcam.setResolution(1280, 720);
	webcam.start();

	while (System::Update())
	{
		//描画されていたものを全て消去
		ClearPrint();
		
		//カメラが1フレームを取得出来たら
		if(webcam.getFrame(image))
		{
			//QRコードをデコード
			if (qrDecoder.decode(image, qr.content) && qr.content.text) {
				//QRコードに赤枠を付与
				qr.content.quad.overwriteFrame(image, 6, Palette::Red);

				qrText = qr.content.text;
				qr.SetString();

				std::ofstream ofs("../../Qt/field.txt");

				ofs << qrText.narrow();

				ofs.close();
			}

			//カメラが止まっていなかったらカメラの画像を描画
			//if (!qr.isCameraStopped) {
				texture.fill(image);
				texture.draw();

				//Enterを押すとカメラを停止
				if (KeyEnter.down()) {
					webcam.stop();
					qr.isCameraStopped = true;
				}

			//}
		}

		//読み取ったテキストを表示
		Print << qrText;
	}
}