#include "qtcell.h"
#include "ui_cell.h"

QtCell::QtCell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtCell)
{
    ui->setupUi(this);

    QPalette pal(ui->pushButton->palette());

    ui->pushButton->setAutoFillBackground(true);
    ui->pushButton->setPalette(pal);
    ui->pushButton->setText("0");

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(setTeam()));
}

QtCell::QtCell(int point_, QWidget *parent) :
    QtCell(parent)
{
    ui->pushButton->setText(QString::number(point = point_));
}

QtCell::~QtCell()
{
    delete ui;
}

void QtCell::mousePressEvent(QMouseEvent *event)
{
//    QPalette pal;
//    ui->pushButton->setAutoFillBackground(true);


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
//    ui->pushButton->setPalette(pal);
}

void QtCell::setTeam(void)
{
    QPalette pal;

    //team1側の操作
    if(Ui::phase == Ui::team1_1){
        //それっぽい青(サファイアブルー)
        ui->pushButton->setStyleSheet("QPushButton {background-color: #0075c2}");
        pal.setColor(QPalette::Base, "#0073a8");
        this->status = this->pl1;
        Ui::phase = Ui::team1_2;
    }
    else if (Ui::phase == Ui::team1_2){
        //それっぽい青(エジプシャンブルー)
        ui->pushButton->setStyleSheet("QPushButton {background-color: #0075c2}");
        this->status = this->pl1;
        Ui::phase = Ui::team2_1;
    }
    else if(Ui::phase == Ui::team2_1){
        //それっぽい赤(トマトレッド)
        ui->pushButton->setStyleSheet("QPushButton {background-color: #ea5549}");
        this->status = this->pl2;
        Ui::phase = Ui::team2_2;
    }
    else if (Ui::phase == Ui::team2_2){
        //それっぽい赤(トマトレッド)
        ui->pushButton->setStyleSheet("QPushButton {background-color: #ea5549}");
        this->status = this->pl2;
        Ui::phase = Ui::team1_1;
    }


    ui->pushButton->setPalette(pal);
}
