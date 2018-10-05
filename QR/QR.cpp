#include "QR.hpp"
#include <string>

void Main()
{
	Window::Resize(1280, 720);

	bool isWebcamMoving = false;

	Webcam webcam(0);

	webcam.setResolution(1280, 720);
	webcam.start();

	Image image;
	DynamicTexture texture;
	QRDecoder qrDecoder;
	QRInfo qr;

	while (System::Update())
	{
		if (KeyEnter.down()) {
			webcam.stop();
			WebcamStop(webcam);
		}

		if (webcam.hasNewFrame())
		{
			ClearPrint();
			webcam.getFrame(image);

			QRContent contents;

			qrDecoder.decode(image, contents);
			contents.quad.overwriteFrame(image, 6, Palette::Red);

			if (contents.text)
			{
				Print << contents.text;
				qr.SetString(contents.text.narrow());
			}
			else {
				Print << U"No text";
			}

			std::string qrContent = qr.GetString();
			Print << qrContent;
		}

		texture.fill(image);
		texture.draw();
	}
}

void WebcamStop(Webcam webcam) {
	
}