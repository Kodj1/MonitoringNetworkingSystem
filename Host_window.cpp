#include <QApplication>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "Host_window.h"
#include "Menu.h"

void Ui_Host_Window::setupUi(QMainWindow *MainWindow)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(793, 326);

    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    
    tableView = new QTableView(centralwidget);
    tableView->setObjectName(QString::fromUtf8("tableView"));
    tableView->setGeometry(QRect(0, 0, 791, 281));
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    // Создание и настройка модели для таблицы
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("host"); // Укажите имя вашей таблицы
    model->select(); // Выполнение запроса к базе данных
    
    // Установка модели в tableView
    tableView->setModel(model);

    tableView->setColumnHidden(model->fieldIndex("id"), true);

    pushButton = new QPushButton(centralwidget);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(10, 290, 81, 27));
    
    pushButton_2 = new QPushButton(centralwidget);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setGeometry(QRect(110, 290, 111, 27));
    
    pushButton_3 = new QPushButton(centralwidget);
    pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
    pushButton_3->setGeometry(QRect(240, 290, 71, 27));
    
    MainWindow->setCentralWidget(centralwidget);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
} 

void Ui_Host_Window::retranslateUi(QMainWindow *MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Хосты", nullptr));
    pushButton->setText(QCoreApplication::translate("MainWindow", "Добавить", nullptr));
    pushButton_2->setText(QCoreApplication::translate("MainWindow", "Редактировать", nullptr));
    pushButton_3->setText(QCoreApplication::translate("MainWindow", "Удалить", nullptr));
} 

bool Ui_Host_Window::authenticateUser()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("mns");
    db.setUserName("postgres");
    db.setPassword("12345"); // Установите пароль

    if (!db.open()) {
        QMessageBox::critical(nullptr, "Database Error", db.lastError().text());
        return false;
    }
    return true;
}