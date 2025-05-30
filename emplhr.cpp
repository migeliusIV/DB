#include "emplhr.h"
#include "ui_emplhr.h"

#include "mainwindow.h"

EmplHR::EmplHR(DataBase* temp, QString strLogin, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EmplHR)
{
    ui->setupUi(this);
    login = strLogin;
    setDataBase(temp);
}

EmplHR::~EmplHR()
{
    delete base;
    delete ui;
}

void EmplHR::on_btnBack_clicked()
{
    MainWindow *window = new MainWindow(getDataBase());
    window->show();
    this->close();
}

