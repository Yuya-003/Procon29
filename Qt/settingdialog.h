#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

    void changeMapSize(int x, int y);
    void changeTurn(int turn);

signals:
    void sendMapSize(int, int);
    void sendTurn(int);
    void requestInit();

private slots:
    void on_ok_button_clicked();

    void on_pushButton_2_clicked();

    void on_num_turn_editingFinished();

    void on_map_x_editingFinished();

    void on_map_y_editingFinished();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
