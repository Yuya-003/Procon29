#include "gamefield.h"
#include "ui_gamefield.h"

GameField::GameField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameField)
{
    ui->setupUi(this);

    this->map_x = 10;
    this->map_y = 8;
    this->pointTeam1 = 0;
    this->pointTeam2 = 0;
    this->turn = 0;


    connect(this, SIGNAL(clicked(QMouseEvent*)), this, SLOT(updateField(QMouseEvent*)));

    /*以下は、テスト用のコード*/
    Cell c;
    c.point = 0;
    Ui::fieldData.cells =
        std::vector<std::vector<Cell>>(map_y, std::vector<Cell>(map_x, c));

    Ui::fieldData.team1[0] = Position(1,0);
    Ui::fieldData.team1[1] = Position(1,4);

    Ui::fieldData.team2[0] = Position(5,0);
    Ui::fieldData.team2[1] = Position(5,4);
    /*ここまで*/
}


GameField::~GameField()
{
    delete ui;
}


bool GameField::isPlayerAround(Ui::Phase phase, Position clickedOnGrid)
{
    //phaseに合わせた、プレイヤーの情報の取得(名前空間内を使うクソ)
    auto pl = (phase == Ui::team1_1) ? (Ui::fieldData.team1[0])
            : (phase == Ui::team1_2) ? (Ui::fieldData.team1[1])
            : (phase == Ui::team2_1) ? (Ui::fieldData.team2[0])
            :                          (Ui::fieldData.team2[1]);


    //クリックされたとこの周りの座標が、範囲外ならとりまfalse
    if(clickedOnGrid.x < 0  || clickedOnGrid.y  < 0 ||
       clickedOnGrid.x > map_x || clickedOnGrid.y > map_y) return false;

    //ノルム無限大が1でtrueを返す
    // ex). (1, 1) と (5, 3)についてのノルム無限大は、4(どちらか値の大きい方を取る)
    auto dx = abs(pl.x - clickedOnGrid.x);
    auto dy = abs(pl.y - clickedOnGrid.y);

    if(dx >= dy && dx == 1) return true;
    if(dy >= dx && dy == 1) return true;
    else                    return false;
}



void GameField::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Meiryo UI", FONT_SIZE, FONT_WIDTH));

    //マス目の色をチームに合わせて表示
    for(int i = 0; i < map_x; i++){
        for(int j = 0;j < map_y; j++){
			//いい感じの青色
            if(Ui::fieldData.cells[j][i].status == Ui::fieldData.cells[j][i].team1)
                painter.setBrush(QBrush(COLOR_LIGHT_BLUE));
			//いい感じの赤色
            else if(Ui::fieldData.cells[j][i].status == Ui::fieldData.cells[j][i].team2)
                painter.setBrush(QBrush(COLOR_LIGHT_ORANGE));
			//真っ白
            else
                painter.setBrush(QBrush(Qt::white));


            //Rectangleを描画
            int x = i * CELL_SIZE;
            int y = j * CELL_SIZE;
            painter.drawRect(QRect(x,y,CELL_SIZE, CELL_SIZE));
            painter.fillRect(QRect(x,y,CELL_SIZE, CELL_SIZE), painter.brush());
        }
    }

    //エージェントの位置にellipseを表示
    auto tmpTeam = Ui::fieldData.team1;
    painter.setBrush(QBrush(COLOR_BLUE));
    painter.drawEllipse(QRect(tmpTeam[0].x*CELL_SIZE, tmpTeam[0].y*CELL_SIZE,CELL_SIZE, CELL_SIZE));
    painter.drawEllipse(QRect(tmpTeam[1].x*CELL_SIZE, tmpTeam[1].y*CELL_SIZE,CELL_SIZE, CELL_SIZE));

    tmpTeam = Ui::fieldData.team2;
    painter.setBrush(QBrush(COLOR_ORANGE));
    painter.drawEllipse(QRect(tmpTeam[0].x*CELL_SIZE, tmpTeam[0].y*CELL_SIZE,CELL_SIZE, CELL_SIZE));
    painter.drawEllipse(QRect(tmpTeam[1].x*CELL_SIZE, tmpTeam[1].y*CELL_SIZE,CELL_SIZE, CELL_SIZE));

    //グリッドの描画
    painter.setBrush(Qt::black);
    //縦線の描画
    for(int i = 0; i <= map_y; i++)
        painter.drawLine(0, i*CELL_SIZE, map_x*CELL_SIZE, i*CELL_SIZE);
    //横線の描画
    for(int i = 0; i <= map_x;i++)
        painter.drawLine(i*CELL_SIZE, 0, i*CELL_SIZE, map_y*CELL_SIZE);

    //端の線を表示するために、10px分増やす
    this->setMinimumSize(map_x*CELL_SIZE + 10, map_y*CELL_SIZE + 10);
    //いい感じにQWidgetのサイズを処理
    this->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    //得点の表示
    for(int i = 0; i < map_x; i++){
        for(int j = 0;j < map_y; j++){
            int x = i * CELL_SIZE + FONT_SIZE * 0.6;  //0.6をかけると、文字が真ん中にくる
            int y = j * CELL_SIZE + CELL_SIZE - FONT_SIZE / 2;  //2で割ったのを引くと、いい感じになる
            // X軸がi、Y軸がj のため、縦の[j]からアクセス
            painter.drawText(x, y, QString::number(Ui::fieldData.cells[j][i].point));
        }
    }

}


