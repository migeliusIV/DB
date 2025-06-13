#ifndef EMPLDIRECTOR_H
#define EMPLDIRECTOR_H

#include <QMainWindow>

#include "database.h"

namespace Ui {
class EmplDirector;
}

class EmplDirector : public QMainWindow
{
    Q_OBJECT
private:
    Ui::EmplDirector *ui;
    DataBase* base;

public:
    QString login;
    void setDataBase(DataBase* temp){base = temp;}
    DataBase* getDataBase() const {return base;}
    explicit EmplDirector(DataBase*, QString, QWidget *parent = nullptr);
    ~EmplDirector();

private slots:
    void on_btnBack_clicked();

    void on_btnRepresentUsers_clicked();
    void on_btnAppendUser_clicked();
    void on_btnDepsBrokers_clicked();
    void on_btnDepsOpers_clicked();
    void on_btnAppendBroker_clicked();
    void on_btnAppendEmployee_clicked();
    void on_chkOperator_checkStateChanged(const Qt::CheckState &arg1);
};

#endif // EMPLDIRECTOR_H
