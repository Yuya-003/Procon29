#include "gamefield.h"
#include "ui_gamefield.h"

GameField::GameField(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::GameField)
{
    ui->setupUi(this);

    //乱数のシード値を設定
    mt.seed(std::random_device()());

    this->map_x = 10;
    this->map_y = 8;
    this->turn = 60;
	this->point = 0;


    this->grid = new QGridLayout(this);
    this->grid->setSpacing(0);
    this->grid->setMargin(0);
    initField();
}

GameField::~GameField()
{
    delete ui;
}

void GameField::initField()
{
    for(auto row:this->field){
        for(auto cell:row){
            this->grid->removeWidget(cell);
            delete cell;
        }
    }
    this->field.clear();

    //正の点数(1～16)を生成する乱数
    std::uniform_int_distribution<> plusRnd(1, 16);
	//負の点数(-16～0)を生成する乱数
    std::uniform_int_distribution<> minusRnd(-16, 0);
	//正負を決める乱数(正:負 = 9:1)
	std::uniform_int_distribution<> seihu(1, 10);
	//対称となる軸の方向(水平 or 垂直)を決める乱数
	std::uniform_int_distribution<> symmetry(1, 2);

	std::vector<std::vector<int>> glidData;

	//水平方向の中央線で配置
	if (true) {

        for (int i = 0; i < map_y / 2; i++) {
			std::vector<QtCell*> row;
			std::vector<int> dataRow;

			for (auto j = 0; j < this->map_x; j++) {

				if (seihu(mt) == 1) {			//負の点数
					int data = minusRnd(mt);
					QtCell *cell = new QtCell(data, this);
					this->grid->addWidget(cell, i, j);
					row.push_back(cell);
					dataRow.push_back(data);
				}
				else {							//正の点数
					int data = plusRnd(mt);
					QtCell *cell = new QtCell(data, this);
					this->grid->addWidget(cell, i, j);
					row.push_back(cell);
					dataRow.push_back(data);
				}
			}
			this->field.push_back(row);
			glidData.push_back(dataRow);
		}

		//(map_y % 2 == 0) ? 0 : 1 … map_y
        for (int i = map_y; i < (map_y / 2) + 1 +  (map_y % 2 == 0) ? 0 : 1; i--) {
			std::vector<QtCell*> row;
			for (int j = 0; j < this->map_x; j++) {

                QtCell *cell = new QtCell(glidData[-i + map_y][j], this);
				this->grid->addWidget(cell, i, j);
				row.push_back(cell);

			}
			this->field.push_back(row);
		}
		
	}
	else {
		for (int i = 0; i < this->map_y; i++) {
			std::vector<QtCell*> row;
			std::vector<int> dataRow;

			for (int j = 0; j < this->map_x / 2; j++) {

				if (seihu(mt) == 1) {			//負の点数
					int data = minusRnd(mt);
					QtCell *cell = new QtCell(data, this);
					this->grid->addWidget(cell, i, j);
					row.push_back(cell);
					dataRow.push_back(data);
				}
				else {							//正の点数
					int data = plusRnd(mt);
					QtCell *cell = new QtCell(data, this);
					this->grid->addWidget(cell, i, j);
					row.push_back(cell);
					dataRow.push_back(data);
				}
			}
			this->field.push_back(row);
			glidData.push_back(dataRow);
		}

        //(map_y % 2 == 0) ? 0 : 1 …

        for (int i = this->map_y; i < (map_y / 2) + 1 + (map_y % 2 == 0) ? 0 : 1; i--) {
			std::vector<QtCell*> row;
			for (int j = 0; j < this->map_x; j++) {

                QtCell *cell = new QtCell(glidData[-i + map_y][j], this);
				this->grid->addWidget(cell, i, j);
				row.push_back(cell);

			}
			this->field.push_back(row);
		}
    }
	//垂直方向の中央線で配置


    this->field.shrink_to_fit();
}

void GameField::changeMapSize(int x, int y)
{
    this->map_x = x;
    this->map_y = y;
}

void GameField::changeTurn(int turn)
{
    this->turn = turn;
}
