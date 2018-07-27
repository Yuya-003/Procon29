#include <Siv3D.hpp>
#include <fstream>
#include <string>

void Main()
{
	Window::Resize(1280, 720);

	Webcam webcam(0);

	webcam.setResolution(1280, 720);

	webcam.start();

	Image image;

	DynamicTexture texture;

	QRDecoder qrDecoder;

	std::ofstream outputfile("test.txt");

	std::string str;

	bool checkOutput = false;

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
				str = contents.text.narrow();
			}
			else {
				Print << U"No text";
			}

			Print << U"";
			if (!str.empty()) {
				String wStr = Unicode::Widen(str);
				Print << wStr;
			}
			if (KeyEnter.pressed())Print << U"Enter Pressed";
			if (KeyEnter.pressed() && !checkOutput) {
				if (!str.empty()) {
					outputfile << str;
					outputfile.close();
					checkOutput = true;
					Print << U"Output";
				}
			}

			if (checkOutput) {
				Print << U"Output End";
			}
		}

		texture.fill(image);

		texture.draw();
	}
}