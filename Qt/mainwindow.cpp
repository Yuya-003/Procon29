#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->setting,SIGNAL(triggered()),this,SLOT(openSettingDialog()));
}

void MainWindow::openSettingDialog()
{
    SettingDialog *dialog = new SettingDialog();
    dialog->exec();
    delete dialog;
}

MainWindow::~MainWindow()
{
    delete ui;
}
