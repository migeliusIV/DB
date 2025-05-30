#include "emploperator.h"
#include "ui_emploperator.h"

#include "passwchange.h"
#include "mainwindow.h"

EmplOperator::EmplOperator(DataBase* temp, QString strLogin, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EmplOperator)
{
    ui->setupUi(this);
    login = strLogin;
    setDataBase(temp);
}

EmplOperator::~EmplOperator()
{
    delete base;
    delete ui;
}

void EmplOperator::on_btnUserChanges_clicked()
{
    PasswChange *window = new PasswChange(getDataBase(), this);
    window->show();
}

void EmplOperator::on_btnBack_clicked()
{
    MainWindow *window = new MainWindow(getDataBase());
    window->show();
    this->close();
}

