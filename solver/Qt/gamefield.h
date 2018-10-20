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
enum Phase{
    team1_1, team1_2, team2_1, team2_2
};

//paintEventの実行タイミングが微妙で、team1_1にできない
static Phase phase = team2_2;
}

class GameField : public QWidget
{
    Q_OBJECT

public:
    enum{
       CELL_SIZE = 50,
	   FONT_SIZE = 25,
	   FONT_WIDTH = 1,
    };

    explicit GameField(QWidget *parent = nullptr);
    ~GameField();

    int map_x, map_y;
    int turn, pointTeam1, pointTeam2;

signals:
    void clicked(void);

    void clicked(QMouseEvent*);


public slots:
    void changeMapSize(int x, int y);

    void changeTurn(int turn);

    void updateField(QMouseEvent *e);

protected:
    void mousePressEvent(QMouseEvent *e) override
		{emit clicked(); emit clicked(e);};

    void paintEvent(QPaintEvent *e) override;

private:
    Ui::GameField *ui;
};

#endif // GAMEFIELD_H
