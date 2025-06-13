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
    ui->frmOutput->hide();
    ui->tabUserAppend->hide();
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


void EmplDirector::on_btnRepresentUsers_clicked()
{
    if (ui->tabUserAppend->isVisible())
        ui->tabUserAppend->hide();
    if (!ui->frmOutput->isVisible())
        ui->frmOutput->show();
}


void EmplDirector::on_btnAppendUser_clicked()
{
    if (ui->frmOutput->isVisible())
        ui->frmOutput->hide();
    if (!ui->tabUserAppend->isVisible())
        ui->tabUserAppend->show();
}


void EmplDirector::on_btnDepsBrokers_clicked()
{
    base->loadDirectBrokersToTable(ui->tblOutput);
}


void EmplDirector::on_btnDepsOpers_clicked()
{
    base->loadDirectEmployeesToTable(ui->tblOutput);
}


void EmplDirector::on_btnAppendBroker_clicked()
{

}


void EmplDirector::on_btnAppendEmployee_clicked()
{

}


void EmplDirector::on_chkOperator_checkStateChanged(const Qt::CheckState &arg1)
{
    if (!ui->frmAppendix->isVisible())
        ui->frmAppendix->show();
    else
        ui->frmAppendix->hide();
}

