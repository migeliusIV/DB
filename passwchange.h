#ifndef PASSWCHANGE_H
#define PASSWCHANGE_H

#include <QDialog>
#include "database.h"

namespace Ui {
class PasswChange;
}

class PasswChange : public QDialog
{
    Q_OBJECT
private:
    Ui::PasswChange *ui;
    DataBase* base;

public:
    QString login;
    explicit PasswChange(DataBase*, QString, QWidget *parent = nullptr);
    ~PasswChange();
    DataBase* getDataBase() const {return base;}

private slots:
    void on_buttonBox_2_accepted();
    void on_buttonBox_2_rejected();

};

#endif // PASSWCHANGE_H
