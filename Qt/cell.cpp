#include "cell.h"
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
