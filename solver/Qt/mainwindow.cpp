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
}
