#include <QApplication>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "AddForm.h"


   void Ui_Add_Form::setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(341, 122);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(30, 40, 113, 27));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(200, 40, 113, 27));
        lineEdit_2->setLayoutDirection(Qt::LeftToRight);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 151, 19));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(220, 10, 71, 19));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(26, 80, 291, 27));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

         QObject::connect(pushButton, &QPushButton::clicked, this, &Ui_Add_Form::onAddButtonClicked);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void Ui_Add_Form::retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265", nullptr));
        lineEdit_2->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265 \321\205\320\276\321\201\321\202\320\260", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "ip-address", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
    } // retranslateUi

    void Ui_Add_Form::onAddButtonClicked()
    {
    QString hostName = lineEdit->text();
    QString ipAddress = lineEdit_2->text();

    if (hostName.isEmpty() || ipAddress.isEmpty()) {
        QMessageBox::warning(nullptr, QObject::tr("Input Error"),
                             QObject::tr("Please fill in both fields."));
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO host (hostname, ip_address) VALUES (:hostname, :ip_address)");
    query.bindValue(":hostname", hostName);
    query.bindValue(":ip_address", ipAddress);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, QObject::tr("Database Error"),
                              query.lastError().text());
    } else {
        QMessageBox::information(nullptr, QObject::tr("Success"),
                                 QObject::tr("Record added successfully."));
    }
    }
