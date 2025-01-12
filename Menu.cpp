#include "Menu.h"
#include "Autorization.h"
#include "NetworkAction.h"
#include "Network_traffic.h"
#include <QApplication>



void Ui_Main_Menu::setupUi(QMainWindow *MainWindow)
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
 

        retranslateUi(MainWindow);

        //  QObject::connect(pushButton, &QPushButton::clicked, this, &Ui_Main_Menu::openMenu);
        QObject::connect(pushButton_2, &QPushButton::clicked, this, &Ui_Main_Menu::Open_Window_Network_Traffic);
        //QObject::connect(pushButton_3, &QPushButton::clicked, this, &Ui_Main_Menu::openWindowNetworkAction);
        // QObject::connect(pushButton_4, &QPushButton::clicked, this, &Ui_Main_Menu::openMenu);
        QObject::connect(pushButton_5, &QPushButton::clicked, this, &Ui_Main_Menu::Open_Window_Network_Action);

        QMetaObject::connectSlotsByName(MainWindow);
    } 

    void Ui_Main_Menu::retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Главное меню", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Хосты", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Сетевая активность", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Контейнеры и кластеры", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Проблемы", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Сканирование сети", nullptr));
    } // retranslateUi

    /* void Ui_Main_Menu::openMenu()//Open 
    {
    // Create a new Menu window
    QMainWindow *menuWindow = new QMainWindow();
    Ui::Menu *menu = new Ui::Menu();
    menu->setupUi(menuWindow);
    menuWindow->show();
    }*/

    void Ui_Main_Menu::Open_Window_Network_Action()
    {
    QMainWindow *networkWindow = new QMainWindow();
    Ui::Network_Window *net_win = new Ui::Network_Window();
    net_win->setupUi(networkWindow);
    networkWindow->show();
    }
    

    void Ui_Main_Menu::Open_Window_Network_Traffic()
    {
    QMainWindow *Network_Traffic_Window = new QMainWindow();
    Ui::Network_Traffic *net_traffic = new Ui::Network_Traffic();
    net_traffic->setupUi(Network_Traffic_Window);
    Network_Traffic_Window->show();
    }