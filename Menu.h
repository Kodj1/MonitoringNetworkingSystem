#ifndef MENU_H
#define MENU_H

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "Autorization.h"
#include "NetworkAction.h"
#include "Network_traffic.h"
#include "Host_window.h"

QT_BEGIN_NAMESPACE

class Ui_Main_Menu : public QObject
{
    Q_OBJECT
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;

    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);  

public slots:
    //void Open_Menu();
    void Open_Window_Network_Action();
    void Open_Window_Network_Traffic();
    void Open_Window_Host_Stats();
    void Open_Window_Host_Window();
};

namespace Ui {
    class Menu : public Ui_Main_Menu {};
}

QT_END_NAMESPACE

#endif