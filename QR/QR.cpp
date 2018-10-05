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
	String qrText = U"No text.";
	static bool isCameraStopped = false;

	while (System::Update())
	{
		ClearPrint();

		if (webcam.hasNewFrame())
		{
			ClearPrint();
			webcam.getFrame(image);

			QRContent contents;

			qrDecoder.decode(image, contents);
			contents.quad.overwriteFrame(image, 6, Palette::Red);

			if (contents.text)
			{
				qrText = contents.text;
				qr.SetString(contents.text.narrow());
			}
		}

		if (KeyEnter.down()) {
			webcam.stop();
			isCameraStopped = true;
		}

		Print << qrText;

		texture.fill(image);
		texture.draw();
	}
}