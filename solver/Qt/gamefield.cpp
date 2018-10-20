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
                painter.setBrush(QBrush("#0075c2"));
			//いい感じの赤色
            else if(Ui::fieldData.cells[j][i].status == Ui::fieldData.cells[j][i].team2)
                painter.setBrush(QBrush("#ea5549"));
			//真っ白
            else
                painter.setBrush(QBrush("#ffffff"));

            int x = i * CELL_SIZE;
            int y = j * CELL_SIZE;
            painter.drawRect(QRect(x,y,CELL_SIZE, CELL_SIZE));
            painter.fillRect(QRect(x,y,CELL_SIZE, CELL_SIZE), painter.brush());
        }
    }

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

void GameField::changeMapSize(int x, int y)
{
    this->map_x = x;
    this->map_y = y;
}

void GameField::changeTurn(int turn)
{
    this->turn = turn;
}

void GameField::updateField(QMouseEvent *e)
{
    //phaseの更新を行う
    if(Ui::phase == Ui::team1_1)
        Ui::phase = Ui::team1_2;
    else if(Ui::phase == Ui::team1_2)
        Ui::phase = Ui::team2_1;
    else if(Ui::phase == Ui::team2_1)
        Ui::phase = Ui::team2_2;
    else
        Ui::phase = Ui::team1_1;

    //Field情報の更新
    auto j = e->pos().y() / CELL_SIZE;
    auto i = e->pos().x() / CELL_SIZE;

    if(Ui::phase == Ui::team1_1 || Ui::phase == Ui::team1_2)
        Ui::fieldData.cells[j][i].status = Ui::fieldData.cells[0][0].team1;
    else
        Ui::fieldData.cells[j][i].status = Ui::fieldData.cells[0][0].team2;

    //再描画
    this->update();
}