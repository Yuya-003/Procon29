#include "gamefield.h"
#include "ui_gamefield.h"

void GameField::drawField(Field field)
{
//    QPainter painter(this);
//    painter.begin(this);

//    painter.setPen(Qt::black);
//    painter.setBrush(Qt::black);

//    int x = 0, y = 0;

//    for(int i = 0; i < map_y; i++){
//        for(int j = 0; j < map_x;j++){
//            painter.drawRect(x, y, CELL_SIZE, CELL_SIZE);
//            painter.drawText(x, y + CELL_SIZE, std::to_string(field.cells[i][j].point).c_str());
//            x += CELL_SIZE;
//        }
//        y += CELL_SIZE;
//    }
}

GameField::GameField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameField)
{
    ui->setupUi(this);

    this->map_x = 10;
    this->map_y = 8;
    this->turn = 60;
    this->pointTeam1 = 0;
    this->pointTeam2 = 0;

    drawField();
    Cell c;
    c.point = 0;
    Ui::fieldData.cells = std::vector<std::vector<Cell>>(map_y, std::vector<Cell>(map_x, c));
}

GameField::~GameField()
{
    delete ui;
}

void GameField::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);

    for(int i = 0; i <= map_y; i++)
        painter.drawLine(0, i*CELL_SIZE, map_x*CELL_SIZE, i*CELL_SIZE);

    for(int i = 0; i <= map_x;i++)
        painter.drawLine(i*CELL_SIZE, 0, i*CELL_SIZE, map_y*CELL_SIZE);

    //端の線を表示するために、10px分増やす
    this->setMinimumSize(map_x*CELL_SIZE + 10, map_y*CELL_SIZE + 10);
    this->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
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

//    if(Ui::phase == Ui::team1_1 || Ui::phase == Ui::team1_2)
//        fieldData.cells[gx][gy].status = fieldData.cells[0][0].team1;
//    else
//        fieldData.cells[gx][gy].status = fieldData.cells[0][0].team2;
}

