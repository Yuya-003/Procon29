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

			if (!str.empty()) 
				String wStr(str);
				if (KeyEnter.down()) {
					outputfile << str;
					Print << U"Output";
				}
			}

			texture.fill(image);
		}


		texture.draw();
	}
}