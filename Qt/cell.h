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
    explicit Cell(QWidget *parent = 0);
    explicit Cell(const QString &text, QWidget *parent = 0);
    ~Cell();

private:
    Ui::Cell *ui;
};

#endif // CELL_H
