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

	//読みとったテキストをstd::stringに変換
	void SetString();

	//std::stringをFieldに変換して受け渡し
	//static Field GetQRContent();
};