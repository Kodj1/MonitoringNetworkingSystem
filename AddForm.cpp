#include "Host_window.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QModelIndex>
#include <QSqlTableModel> 
#include "AddForm.h"

    void UI_AddFormWindow::setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(345, 202);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(210, 30, 113, 27));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(210, 70, 113, 27));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 81, 19));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 70, 66, 19));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(210, 110, 111, 27));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 110, 171, 19));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(26, 150, 291, 27));
        MainWindow->setCentralWidget(centralwidget);

        comboBox->addItem("Manjaro");
        comboBox->addItem("Ubuntu");
        comboBox->addItem("FreeBSD");
        comboBox->addItem("Fedora");


        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    }

    void UI_AddFormWindow::retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \321\205\320\276\321\201\321\202\320\260", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217 \321\205\320\276\321\201\321\202\320\260:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "ip-\320\260\320\264\321\200\320\265\321\201:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\236\320\277\320\265\321\200\320\260\321\206\320\270\320\276\320\275\320\275\320\260\321\217 \321\201\320\270\321\201\321\202\320\265\320\274\320\260:", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
    }
