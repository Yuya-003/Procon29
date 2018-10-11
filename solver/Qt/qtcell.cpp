#include "qtcell.h"
#include "ui_cell.h"

QtCell::QtCell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtCell)
{
    ui->setupUi(this);

    ui->label->setFont(QFont("メイリオ", 20, QFont::Normal, false));
    ui->label->setFrameShape(QFrame::Box);
    ui->label->setMinimumSize(50,50);
    ui->label->setAlignment(Qt::AlignCenter);

    QPalette pal(ui->label->palette());
    pal.setColor(QPalette::Background, Qt::white);
    ui->label->setAutoFillBackground(true);
    ui->label->setPalette(pal);
}

QtCell::QtCell(int point_, QWidget *parent) :
    QtCell(parent)
{
    ui->label->setText(QString::number(point = point_));
}

QtCell::~QtCell()
{
    delete ui;
}

void QtCell::mousePressEvent(QMouseEvent *event)
{
    emit m_mouseClickEvent(event);
//    QPalette pal;
//    ui->label->setAutoFillBackground(true);

//    if(event->button() == Qt::LeftButton){

//         //team1側の操作
//        if(Ui::phase == Ui::team1_1){
//            //それっぽい青(エジプシャンブルー)
//             pal.setColor(QPalette::Background, "#0073a8");
//             this->status = this->pl1;
//             Ui::phase = Ui::team1_2;
//        }
//        else if (Ui::phase == Ui::team1_2){
//            //それっぽい青(エジプシャンブルー)
//            pal.setColor(QPalette::Background, "#0073a8");
//            this->status = this->pl1;
//            Ui::phase = Ui::team2_1;
//        }
//        else if(Ui::phase == Ui::team2_1){
//            //それっぽい赤(トマトレッド)
//             pal.setColor(QPalette::Background, "#ea5549");
//             this->status = this->pl2;
//             Ui::phase = Ui::team2_2;
//        }
//        else if (Ui::phase == Ui::team2_2){
//            //それっぽい赤(トマトレッド)
//            pal.setColor(QPalette::Background, "#ea5549");
//            this->status = this->pl2;
//            Ui::phase = Ui::team1_1;
//        }

//    }
//    ui->label->setPalette(pal);
}

void QtCell::setTeam(QMouseEvent *event)
{
    QPalette pal;
    ui->label->setAutoFillBackground(true);

    if(event->button() == Qt::LeftButton){

         //team1側の操作
        if(Ui::phase == Ui::team1_1){
            //それっぽい青(エジプシャンブルー)
             pal.setColor(QPalette::Background, "#0073a8");
             this->status = this->pl1;
             Ui::phase = Ui::team1_2;
        }
        else if (Ui::phase == Ui::team1_2){
            //それっぽい青(エジプシャンブルー)
            pal.setColor(QPalette::Background, "#0073a8");
            this->status = this->pl1;
            Ui::phase = Ui::team2_1;
        }
        else if(Ui::phase == Ui::team2_1){
            //それっぽい赤(トマトレッド)
             pal.setColor(QPalette::Background, "#ea5549");
             this->status = this->pl2;
             Ui::phase = Ui::team2_2;
        }
        else if (Ui::phase == Ui::team2_2){
            //それっぽい赤(トマトレッド)
            pal.setColor(QPalette::Background, "#ea5549");
            this->status = this->pl2;
            Ui::phase = Ui::team1_1;
        }

    }
    ui->label->setPalette(pal);
}
