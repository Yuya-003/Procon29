#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "cell.h"

#include <QFrame>
#include <QLabel>
#include <QGridLayout>

#include <random>
#include <vector>
#include <structure/Field.hpp>

namespace Ui {
class GameField;

}

class GameField : public QFrame
{
    Q_OBJECT

public:
    explicit GameField(QWidget *parent = nullptr);
    ~GameField();

    using QtField = std::vector<std::vector<QtCell*>>;

    int map_x, map_y;
    int turn, point;

    //専攻チームの1人目、2人目、後攻チームの1人目、2人目
    enum phase{
        term1_1, team1_2, team2_1, tean2_2
    };


    //Qt側のField
    QtField qtField;

    QGridLayout *grid;

    //structure側のField
    //Field fieldData;


public slots:
    void changeMapSize(int x, int y);

    void changeTurn(int turn);

    //void changePoint(int point);

    void initField();

    void cellClicked();

private:
    Ui::GameField *ui;
};

#endif // GAMEFIELD_H
