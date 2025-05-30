#include "empldirector.h"
#include "ui_empldirector.h"

#include "mainwindow.h"

EmplDirector::EmplDirector(DataBase* temp, QString strLogin, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EmplDirector)
{
    ui->setupUi(this);
    login = strLogin;
    setDataBase(temp);
}

EmplDirector::~EmplDirector()
{
    delete ui;
    delete base;
}

void EmplDirector::on_btnBack_clicked()
{
    MainWindow *window = new MainWindow(getDataBase());
    window->show();
    this->close();
}

