#ifndef BROKER_H
#define BROKER_H

#include <QMainWindow>
// extern
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Broker;
}
QT_END_NAMESPACE

class Broker : public QMainWindow
{
    Q_OBJECT
private:
    Ui::Broker *ui;
    DataBase* base;

public:
    // my
    QString login;
    int outputMode;
    void setDataBase(DataBase* temp){base = temp;}
    DataBase* getDataBase() const {return base;}
    // class
    explicit Broker(DataBase*, QString, QWidget *parent = nullptr);
    ~Broker();

private slots:
    void on_btnUserChanges_clicked();
    void on_btnAccountAppend_clicked();
    void on_btnAccountDel_clicked();
    void on_btnOperations_clicked();
    void on_btnAccounts_clicked();
    void on_btnSearch_clicked();
    void on_btnStocks_clicked();
    void on_btnBack_clicked();
};

#endif // BROKER_H
