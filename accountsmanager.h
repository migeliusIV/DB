#ifndef ACCOUNTSMANAGER_H
#define ACCOUNTSMANAGER_H

#include <QMainWindow>

namespace Ui {
class AccountsManager;
}

class AccountsManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit AccountsManager(QWidget *parent = nullptr);
    ~AccountsManager();

private:
    Ui::AccountsManager *ui;
};

#endif // ACCOUNTSMANAGER_H
