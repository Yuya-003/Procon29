#include "gamefield.h"
#include "ui_gamefield.h"

GameField::GameField(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::GameField)
{
    ui->setupUi(this);

    this->map_x = 10;
    this->map_y = 8;
    this->turn = 60;
    this->pointTeam1 = 0;
    this->pointTeam2 = 0;


    this->grid = new QGridLayout(this);
    this->grid->setSpacing(0);
    this->grid->setMargin(0);


    auto *qtcell = new QtCell();
    //connect(qtcell, SIGNAL(clicked()), this, SLOT(updateField()));

    for(auto row : this->qtField){
        for(auto cell : row){
            //connect(cell, SIGNAL(clicked(QMouseEvent*)), this, SLOT(updateField(QMouseEvent*)));
        }
    }
    delete qtcell;

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

void GameField::updateField(QMouseEvent *e)
{
    auto cellSize = 50;
    auto point = e->pos();
    auto gx = point.x() / cellSize;
    auto gy = point.y() / cellSize;

    if(Ui::phase == Ui::team1_1 || Ui::phase == Ui::team1_2)
        Ui::fieldData.cells[gx][gy].status = Ui::fieldData.cells[0][0].team1;
    else
        Ui::fieldData.cells[gx][gy].status = Ui::fieldData.cells[0][0].team2;
}

