#include "gamefield.h"
#include "ui_gamefield.h"

GameField::GameField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameField)
{
    ui->setupUi(this);

    this->pointTeam1 = 0;
    this->pointTeam2 = 0;
    this->turn = 0;
    this->isReadyTurn = true;

    //Fieldをてきとーに初期化
    Field f;
    Cell c;
    c.point = 0;
    f.cells = std::vector<std::vector<Cell>>(8, std::vector<Cell>(10, c));
    this->field = f;

    this->field.team1[0] = Position(1,0);
    this->field.team1[1] = Position(1,4);

    this->field.team2[0] = Position(5,0);
    this->field.team2[1] = Position(5,4);
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
    for(int i = 0; i < mapX(); i++){
        for(int j = 0;j < mapY(); j++){
			//いい感じの青色
            if(this->field.cells[j][i].status == Cell::team1)
                painter.setBrush(QBrush(COLOR_LIGHT_BLUE));
			//いい感じの赤色
            else if(this->field.cells[j][i].status == Cell::team2)
                painter.setBrush(QBrush(COLOR_LIGHT_RED));
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
    if(!isReadyTurn){
        auto team1 = this->field.team1;
        auto team2 = this->field.team2;

        painter.setBrush(QBrush(COLOR_BLUE));
        painter.drawEllipse(QRect(team1[0].x*CELL_SIZE, team1[0].y*CELL_SIZE,CELL_SIZE, CELL_SIZE));
        painter.drawEllipse(QRect(team1[1].x*CELL_SIZE, team1[1].y*CELL_SIZE,CELL_SIZE, CELL_SIZE));
        this->field.cells[team1[0].y][team1[0].x].status = Cell::team1;
        this->field.cells[team1[1].y][team1[1].x].status = Cell::team1;

        painter.setBrush(QBrush(COLOR_RED));
        painter.drawEllipse(QRect(team2[0].x*CELL_SIZE, team2[0].y*CELL_SIZE,CELL_SIZE, CELL_SIZE));
        painter.drawEllipse(QRect(team2[1].x*CELL_SIZE, team2[1].y*CELL_SIZE,CELL_SIZE, CELL_SIZE));
        this->field.cells[team2[0].y][team2[0].x].status = Cell::team2;
        this->field.cells[team2[1].y][team2[1].x].status = Cell::team2;
    }

    //グリッドの描画
    painter.setBrush(Qt::black);
    //縦線の描画
    for(int i = 0; i <= mapY(); i++)
        painter.drawLine(0, i*CELL_SIZE, mapX()*CELL_SIZE, i*CELL_SIZE);
    //横線の描画
    for(int i = 0; i <= mapX();i++)
        painter.drawLine(i*CELL_SIZE, 0, i*CELL_SIZE, mapY()*CELL_SIZE);

    //端の線を表示するために、10px分増やす
    this->setMinimumSize(mapX()*CELL_SIZE + 10, mapY()*CELL_SIZE + 10);
    //いい感じにQWidgetのサイズを処理
    this->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    //得点の表示
    for(int i = 0; i < mapX(); i++){
        for(int j = 0;j < mapY(); j++){
            int x = i * CELL_SIZE + FONT_SIZE * 0.6;  //0.6をかけると、文字が真ん中にくる
            int y = j * CELL_SIZE + CELL_SIZE - FONT_SIZE / 2;  //2で割ったのを引くと、いい感じになる
            // X軸がi、Y軸がj のため、縦の[j]からアクセス
            painter.drawText(x, y, QString::number(this->field.cells[j][i].point));
        }
    }

}

