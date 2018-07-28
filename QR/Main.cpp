#include <Siv3D.hpp>
#include <fstream>
#include <string>

class QRInfo {
private:
	std::string qrInfo;
	bool checkOutput = false;
public:
	void SetQRContent(std::string set) {
		qrInfo = set;
	}

	std::string GetQRContent() {
		return qrInfo;
	}

	void OutputQRContent() {
		std::ofstream outputFile("test.txt");

		if (KeyEnter.pressed() && !checkOutput) {
			if (!qrInfo.empty()) {
				outputFile << qrInfo;
				outputFile.close();
				checkOutput = true;
				Print << U"Output";
			}
		}

		if (checkOutput) {
			Print << U"Output End";
		}
	}
};

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


	while (System::Update())
	{
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
				qr.SetQRContent(contents.text.narrow());
			}
			else {
				Print << U"No text";
			}

			Print << U"";
			Print << Unicode::Widen(qr.GetQRContent());

			qr.OutputQRContent();
		}

		texture.fill(image);
		texture.draw();
	}
}
