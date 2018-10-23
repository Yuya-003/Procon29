#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->importQR, SIGNAL(triggered()), this, SLOT(importFromQR()));
    connect(ui->gamefield, SIGNAL(changedTurn(int)), this, SLOT(changeTurn(int)));

    ui->label_turn->setText(QString::number(ui->gamefield->turn));

    //各チームの得点を表示
    ui->label_pointTeam1->setStyleSheet(QString("color:") + COLOR_BLUE);
    ui->label_pointTeam1->setText(QString::number(ui->gamefield->pointTeam1));

    ui->label_pointTeam2->setStyleSheet(QString("color:") + COLOR_ORANGE);
    ui->label_pointTeam2->setText(QString::number(ui->gamefield->pointTeam2));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::importFromQR()
{
    //QRコードからデータを受け取る
    Ui::fieldData = Field();
	Cell c;
	c.point = 1;

	Ui::fieldData.cells = std::vector<std::vector<Cell>>(4, std::vector<Cell>(5, c));

    ui->gamefield->map_x = Ui::fieldData.cells[0].size();
    ui->gamefield->map_y = Ui::fieldData.cells.size();

    //fieldの更新
    this->ui->gamefield->update();
    this->update();
}

void MainWindow::changeTurn(int turn)
{
    ui->label_turn->setText(QString::number(turn));
   // ui->gamefield->update();
}

void MainWindow::changeScore(Field field)
{
    ui->label_pointTeam1->setText(QString::number(field.calcScore(Cell::team1)));
    ui->label_pointTeam2->setText(QString::number(field.calcScore(Cell::team2)));
}
