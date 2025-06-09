#ifndef EMPLOPERATOR_H
#define EMPLOPERATOR_H

#include <QMainWindow>
#include "database.h"

namespace Ui {
class EmplOperator;
}

class EmplOperator : public QMainWindow
{
    Q_OBJECT
private:
    Ui::EmplOperator *ui;
    DataBase* base;

public:
    // temp
    QString login;
    void setDataBase(DataBase* temp){base = temp;}
    DataBase* getDataBase() const {return base;}
    // class
    explicit EmplOperator(DataBase*, QString, QWidget *parent = nullptr);
    ~EmplOperator();


private slots:
    void on_btnUserChanges_clicked();

    void on_btnBack_2_clicked();
    void on_btnDealsAll_clicked();
    void on_btnDealsNew_clicked();
    void on_btnDealsReport_clicked();
    void on_btnDealCheck_clicked();
    void on_btnDealReject_clicked();
    void on_btnDealAccept_clicked();
};

#endif // EMPLOPERATOR_H
