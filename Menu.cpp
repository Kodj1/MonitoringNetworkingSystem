#include "Menu.h"
#include "Autorization.h"
#include "NetworkAction.h"
#include "Host_stats.h"
#include "Host_window.h"
#include "Server_logs.h"
#include <QApplication>


void Ui_Main_Menu::setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(283, 210);

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

        MainWindow->setCentralWidget(centralwidget);
 
        retranslateUi(MainWindow);

        QObject::connect(pushButton, &QPushButton::clicked, this, &Ui_Main_Menu::Open_Window_Host_Window);
        QObject::connect(pushButton_2, &QPushButton::clicked, this, &Ui_Main_Menu::Open_Window_Host_Stats);
        QObject::connect(pushButton_3, &QPushButton::clicked, this, &Ui_Main_Menu::Open_Window_Network_Action);
        QObject::connect(pushButton_4, &QPushButton::clicked, this, &Ui_Main_Menu::Open_Window_Server_Logs);

        QMetaObject::connectSlotsByName(MainWindow);
    } 

    void Ui_Main_Menu::retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Главное меню", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Хосты", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Статистика хостов", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Сканирование сети", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Журнал системы", nullptr));
    }

    void Ui_Main_Menu::Open_Window_Network_Action()
    {
    QMainWindow *networkWindow = new QMainWindow();
    Ui::Network_Window *net_win = new Ui::Network_Window();
    net_win->setupUi(networkWindow);
    networkWindow->show();
    }
    
    void Ui_Main_Menu::Open_Window_Host_Stats()
    {
    QMainWindow *Network_Host_Stats = new QMainWindow();
    Ui::Host_stats *host_stat = new Ui::Host_stats();
    host_stat->setupUi(Network_Host_Stats);
    Network_Host_Stats->show();
    }

    void Ui_Main_Menu::Open_Window_Host_Window()
    {
    QMainWindow *_Host = new QMainWindow();
    Ui::Host *host_win= new Ui::Host();
    host_win->setupUi(_Host);
    _Host->show();
    }

    void Ui_Main_Menu::Open_Window_Server_Logs()
    {
    QMainWindow *_Server_logs = new QMainWindow();
    Ui::Server_logs *server_logs= new Ui::Server_logs();
    server_logs->setupUi(_Server_logs);
    _Server_logs->show();
    }