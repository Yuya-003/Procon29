#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

#include <random>

namespace Ui {
class GameField;
}

class GameField : public QWidget
{
    Q_OBJECT

public:
    explicit GameField(QWidget *parent = 0);
    ~GameField();

    int map_x, map_y;
    int turn;

    std::mt19937 mt;

public slots:
    void changeMapSize(int x, int y);
    void changeTurn(int turn);
    void initField();

private:
    Ui::GameField *ui;
};

#endif // GAMEFIELD_H
