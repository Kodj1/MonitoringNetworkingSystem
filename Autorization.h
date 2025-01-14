#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include "Menu.h"

QT_BEGIN_NAMESPACE

class Ui_Autorization_Window : public QMainWindow
{
    Q_OBJECT
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QMainWindow *mainWindow;

    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);

public slots:
    void openMenu();
    bool authenticateUser(const QString &username, const QString &password);
};

namespace Ui {
    class Autorization_Window : public Ui_Autorization_Window {};
}

QT_END_NAMESPACE

#endif // AUTHORIZATION_H