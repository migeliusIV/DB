#include "broker.h"
#include "./ui_broker.h"

Broker::Broker(DataBase* temp, QString strLogin, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Broker)
{
    ui->setupUi(this);
    login = strLogin;
    setDataBase(temp);
    base->brokerFormInit(login, ui->lblCompanyNameTxt, ui->lblINNTxt, ui->lblAccountTxt, ui->lblCheckTxt);
}

Broker::~Broker()
{
    base->~DataBase();
    delete base;
    delete ui;
}

void Broker::on_btnUserChanges_clicked()
{
    // форма для смены пароля
}


void Broker::on_btnAccountAppend_clicked()
{
    // форма для регистрации счёта
    base->brokerFormUpdate(login, ui->lblAccountTxt, ui->lblCheckTxt);
}


void Broker::on_btnAccountDel_clicked()
{
    // уаление выбранного в окне пользователя (№депо выводится)
    base->brokerFormUpdate(login, ui->lblAccountTxt, ui->lblCheckTxt);
}


void Broker::on_btnOperations_clicked()
{
    //base->loadBrokersOperationsDataToTextEdit(ui->teOutput);
    outputMode = 1;
}


void Broker::on_btnAccounts_clicked()
{
    base->loadBrokersAccountDataToTextEdit(login, ui->teOutput);
    outputMode = 2;
    base->brokerFormUpdate(login, ui->lblAccountTxt, ui->lblCheckTxt); // изменение количества аккаунтов или добавление чека
}


void Broker::on_btnStocks_clicked()
{
    base->loadBrokersStocksDataToTextEdit(login, ui->teOutput);
    outputMode = 3;
}


void Broker::on_btnSearch_clicked()
{
    // как проверять дисплей?
    switch (outputMode){
        case 1: {  // (operations)
            //base->loadBrokersOperationsDataToTextEdit(ui->teOutput, ui->edtSearhing->text());
            break;
        }
        case 2: { // (accounts)
            base->loadBrokersAccountDataToTextEdit(login, ui->teOutput, ui->edtSearhing->text());
            break;
        }
        case 3: { // (stocks)
            base->loadBrokersStocksDataToTextEdit(login, ui->teOutput, ui->edtSearhing->text());
            break;
        }
    }
}
