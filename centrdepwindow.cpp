#include "centrdepwindow.h"
#include "./ui_centrdepwindow.h"

// my
#include "mainwindow.h"

centrdepwindow::centrdepwindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::centrdepwindow)
{
    ui->setupUi(this);
}

centrdepwindow::~centrdepwindow()
{
    base->~DataBase();
    delete base;
    delete ui;
}

void centrdepwindow::on_btnStocks_clicked()
{
    base->loadStockDataToTable(ui->tblOutput);
}


void centrdepwindow::on_btnOperations_clicked()
{
    base->loadOperationsDataToTable(ui->tblOutput);
}

void centrdepwindow::on_btnStockAppend_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    "Сохранить CSV файл",
                                                    QDir::homePath(),
                                                    "CSV Files (*.csv)");
    if (!filePath.isEmpty()) {
        base->importReleasedStocksFromCSV(filePath);
    }
}


void centrdepwindow::on_btnOperationAppend_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    "Открыть CSV файл",
                                                    QDir::homePath(),
                                                    "CSV Files (*.csv)");
    if (!filePath.isEmpty()) {
        base->importOperationsFromCSV(filePath);
    }
}


void centrdepwindow::on_btnStockDelete_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    "Открыть CSV файл",
                                                    QDir::homePath(),
                                                    "CSV Files (*.csv)");
    if (!filePath.isEmpty()) {
        base->exportReleasedStocksToCSV(filePath);
    }
}


void centrdepwindow::on_btnReport_clicked()
{
    // открывает яндекс-диск с папкой отчётов для ЦД
}


void centrdepwindow::on_btnBack_clicked()
{
    MainWindow *window = new MainWindow(getDataBase());
    window->show();
    this->close();
}

