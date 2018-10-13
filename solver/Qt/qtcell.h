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

//static Field fieldData;
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

public slots:
    void setTeam(void);

public:
    //マウスクリック時のイベントハンドラ(オーバーライド)
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::QtCell *ui;
};

#endif // CELL_H
