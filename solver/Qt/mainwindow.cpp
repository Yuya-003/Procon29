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

    //QtCell内mousePressEvent と QtCell::QMouseEvent をconnect
    //QtCell *qtcell = new QtCell();
    for(auto row : ui->gamefield->qtField){
        for(auto cell : row){
            connect(cell, SIGNAL(m_mouseClickEvent(QMouseEvent*)), cell, SLOT(setTeam(QMouseEvent*)));
        }
    }

    //delete qtcell;
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
    //QRコードからデータを受け取る
	Field field = Field();

    //FieldクラスからQtFieldクラスへ変換

	for (auto i = 0; i < field.cells.size(); i++) {

		ui->gamefield->qtField.push_back(std::vector<QtCell *>());

		for (auto j = 0; j < field.cells[i].size(); j++) {
			ui->gamefield->qtField[i][j]->point = field.cells[i][j].point;
		}
	}


}