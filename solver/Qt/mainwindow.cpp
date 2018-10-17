#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->importQR, SIGNAL(triggered()), this, SLOT(importFromQR()));

    //connect(ui->gamefield, SIGNAL(clicked(QMouseEvent*)), ui->gamefield, SLOT(updateField(QMouseEvent*)));

    ui->label_turn->setText(QString::number(ui->gamefield->turn));
    ui->label_pointTeam1->setText(QString::number(ui->gamefield->pointTeam1));
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


    //FieldクラスからQtFieldクラスへ変換
    for (auto i = 0; i < Ui::fieldData.cells.size(); i++)
    {
        //ui->gamefield->qtField.push_back(std::vector<QtCell *>());
        for (auto j = 0; j < Ui::fieldData.cells[i].size(); j++)
        {
           // ui->gamefield->qtField[i][j]->point = Ui::fieldData.cells[i][j].point;
		}
	}

}
