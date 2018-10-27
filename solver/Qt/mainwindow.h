#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPalette>

#include <Convert.hpp>

#include "gamefield.h"

namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    const int CELL_SIZE = 50;
    const int FONT_SIZE = 25,  FONT_WIDTH = 1;
    const QString COLOR_BLUE = "#1489ff", COLOR_LIGHT_BLUE = "#9eceff";
    const QString COLOR_RED = "#ff1414", COLOR_LIGHT_RED = "#ff7a7a";
    bool isReadyTurn;

    bool isPlayerArround(Position player, Position clickedOnGrid);

signals:
    void changedField(Field field);

public slots:
    void importFromQR();
    void updateField(QMouseEvent *e);
    void changeScore();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
