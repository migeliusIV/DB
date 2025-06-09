#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QtSql>
#include <QTextEdit>
#include <QDebug>
#include <QLabel>
#include <QHeaderView>
#include <QMainWindow>
// debug
#include <QTableWidget>
#include <QTableWidgetItem>
// Для импорта-экспорта данных
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
class DataBase
{
private:
    QSqlDatabase db;
    QMetaObject::Connection tableSelectionConnection;
public:
    DataBase();
    ~DataBase();
    QSqlDatabase getDB() const {return db;}
    //MainWindow
    int SelectAISUser(QString, QString);
    //Central depository
    void loadStockDataToTable(QTableWidget*);
    void loadOperationsDataToTable(QTableWidget*);
    bool exportReleasedStocksToCSV(const QString&);
    bool importReleasedStocksFromCSV(const QString&);
    bool importOperationsFromCSV(const QString&);
    //Broker
    void loadBrokersOperationsDataToTable(QString, QTableWidget*, QString = "");   // вывод связанных операций
    void loadBrokersAccountDataToTable(QString, QTableWidget*, QString = "");     // вывод связанных счетов
    void loadBrokersStocksDataToTable(QString, QTableWidget*, QString = "");      // вывод связанных ценных бумаг
    void brokerFormInit(QString, QLabel*, QLabel*, QLabel*, QLabel*);   // основная инфа
    void brokerFormUpdate(QString, QLabel*, QLabel* );                  // обновление вспомогательных данных
    QString deleteBrokerAccount(QString, QTableWidget*, QString);             // удаление счёта
    void brokerFillingCmb(QString, QComboBox*);
    //Operator
    void loadDealsRequests(QTableWidget*, int = 0);
    bool checkSufficientStocksForOperation(int);
    //HR
    //Director
    //Password window
    void setPassword(QString, QString);
};

#endif // DATABASE_H
