#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->importQR, SIGNAL(triggered()), this, SLOT(importFromQR()));
    connect(ui->gamefield, SIGNAL(changedTurn(int)), this, SLOT(changeTurn(int)));
    connect(ui->gamefield, SIGNAL(changedPhase(Ui::Phase)), this, SLOT(changeStatusBar(Ui::Phase)));

    //ターン数の表示
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
    update();
}

void MainWindow::changeScore(Field field)
{
    ui->label_pointTeam1->setText(QString::number(field.calcScore(Cell::team1)));
    ui->label_pointTeam2->setText(QString::number(field.calcScore(Cell::team2)));
}

void MainWindow::changeStatusBar(Ui::Phase phase)
{
    if(phase == Ui::team1_1)
        ui->statusBar->showMessage(QString::fromLocal8Bit("先攻チーム、エージェント1人目の行動を入力してください。"));
    if(phase == Ui::team1_2)
        ui->statusBar->showMessage(QString::fromLocal8Bit("先攻チーム、エージェント2人目の行動を入力してください。"));
    if(phase == Ui::team2_1)
        ui->statusBar->showMessage(QString::fromLocal8Bit("後攻チーム、エージェント1人目の行動を入力してください。"));
    if(phase == Ui::team2_2)
        ui->statusBar->showMessage(QString::fromLocal8Bit("後攻チーム、エージェント2人目の行動を入力してください。"));

    update();
}