void GameField::updateField(QMouseEvent *e)
{
    auto _x = e->pos().x() / CELL_SIZE;
    auto _y = e->pos().y() / CELL_SIZE;

    //クリックされた場所が範囲外なら、無視
    if(_x >= map_x || _y >= map_y) return;

    //phaseの更新、エージェントの位置(クリックしたところへ)の更新を行う
    //敵対するチームのcellをクリックしていない場合の処理
    if(isPlayerAround(Ui::phase, Position(_x,_y))){
        if(Ui::phase == Ui::team1_1 && Ui::fieldData.cells[_y][_x].status != Ui::fieldData.cells[_y][_x].team2){
            Ui::fieldData.cells[_y][_x].status = Ui::fieldData.cells[0][0].team1;
            Ui::phase = Ui::team1_2;
            emit changedPhase(Ui::phase);
            Ui::fieldData.team1[0] = Position(_x, _y);
        }
        else if(Ui::phase == Ui::team1_2 && Ui::fieldData.cells[_y][_x].status != Ui::fieldData.cells[_y][_x].team2){
            Ui::fieldData.cells[_y][_x].status = Ui::fieldData.cells[0][0].team1;
            Ui::phase = Ui::team2_1;
            emit changedPhase(Ui::phase);
            Ui::fieldData.team1[1] = Position(_x, _y);
        }
        else if(Ui::phase == Ui::team2_1 && Ui::fieldData.cells[_y][_x].status != Ui::fieldData.cells[_y][_x].team1){
            Ui::fieldData.cells[_y][_x].status = Ui::fieldData.cells[0][0].team2;
            Ui::phase = Ui::team2_2;
            emit changedPhase(Ui::phase);
            Ui::fieldData.team2[0] = Position(_x, _y);
        }
        else if(Ui::phase == Ui::team2_2 && Ui::fieldData.cells[_y][_x].status != Ui::fieldData.cells[_y][_x].team1){
            Ui::fieldData.cells[_y][_x].status = Ui::fieldData.cells[0][0].team2;
            Ui::phase = Ui::team1_1;
            emit changedPhase(Ui::phase);
            Ui::fieldData.team2[1] = Position(_x, _y);
            //ターン変更のシグナル送信
            emit changedTurn(++turn);
        }
        //敵対するチームのcellをクリックした場合の処理(→相手チームのcellの除去)
        else if(isPlayerAround(Ui::phase, Position(_x, _y))){
            Ui::fieldData.cells[_y][_x].status = Ui::fieldData.cells[_y][_x].none;

            //三項演算子を使って、phaseの切り替え
            Ui::phase = (Ui::phase == Ui::team1_1) ? (Ui::team1_2)
                      : (Ui::phase == Ui::team1_2) ? (Ui::team2_1)
                      : (Ui::phase == Ui::team2_1) ? (Ui::team2_2)
                      :                              (Ui::team1_1);
            emit changedPhase(Ui::phase);
        }
    }

    //マウスのクリックによってfieldの状態が変わった際のシグナル送信
    emit changedField(Ui::fieldData);

    //再描画(paintEventの呼び出し)
    this->update();
}
