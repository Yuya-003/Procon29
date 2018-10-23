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
    this->pointTeam1 = 0;
    this->pointTeam2 = 0;

    Cell c;
    c.point = 0;
    Ui::fieldData.cells =
        std::vector<std::vector<Cell>>(map_y, std::vector<Cell>(map_x, c));

    connect(this, SIGNAL(clicked(QMouseEvent*)), this, SLOT(updateField(QMouseEvent*)));
}


GameField::~GameField()
{
    delete ui;
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
    auto i = e->pos().x() / CELL_SIZE;
    auto j = e->pos().y() / CELL_SIZE;

    //phaseの更新、エージェントの位置(クリックしたところへ)の更新を行う
    //敵対するチームのcellをクリックしていない場合の処理
    if(Ui::phase == Ui::team1_1 && Ui::fieldData.cells[j][i].status != Ui::fieldData.cells[j][i].team2){
        Ui::fieldData.cells[j][i].status = Ui::fieldData.cells[0][0].team1;
        Ui::phase = Ui::team1_2;
        Ui::fieldData.team1[0] = Position(i, j);
    }
    else if(Ui::phase == Ui::team1_2 && Ui::fieldData.cells[j][i].status != Ui::fieldData.cells[j][i].team2){
        Ui::fieldData.cells[j][i].status = Ui::fieldData.cells[0][0].team1;
        Ui::phase = Ui::team2_1;
        Ui::fieldData.team1[1] = Position(i, j);
    }
    else if(Ui::phase == Ui::team2_1 && Ui::fieldData.cells[j][i].status != Ui::fieldData.cells[j][i].team1){
        Ui::fieldData.cells[j][i].status = Ui::fieldData.cells[0][0].team2;
        Ui::phase = Ui::team2_2;
        Ui::fieldData.team2[0] = Position(i, j);
    }
    else if(Ui::phase == Ui::team2_2 && Ui::fieldData.cells[j][i].status != Ui::fieldData.cells[j][i].team1){
        Ui::fieldData.cells[j][i].status = Ui::fieldData.cells[0][0].team2;
        Ui::phase = Ui::team1_1;
        Ui::fieldData.team2[1] = Position(i, j);
        //ターン変更のシグナル送信
        emit changedTurn(--turn);
    }
    else{ //敵対するチームのcellをクリックした場合の処理(→相手チームのcellの除去)


    }

    //再描画(paintEventの呼び出し)
    this->update();
}
