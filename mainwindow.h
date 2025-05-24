#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

// extern
#include "database.h"

// my
#include "centrdepwindow.h"
#include "broker.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    DataBase* base;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    DataBase* getDataBase() const {return base;}

private slots:
    void on_btnEnter_clicked();

public slots:
              //void dbconnect();
};
#endif // MAINWINDOW_H
