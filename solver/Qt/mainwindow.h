#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPalette>

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

    const QString COLOR_BLUE = "#1489ff", COLOR_LIGHT_BLUE = "#9eceff";
    const QString COLOR_ORANGE = "#ff8914", COLOR_LIGHT_ORANGE = "#ffce9e";

public slots:
    void importFromQR();
    void changeTurn(int turn);
    void changeScore(Field field);
    void changeStatusBar(Ui::Phase phase);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
