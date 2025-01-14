#include "Autorization.h"
#include "Menu.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

void Ui_Autorization_Window::setupUi(QMainWindow *MainWindow)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(271, 236);

    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));

    pushButton = new QPushButton(centralwidget);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(90, 160, 87, 27));

    lineEdit = new QLineEdit(centralwidget);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
    lineEdit->setGeometry(QRect(40, 70, 191, 27));

    lineEdit_2 = new QLineEdit(centralwidget);
    lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
    lineEdit_2->setGeometry(QRect(40, 110, 191, 27));
    lineEdit_2->setEchoMode(QLineEdit::Password);

    label = new QLabel(centralwidget);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(90, 30, 91, 19));

    MainWindow->setCentralWidget(centralwidget);

    retranslateUi(MainWindow);

    mainWindow = MainWindow;

    QObject::connect(pushButton, &QPushButton::clicked, this, &Ui_Autorization_Window::openMenu);

    QMetaObject::connectSlotsByName(MainWindow);
}

void Ui_Autorization_Window::retranslateUi(QMainWindow *MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Авторизация", nullptr));
    pushButton->setText(QCoreApplication::translate("MainWindow", "Войти", nullptr));
    label->setText(QCoreApplication::translate("MainWindow", "Авторизация", nullptr));
}

bool Ui_Autorization_Window::authenticateUser(const QString &username, const QString &password)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("mns");
    db.setUserName("postgres");
    //db.setPassword("12345");

    if (!db.open()) {
        QMessageBox::critical(this, "Database Error", db.lastError().text());
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT 1 FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        QMessageBox::critical(this, "Query Error", query.lastError().text());
        return false;
    }

    return query.next();
}

void Ui_Autorization_Window::openMenu()
{
    QString username = lineEdit->text();
    QString password = lineEdit_2->text();

    if (authenticateUser(username, password)) {
        QMainWindow *menuWindow = new QMainWindow();
        Ui::Menu *menu = new Ui::Menu();
        menu->setupUi(menuWindow);
        menuWindow->show();
        mainWindow->close();
    } else {
        QMessageBox::warning(this, "Authentication Failed", "Incorrect username or password", QMessageBox::Ok);
    }
}