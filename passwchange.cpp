#include "passwchange.h"
#include "ui_passwchange.h"

PasswChange::PasswChange(DataBase*, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PasswChange)
{
    // getter ui-rebuild
    ui->setupUi(this);
}

PasswChange::~PasswChange()
{
    delete ui;
}

void PasswChange::on_buttonBox_2_accepted()
{
    // setter - db query
}


void PasswChange::on_buttonBox_2_rejected()
{
    this->close();
}

