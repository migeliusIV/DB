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
// file service
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
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
    void loadStockDataToTable(QTableWidget*, QString = "new");
    void loadOperationsDataToTable(QTableWidget*, QString = "center", QString = "all");
    void loadAccountsDataToTable(QTableWidget*, QString = "all");
    bool exportReleasedStocksToCSV(const QString&);
    bool importReleasedStocksFromCSV(const QString&);
    bool importOperationsFromCSV(const QString&);
    bool rejectAccount(QString);
    QString acceptAccount(QString, QString);
    QString getAccStatus(QString);
    //Broker
    void loadBrokersOperationsDataToTable(QString, QTableWidget*, QString = "");   // вывод связанных операций
    void loadBrokersAccountDataToTable(QString, QTableWidget*, QString = "");     // вывод связанных счетов
    void loadBrokersStocksDataToTable(QString, QTableWidget*, QString = "");      // вывод связанных ценных бумаг
    void brokerFormInit(QString, QLabel*, QLabel*, QLabel*, QLabel*);   // основная инфа
    void brokerFormUpdate(QString, QLabel*, QLabel* );                  // обновление вспомогательных данных
    QString deleteBrokerAccount(QString, QString);                      // удаление счёта
    QString appendBrokerAccount(QString, QString, QString);             // Добавление счёта
    void InnFillingCmb(QComboBox*, QString="");                         // Перезаполнение ComboBox'a
    //Operator
    void loadDealsRequests(QTableWidget*, int = 0);
    void windowInit(QString, QLabel*, QLabel*);
    void idFillingCmb(QComboBox*);
    QString setAcceptOperation(QString);
    QString setFreezeOperation(QString);
    //Director
    void loadDirectEmployeesToTable(QTableWidget*);
    void loadDirectBrokersToTable(QTableWidget*);
    QString appendDirectorsBroker(QString, QString, QString, QString);
    QString appendDirectorsEmployee(QString, QString, QString, QString, QString = "", QString = "");
    void deleteDirectorsBroker(QString, QString);
    void deleteDirectorsEmployee(QString, QString);
    //Password window
    void setPassword(QString, QString);
    // Universe
    void createReport(QString, QString, QString, QString); // path, header, text
    QString getBrokerByInn(QString);
    QString getAccDepoByInn(QString);
    bool deleteUserDirectory(QString);
};

#endif // DATABASE_H
