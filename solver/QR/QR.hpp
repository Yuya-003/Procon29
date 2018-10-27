#pragma once
#include <Siv3D.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <structure/Field.hpp>

class QRInfo {
private:
	static std::string qrText;

public:
	QRContent content;
	static bool isCameraStopped;

	//static std::vector<std::string> Split(const std::string &str, char del);

	//�ǂ݂Ƃ����e�L�X�g��std::string�ɕϊ�
	void SetString();

	//std::string��Field�ɕϊ����Ď󂯓n��
	//static Field GetQRContent();
};