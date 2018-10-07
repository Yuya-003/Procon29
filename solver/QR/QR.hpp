#pragma once
#include <Siv3D.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <structure/Field.hpp>

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
		Position firstPlace[2];
		size_t h, w;
		std::vector<std::string> splitText;
		std::vector<std::vector<int>> splitValue;
		
		for (const auto tempStr : Split(qrText, ':')) {
			splitText.push_back(tempStr);
		}

		for (int i = 0; i < splitText.size(); i++) {
			std::vector<int> temp;
			std::vector<std::string> splitStr = Split(splitText[i], ' ');

			for (int j = 0; j < splitStr.size(); j++) {
				temp.push_back(atoi(splitStr[j].c_str()));
			}

			splitValue.push_back(temp);
		}

		h = splitValue[0][0];
		w = splitValue[0][1];
		firstPlace[0] = { splitValue[h + 1][0] - 1 ,splitValue[h + 1][1] - 1 };
		firstPlace[1] = { splitValue[h + 2][0] - 1 ,splitValue[h + 2][1] - 1 };

		for (unsigned int i = 0; i < h; i++) {
			std::vector<Cell> cellArray;

			for (unsigned int j = 0; j < w; j++) {
				Cell tempCell;
				tempCell.point = splitValue[i + 1][j];
				tempCell.status = tempCell.none;

				cellArray.push_back(tempCell);
			}

			field.cells.push_back(cellArray);
		}

		field.cells[firstPlace[0].x][firstPlace[0].y].status = Cell::team1;
		field.cells[firstPlace[0].x][firstPlace[1].y].status = Cell::team2;
		field.cells[firstPlace[1].x][firstPlace[0].y].status = Cell::team2;
		field.cells[firstPlace[1].x][firstPlace[1].y].status = Cell::team1;

		return field;
	}
};

std::string QRInfo::qrText = "";