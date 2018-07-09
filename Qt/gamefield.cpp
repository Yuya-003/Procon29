#include "gamefield.h"
#include "ui_gamefield.h"

GameField::GameField(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::GameField)
{
    ui->setupUi(this);

    mt.seed(std::random_device()());

    this->map_x = 10;
    this->map_y = 8;
    this->turn = 60;

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

    std::uniform_int_distribution<> rnd(1, 16);

    for(int i = 0; i < this->map_y; i++){
        std::vector<Cell*> row;
        for(int j = 0; j < this->map_x; j++){
            Cell *cell = new Cell(rnd(mt), this);
            this->grid->addWidget(cell, i, j);
            row.push_back(cell);
        }
        this->field.push_back(row);
    }

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
