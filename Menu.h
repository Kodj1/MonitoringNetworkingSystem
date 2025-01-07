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
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);  

public slots:
    void openMenu();
};

namespace Ui {
    class Menu : public Ui_Main_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MENU_H