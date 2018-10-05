#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->setting,SIGNAL(triggered()),this,SLOT(openSettingDialog()));
    connect(ui->importQR, SIGNAL(triggered()), this, SLOT(importFromQR()));

    ui->label_turn->setText(QString::number(ui->gamefield->turn));
    ui->label_points->setText(QString::number(ui->gamefield->point));
}

void MainWindow::openSettingDialog()
{
    SettingDialog *dialog = new SettingDialog();

    connect(dialog, SIGNAL(sendMapSize(int,int)), ui->gamefield, SLOT(changeMapSize(int,int)));
    connect(dialog, SIGNAL(sendTurn(int)), ui->gamefield, SLOT(changeTurn(int)));
    connect(dialog, SIGNAL(requestInit()), ui->gamefield, SLOT(initField()));

    dialog->changeMapSize(ui->gamefield->map_x, ui->gamefield->map_y);
    dialog->changeTurn(ui->gamefield->turn);
    dialog->exec();
    delete dialog;

    ui->label_turn->setText(QString::number(ui->gamefield->turn));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::importFromQR()
{

}

