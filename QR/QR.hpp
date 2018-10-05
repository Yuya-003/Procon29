#pragma once
#include <Siv3D.hpp>
#include <structure/Field.hpp>
#include <string>
#include <vector>

class QRInfo {
private:
	static std::string qrInfo;
	bool checkOutput = false;

	static std::vector<std::string> split(std::string str, char del) {
		int first = 0;
		int last = str.find_first_of(del);
		std::vector<std::string> result;

		while (first < str.size)
		{
			std::string subStr(str, first, last - first);

			result.push_back(subStr);

			first = last + 1;
			last = str.find_first_of(del, first);

			if (last == std::string::npos) {
				last = str.size();
			}
		}

		return result;
	}

public:
	struct Point {
		int x, y;
	};

	std::string GetString() {
		return qrInfo;
	}

	void SetString(std::string set) {
		qrInfo = set;
	}

	static Field GetQRContent() {
		Field field;
		Cell temp;
		Point team1[2], team2[2];
		size_t h, w;
		std::vector<std::vector<int>> splitValue;

		for (const auto subStr : split(qrInfo, ':')) {
			for (int i = 0; i < subStr.length(); i++) {
				for (const auto subStr : split(subStr, ' ')) {
					splitValue[i].push_back(atoi(subStr.c_str));
				}
			}
		}

		h = splitValue[0][0];
		w = splitValue[0][1];
		team1[0] = { splitValue[h + 1][0] ,splitValue[h + 1][1] };
		team1[1] = { splitValue[h + 2][0] ,splitValue[h + 2][1] };
		team2[0] = { splitValue[h + 1][0] ,splitValue[h + 2][1] };
		team2[1] = { splitValue[h + 2][0] ,splitValue[h + 1][1] };

		field.resize(h, w);

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				temp.point = splitValue[i + 1][j];
				temp.status = temp.none;

				field.cells[i].push_back(temp);
			}
		}

		for (int i = 0; i < 2; i++) {
			field.cells[team1[0].x][team1[0].x].status = temp.team1;
			field.cells[team1[1].x][team1[1].x].status = temp.team2;
		}

		return field;
	}
};
