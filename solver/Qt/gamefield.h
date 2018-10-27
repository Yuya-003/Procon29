#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QtGui>
#include <QFrame>
#include <QLabel>
#include <QMouseEvent>
#include <QPalette>
#include <QPainter>
#include <QSizePolicy>

#include <random>
#include <vector>
#include <string>
#include <structure/Field.hpp>

namespace Ui {
class GameField;
}

class GameField : public QWidget
{
    Q_OBJECT

public:

    const int CELL_SIZE = 50;
    const int FONT_SIZE = 25,  FONT_WIDTH = 1;
    const QColor COLOR_BLUE = "#1489ff", COLOR_LIGHT_BLUE = "#9eceff";
    const QColor COLOR_RED = "#ff1414",  COLOR_LIGHT_RED = "#ff7a7a";

    explicit GameField(QWidget *parent = nullptr);
    ~GameField();

    bool isPlayerAround(Position clickedOnGrid);

    size_t mapX(){ return field.rowSize(); }
    size_t mapY(){ return field.colSize(); }

    int turn, pointTeam1, pointTeam2;
    bool isReadyTurn;
    Field field;

signals:
    //emit in mousePressEvent
    void clicked(void);
    void clicked(QMouseEvent*);

protected:
    void mousePressEvent(QMouseEvent *e) override
        {emit clicked(); emit clicked(e);}

    void paintEvent(QPaintEvent *e) override;

private:
    Ui::GameField *ui;
};

#endif // GAMEFIELD_H
