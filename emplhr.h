#ifndef EMPLHR_H
#define EMPLHR_H

#include <QMainWindow>

#include "database.h"

namespace Ui {
class EmplHR;
}

class EmplHR : public QMainWindow
{
    Q_OBJECT
private:
    Ui::EmplHR *ui;
    DataBase* base;

public:
    // my
    QString login;
    void setDataBase(DataBase* temp){base = temp;}
    DataBase* getDataBase() const {return base;}
    // class
    explicit EmplHR(DataBase*, QString, QWidget *parent = nullptr);
    ~EmplHR();

private slots:
    void on_btnBack_clicked();
};

#endif // EMPLHR_H
