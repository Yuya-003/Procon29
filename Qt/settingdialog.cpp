#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::changeMapSize(int x, int y)
{
    ui->map_x->setValue(x);
    ui->map_y->setValue(y);
}

void SettingDialog::changeTurn(int turn)
{
    ui->num_turn->setValue(turn);
}

void SettingDialog::on_ok_button_clicked()
{
    emit sendMapSize(ui->map_x->value(), ui->map_y->value());
    emit sendTurn(ui->num_turn->value());
    emit requestInit();

    this->close();
}

void SettingDialog::on_pushButton_2_clicked()
{
    this->close();
}

void SettingDialog::on_num_turn_editingFinished()
{
    if(ui->num_turn->value() < 60){
        ui->num_turn->setValue(60);
    }
    else if(ui->num_turn->value() > 120){
        ui->num_turn->setValue(120);
    }
}

void SettingDialog::on_map_x_editingFinished()
{
    if(ui->map_x->value() < 10){
        ui->map_x->setValue(10);
    }
    else if(ui->map_x->value() > 12){
        ui->map_x->setValue(12);
    }
}

void SettingDialog::on_map_y_editingFinished()
{
    if(ui->map_y->value() < 8){
        ui->map_y->setValue(8);
    }
    else if(ui->map_y->value() > 12){
        ui->map_y->setValue(12);
    }
}
