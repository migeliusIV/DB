#include "mainwindow.h"
#include "./ui_mainwindow.h"

// my
#include "centrdepwindow.h"
#include "broker.h"
#include "emploperator.h"
#include "empldirector.h"
#include "emplhr.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // start
    base = new DataBase();
    base->getDB().open();
    // regular
    ui->setupUi(this);
    ui->edtPassword->setEchoMode(QLineEdit::Password);
}

MainWindow::MainWindow(DataBase* ptrDB, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // re-open
    base = ptrDB;
    // regular
    ui->setupUi(this);
    ui->edtPassword->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete base;
    delete ui;
}

void MainWindow::on_btnEnter_clicked()
{
    // Получаем введённые логин и пароль
    QString login = ui->edtLogin->text().trimmed();
    QString password = ui->edtPassword->text().trimmed();

    // Проверяем, что поля не пустые
    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Логин и пароль не могут быть пустыми!");
        return;
    }

    switch (base->SelectAISUser(login, password)){
    case 1: { // central depository
        centrdepwindow *window = new centrdepwindow(getDataBase());
        window->show();
        this->close();
        break;
    }
    case 2: { // broker
        Broker *window = new Broker(getDataBase(), login);
        window->show();
        this->close();
        break;
    }
    case 3: { // operator
        EmplOperator *window = new EmplOperator(getDataBase(), login);
        window->show();
        this->close();
        break;
    }
    case 4: { // hr
        EmplHR *window = new EmplHR(getDataBase(), login);
        window->show();
        this->close();
        break;
    }
    case 5: { // director
        EmplDirector *window = new EmplDirector(getDataBase(), login);
        window->show();
        this->close();
        break;
    }
    case 0: { // not classificated error
        QMessageBox::warning(this, "Ошибка", "Ошибка неопределённого вида!");
        break;
    }
    case -1: { // wrong_login
        QMessageBox::warning(this, "Ошибка", "Пользователь с таким логином не найден!");
        break;
    }
    case -2: { // wrong_pass
        QMessageBox::warning(this, "Ошибка", "Неверный пароль!");
        break;
    }
    }
}
