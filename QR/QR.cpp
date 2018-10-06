#include "QR.hpp"

void Main()
{
	Window::Resize(1280, 720);

	Webcam webcam(0);

	webcam.setResolution(1280, 720);
	webcam.start();

	Image image;
	DynamicTexture texture;
	QRDecoder qrDecoder;

	QRInfo qr;
	Field field;
	String qrText = U"No text.";
	static bool isCameraStopped = false;

	while (System::Update())
	{
		ClearPrint();

		if (webcam.hasNewFrame())
		{
			webcam.getFrame(image);

			qrDecoder.decode(image, qr.content);
			qr.content.quad.overwriteFrame(image, 6, Palette::Red);

			if (qr.content.text)
			{
				qrText = qr.content.text;
				qr.SetString();
			}
		}

		if (!isCameraStopped) {
			texture.fill(image);
			texture.draw();

			if (KeyEnter.down()) {
				webcam.stop();
				isCameraStopped = true;
			}
		}

		Print << qrText;
	}
}