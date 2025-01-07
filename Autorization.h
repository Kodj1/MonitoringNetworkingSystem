#ifndef AUTORIZATION_H
#define AUTORIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "Menu.h"

QT_BEGIN_NAMESPACE

class Ui_Autorization_Window : public QObject
{
    Q_OBJECT
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QStatusBar *statusbar;
    QMainWindow *mainWindow; // Member variable to store the main window

    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);

public slots:
    void openMenu();
};

namespace Ui {
    class Autorization_Window : public Ui_Autorization_Window {};
}

QT_END_NAMESPACE

#endif