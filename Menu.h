/********************************************************************************
** Form generated from reading UI file 'designervvHGxU.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MENU_H
#define MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Main_Menu
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(283, 275);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 30, 171, 27));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(50, 70, 171, 27));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(50, 110, 171, 27));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(50, 150, 171, 27));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(50, 190, 171, 27));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\245\320\276\321\201\321\202\321\213", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\320\241\320\265\321\202\320\265\320\262\320\260\321\217 \320\260\320\272\321\202\320\270\320\262\320\275\320\276\321\201\321\202\321\214", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\275\321\202\320\265\320\271\320\275\320\265\321\200\321\213 \320\270 \320\272\320\273\320\260\321\201\321\202\320\265\321\200\321\213", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\261\320\273\320\265\320\274\321\213", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\320\241\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \321\201\320\265\321\202\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Menu: public Ui_Main_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MENU_H
