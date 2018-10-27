#include "QR.hpp"

std::string QRInfo::qrText = "";
bool QRInfo::isCameraStopped = false;

void QRInfo::SetString() {
	qrText = content.text.narrow();
}