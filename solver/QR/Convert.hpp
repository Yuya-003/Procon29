#pragma once
#include "QR.hpp"
#include <fstream>

static Field GetQRContent()
{
	Field field;
	Position firstPlace[2];
	size_t h, w;
	std::vector<std::string> splitText;
	std::vector<std::vector<int>> splitValue;

	std::ifstream ifs("./field.txt");
	if (ifs.fail()) {
		return Field();
	}

	std::string str;
	ifs >> str;
	ifs.close();

	//�ǂݎ�����e�L�X�g���s�E����ێ����ĕ������ϊ�
	for (const auto tempStr : QRInfo::Split(str, ':')) {
		splitText.push_back(tempStr);
	}

	for (int i = 0; i < splitText.size(); i++) {
		std::vector<int> temp;
		std::vector<std::string> splitStr = QRInfo::Split(splitText[i], ' ');

		for (int j = 0; j < splitStr.size(); j++) {
			temp.push_back(atoi(splitStr[j].c_str()));
		}

		splitValue.push_back(temp);
	}

	//�ϊ������l�̂����s,��,�v���C���[�̂���ꏊ��ʕϐ��ɑ��
	h = splitValue[0][0];
	w = splitValue[0][1];
	firstPlace[0] = { splitValue[h + 1][0] - 1 ,splitValue[h + 1][1] - 1 };
	firstPlace[1] = { splitValue[h + 2][0] - 1 ,splitValue[h + 2][1] - 1 };

	//Field�֑��
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

	//�v���C���[�̂���ꏊ��ۑ�
	field.team1[0] = { firstPlace[0].x + 1,firstPlace[0].y + 1 };
	field.team2[1] = { firstPlace[0].x + 1,firstPlace[1].y + 1 };
	field.team2[0] = { firstPlace[1].x + 1,firstPlace[0].y + 1 };
	field.team1[1] = { firstPlace[1].x + 1,firstPlace[1].y + 1 };

	//�v���C���[�̂���ꏊ�̃X�e�[�^�X��ύX
	field.cells[firstPlace[0].x][firstPlace[0].y].status = Cell::team1;
	field.cells[firstPlace[0].x][firstPlace[1].y].status = Cell::team2;
	field.cells[firstPlace[1].x][firstPlace[0].y].status = Cell::team2;
	field.cells[firstPlace[1].x][firstPlace[1].y].status = Cell::team1;

	return field;
}