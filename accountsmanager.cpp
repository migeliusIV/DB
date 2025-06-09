#include "accountsmanager.h"
#include "ui_accountsmanager.h"

AccountsManager::AccountsManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AccountsManager)
{
    ui->setupUi(this);
}

AccountsManager::~AccountsManager()
{
    delete ui;
}
