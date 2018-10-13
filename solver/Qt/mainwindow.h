#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

#include "settingdialog.h"
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

public slots:
    void openSettingDialog();

    void importFromQR();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
