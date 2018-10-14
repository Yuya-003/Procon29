#ifndef CELL_H
#define CELL_H

#include <QWidget>
#include <QMouseEvent>
#include <structure/Field.hpp>

namespace Ui {
class QtCell;

//専攻チームの1人目、2人目、後攻チームの1人目、2人目
enum Phase{
    team1_1, team1_2, team2_1, team2_2
};

static Phase phase = team1_1;
static Field fieldData;
}

class QtCell : public QWidget
{
    Q_OBJECT

public:
    explicit QtCell(QWidget *parent = nullptr);
    explicit QtCell(int point_, QWidget *parent = nullptr);
    ~QtCell();

    enum Status{
        none, pl1, pl2, area1, area2
    };

    int point = 0;
    Status status = none;

signals:
    void clicked(QMouseEvent *e);

public slots:
    void setTeam();

protected:
    //mousePressEvent オーバーライドし、QMouseEvent* 型を引数に持つシグナルをオーバーロード
    void mousePressEvent(QMouseEvent *e);

private:
    Ui::QtCell *ui;
};

#endif // CELL_H
