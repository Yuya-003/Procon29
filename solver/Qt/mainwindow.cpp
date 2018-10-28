#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->importQR, SIGNAL(triggered()), this, SLOT(importFromQR()));
    connect(ui->gamefield, SIGNAL(clicked(QMouseEvent*)), this, SLOT(updateField(QMouseEvent*)));

    //ターン数の表示
    ui->label_turn->setText(QString::number(ui->gamefield->turn));
    //各チームの得点を表示、ラジオボタンの色を設定
    ui->label_pointTeam1->setStyleSheet(QString("color:") + COLOR_BLUE);
    ui->radioButton_Team1->setStyleSheet(QString("color:") + COLOR_BLUE);
    ui->label_pointTeam1->setText(QString::number(ui->gamefield->pointTeam1));

    ui->label_pointTeam2->setStyleSheet(QString("color:") + COLOR_RED);
    ui->radioButton_Team2->setStyleSheet(QString("color:") + COLOR_RED);
    ui->label_pointTeam2->setText(QString::number(ui->gamefield->pointTeam2));

    //準備中のターンは、すこし特殊な動きしたい
    isReadyTurn = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::isPlayerArround(Position player, Position clickedOnGrid)
{
    //クリックされたとこの周りの座標が、範囲外ならとりまfalse
    if(clickedOnGrid.x < 0  || clickedOnGrid.y  < 0 ||
       clickedOnGrid.x > ui->gamefield->mapX() || clickedOnGrid.y > ui->gamefield->mapY()) return false;

    //ノルム無限大が1でtrueを返す関数
    // ex). (1, 1) と (5, 3)についてのノルム無限大は、4(それぞれの成分の差の大きい方を取る、4と2なので、)
    auto dx = abs(player.x - clickedOnGrid.x);
    auto dy = abs(player.y - clickedOnGrid.y);

    if(dx >= dy && dx == 1) return true;
    if(dy >= dx && dy == 1) return true;
    else                    return false;
}

void MainWindow::importFromQR()
{
    //QRコードからデータを受け取る
    ui->gamefield->field = GetQRContent();

    //fieldの更新
    this->ui->gamefield->update();
    this->update();
}

void MainWindow::updateField(QMouseEvent *e)
{
    auto _x = e->pos().x() / CELL_SIZE;
    auto _y = e->pos().y() / CELL_SIZE;

    //クリックされた場所が範囲外なら、無視
    if(_x >= ui->gamefield->mapX() || _y >= ui->gamefield->mapY()) return;
    if(_x < 0 || _y < 0) return;

    //teamの判断(ラジオボタンを使う)
    Cell::Status team = (ui->radioButton_Team1->isChecked()) ? (Cell::team1)
                      : (ui->radioButton_Team2->isChecked()) ? (Cell::team2)
                      :                                        (Cell::none);

    //本番開始前の準備(エージェントの初期位置設定)
    static bool turn1_1 = true;
    static bool turn1_2 = true;
    static bool turn2_1 = true;
    static bool turn2_2 = true;

    if(team == Cell::team1){
        if(turn1_1){
            ui->gamefield->field.team1[0] = Position(_x, _y);
            turn1_1 = false;
        }else if(turn1_2){
            ui->gamefield->field.team1[1] = Position(_x, _y);
            turn1_2 = false;
        }
    }
    if(team == Cell::team2){
        if(turn2_1){
            ui->gamefield->field.team2[0] = Position(_x, _y);
            turn2_1 = false;
        }else if(turn2_2){
            ui->gamefield->field.team2[1] = Position(_x, _y);
            turn2_2 = false;
        }
    }

    if(!turn1_1 && !turn1_2 && !turn2_1 && !turn2_2)
        ui->gamefield->isReadyTurn = false;


    //エージェントの位置の更新・クリックした場所のStatus替え
    if(team == Cell::team1){
        if(isPlayerArround(ui->gamefield->field.team1[0], Position(_x, _y))){
            ui->gamefield->field.team1[0] = Position(_x, _y);

            if(ui->gamefield->field.cells[_y][_x].status != Cell::team2)
                ui->gamefield->field.cells[_y][_x].status = Cell::team1;
            else
                ui->gamefield->field.cells[_y][_x].status = Cell::none;
        }
        else if(isPlayerArround(ui->gamefield->field.team1[1], Position(_x, _y))){
            ui->gamefield->field.team1[1] = Position(_x, _y);

            if(ui->gamefield->field.cells[_y][_x].status != Cell::team2)
                ui->gamefield->field.cells[_y][_x].status = Cell::team1;
            else
                ui->gamefield->field.cells[_y][_x].status = Cell::none;
        }

    }
    else if(team == Cell::team2){
        if(isPlayerArround(ui->gamefield->field.team2[0], Position(_x, _y))){
            ui->gamefield->field.team2[0] = Position(_x, _y);

            if(ui->gamefield->field.cells[_y][_x].status != Cell::team1)
                ui->gamefield->field.cells[_y][_x].status = Cell::team2;
            else
                ui->gamefield->field.cells[_y][_x].status = Cell::none;
        }
        else if(isPlayerArround(ui->gamefield->field.team2[1], Position(_x, _y))){
            ui->gamefield->field.team2[1] = Position(_x, _y);

            if(ui->gamefield->field.cells[_y][_x].status != Cell::team1)
                ui->gamefield->field.cells[_y][_x].status = Cell::team2;
            else
                ui->gamefield->field.cells[_y][_x].status = Cell::none;
        }

    }

    //マウスのクリックによってfieldの状態が変わった際のシグナル送信
    emit changedField(ui->gamefield->field);

    //再描画(paintEventの呼び出し)
    ui->gamefield->update();
}

void MainWindow::changeScore()
{
    ui->label_pointTeam1->setText(QString::number(ui->gamefield->field.calcScore(Cell::team1)));
    ui->label_pointTeam2->setText(QString::number(ui->gamefield->field.calcScore(Cell::team2)));
}
