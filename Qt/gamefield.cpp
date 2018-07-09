#include "gamefield.h"
#include "ui_gamefield.h"

GameField::GameField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameField)
{
    ui->setupUi(this);

    mt.seed(std::random_device()());

    this->map_x = 10;
    this->map_y = 8;
    this->turn = 60;

    initField();
}

GameField::~GameField()
{
    delete ui;
}

void GameField::initField()
{
    delete ui->frame;
    ui->frame = new QFrame(this);
    ui->horizontalLayout->addWidget(ui->frame);

    QGridLayout *gridlayout = new QGridLayout(ui->frame);
    gridlayout->setSpacing(0);
    gridlayout->setMargin(0);

    std::uniform_int_distribution<> rnd(1, 16);

    for(int i = 0; i < this->map_y; i++){
        for(int j = 0; j < this->map_x; j++){
            Cell *cell = new Cell(rnd(mt), ui->frame);
            gridlayout->addWidget(cell, i, j);
        }
    }

    ui->frame->setLayout(gridlayout);
    ui->frame->setFrameShape(QFrame::Box);
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
