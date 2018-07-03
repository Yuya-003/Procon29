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

    initField();
}

GameField::~GameField()
{
    delete ui;
}

void GameField::initField()
{
    delete ui->widget;
    ui->widget = new QWidget(this);
    ui->horizontalLayout->addWidget(ui->widget);

    QGridLayout *gridlayout = new QGridLayout(ui->widget);
    int count = 1;
    for(int i = 0; i < this->map_y; i++){
        for(int j = 0; j < this->map_x; j++){
            QLabel *label = new QLabel(QString::number(count++), ui->widget);
            label->setFont(QFont("メイリオ", 20, QFont::Normal, false));
            label->setAlignment(Qt::AlignCenter);
            QPalette pal(label->palette());
            pal.setColor(QPalette::Background, Qt::white);
            label->setAutoFillBackground(true);
            label->setPalette(pal);
            gridlayout->addWidget(label, i, j);
        }
    }

    ui->widget->setLayout(gridlayout);
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
