#include "QR.hpp"

std::string QRInfo::qrText = "";
bool QRInfo::isCameraStopped = false;

std::vector<std::string> QRInfo::Split(const std::string & str, char del)
{
	std::vector<std::string> subStr;
	std::stringstream ss(str);
	std::string item;
	while (std::getline(ss, item, del)) {
		if (!item.empty()) {
			subStr.push_back(item);
		}
	}

	return subStr;
}

void QRInfo::SetString() {
	qrText = content.text.narrow();
}