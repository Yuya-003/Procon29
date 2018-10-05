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


    for(auto row:this->qtField){
        for(auto cell : row){
            this->grid->removeWidget(cell);
            delete cell;
        }
    }
    this->qtField.clear();





    for (auto i = 0; i < map_y ; i++) {

        std::vector<QtCell *> row;

        for (auto j = 0; j < this->map_x; j++) {

            //とりあえず0で初期化
            QtCell *cell = new QtCell(0, this);
            row.push_back(cell);
            this->grid->addWidget(cell, i, j);

        }

        this->qtField.push_back(row);
    }

    this->qtField.shrink_to_fit();
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
