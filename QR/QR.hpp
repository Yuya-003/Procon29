#pragma once
#include <Siv3D.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <structure/Field.hpp>

struct Place {
	int x, y;
};

class QRInfo {
private:
	static std::string qrText;

	static std::vector<std::string> Split(const std::string &str, char del) {
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

public:
	QRContent content;

	void SetString() {
		qrText = content.text.narrow();
	}

	void QRToField() {
		
	}

	static Field GetQRContent() {
		Field field;
		Cell temp;
		size_t h, w;
		std::vector<std::vector<int>> splitValue;
		struct Place firstPlace[2];

		for (const auto tempStr : Split(qrText, ':')) {
			for (unsigned int i = 0; i < tempStr.length(); i++) {
				for (const auto splitStr : Split(tempStr, ' ')) {
					splitValue[i].push_back(atoi(splitStr.c_str()));
				}
			}
		}

		h = splitValue[0][0];
		w = splitValue[0][1];
		firstPlace[0] = { splitValue[h + 1][0] ,splitValue[h + 1][1] };
		firstPlace[1] = { splitValue[h + 2][0] ,splitValue[h + 2][1] };

		field.resize(h, w);

		for (unsigned int i = 0; i < h; i++) {
			for (unsigned int j = 0; j < w; j++) {
				temp.point = splitValue[i + 1][j];
				temp.status = temp.none;

				field.cells[i].push_back(temp);
			}
		}

		for (int i = 0; i < 2; i++) {
			field.cells[firstPlace[0].x][firstPlace[0].x].status = temp.team1;
			field.cells[firstPlace[1].x][firstPlace[1].x].status = temp.team2;
		}

		return field;
	}
};

std::string QRInfo::qrText = "";