#ifndef CELL_H
#define CELL_H

#include <QWidget>

namespace Ui {
class Cell;
}

class Cell : public QWidget
{
    Q_OBJECT

public:
    explicit Cell(QWidget *parent = nullptr);
    explicit Cell(int point_, QWidget *parent = nullptr);
    ~Cell();

    enum Status{
        none, pl1, pl2, area1, area2
    };

    int point = 0;
    Status status = none;

private:
    Ui::Cell *ui;
};

#endif // CELL_H
