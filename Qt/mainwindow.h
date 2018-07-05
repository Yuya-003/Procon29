#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "settingdialog.h"
#include "gamefield.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openSettingDialog();

private slots:
    void on_reset_button_clicked();

    void on_shuffle_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
