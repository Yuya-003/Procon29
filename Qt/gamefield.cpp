#include "gamefield.h"
#include "ui_gamefield.h"

GameField::GameField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameField)
{
    ui->setupUi(this);

    this->map_x = 10;
    this->map_y = 8;
    this->turn = 60;
}

GameField::~GameField()
{
    delete ui;
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
