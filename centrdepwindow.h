#ifndef CENTRDEPWINDOW_H
#define CENTRDEPWINDOW_H

#include <QMainWindow>

// extern
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class centrdepwindow;
}
QT_END_NAMESPACE

class centrdepwindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::centrdepwindow *ui;
    DataBase* base;

public:
    int outputMode;
    centrdepwindow(QWidget *parent = nullptr);
    ~centrdepwindow();
    void setDataBase(DataBase* temp){base = temp;} // перенос коннекта с БД
    DataBase* getDataBase() const {return base;}   // getter для указателя на БД

private slots:
    void on_btnStocks_clicked();
    void on_btnOperations_clicked();
    void on_btnStockAppend_clicked();
    void on_btnOperationAppend_clicked();
    void on_btnStockDelete_clicked();
    void on_btnReport_clicked();
    void on_btnBack_clicked();
    void on_btnDepoInit_clicked();
    void on_btnAccounts_clicked();

public slots:
signals:
};

#endif // CENTRDEPWINDOW_H
