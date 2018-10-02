#ifndef CELL_H
#define CELL_H

#include <QWidget>

namespace Ui {
class QtCell;
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

private:
    Ui::QtCell *ui;
};

#endif // CELL_H
