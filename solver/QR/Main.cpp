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

	//�E�B���h�E�T�C�Y�̃��T�C�Y
	Window::Resize(1280, 720);

	//�J�����̋N��
	webcam.setResolution(1280, 720);
	webcam.start();

	while (System::Update())
	{
		//�`�悳��Ă������̂�S�ď���
		ClearPrint();

		if (webcam.hasNewFrame())
		{
			webcam.getFrame(image);

			//QR�R�[�h���f�R�[�h
			qrDecoder.decode(image, qr.content);
			//QR�R�[�h�ɐԘg��t�^
			qr.content.quad.overwriteFrame(image, 6, Palette::Red);

			if (qr.content.text)
			{
				qrText = qr.content.text;
				qr.SetString();

				std::ofstream ofs("./field.txt");

				std::string temp = qrText.narrow();
				std::vector<std::string> trans = Split(temp, ':');

				for (int i = 0; i < trans.size(); i++) {
					ofs << trans[i];
					ofs << "\n";
				}

				ofs.close();
			}
		}

		//�J�������~�܂��Ă��Ȃ�������J�����̉摜��`��
		if (!qr.isCameraStopped) {
			texture.fill(image);
			texture.draw();

			//Enter�������ƃJ�������~
			if (KeyEnter.down()) {
				webcam.stop();
				qr.isCameraStopped = true;
			}
		}

		//�ǂݎ�����e�L�X�g��\��
		Print << qrText;
	}
}