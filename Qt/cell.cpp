#include "cell.h"
#include "ui_cell.h"

Cell::Cell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cell)
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

Cell::Cell(const QString &text, QWidget *parent) :
    Cell(parent)
{
    ui->label->setText(text);
}

Cell::~Cell()
{
    delete ui;
}
