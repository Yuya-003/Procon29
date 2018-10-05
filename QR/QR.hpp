#pragma once
#include <Siv3D.hpp>
#include <fstream>
#include <structure/Field.hpp>

class QRInfo {
private:
	std::string qrInfo;
	bool checkOutput = false;
public:
	std::string GetString() {
		return qrInfo;
	}

	void SetString(std::string set) {
		qrInfo = set;
	}

	static Field GetQRContent() {
		Field content;
	}
};
