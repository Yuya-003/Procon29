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

static Field fieldData = Field();
}

class GameField : public QWidget
{
    Q_OBJECT

public:
    enum{
       CELL_SIZE = 50,
    };

    explicit GameField(QWidget *parent = nullptr);
    ~GameField();

    int map_x, map_y;
    int turn, pointTeam1, pointTeam2;

    inline void mousePressEvent(QMouseEvent *e) override { emit clicked(e); }
    void paintEvent(QPaintEvent *e) override;

    void drawField(Field field = Field());

signals:
    void clicked(QMouseEvent*);


public slots:
    void changeMapSize(int x, int y);

    void changeTurn(int turn);

    void updateField(QMouseEvent *e);

    //void updateScore(int point);

private:
    Ui::GameField *ui;
};

#endif // GAMEFIELD_H
