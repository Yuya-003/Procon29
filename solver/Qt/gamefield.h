#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "qtcell.h"

#include <QFrame>
#include <QLabel>
#include <QGridLayout>
#include <QMouseEvent>

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
    int turn, pointTeam1, pointTeam2;

    //Qt側のField
    QtField qtField;

    QGridLayout *grid;

    //structure側のField
    //Field fieldData;



public slots:
    void changeMapSize(int x, int y);

    void changeTurn(int turn);

    void updateField(QMouseEvent *e);

    //void changePoint(int point);

    //void setTeam(QMouseEvent *event);

    void initField();

private:
    Ui::GameField *ui;
};

#endif // GAMEFIELD_H
