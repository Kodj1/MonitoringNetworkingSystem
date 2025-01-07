#ifndef HOSTCHECKER_H
#define HOSTCHECKER_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QStatusBar>
#include <QWidget>
#include <QProcess>
#include "Menu.h"

QT_BEGIN_NAMESPACE

class Ui_HostChecker_Window : public QObject
{
    Q_OBJECT

public:
    QWidget *centralwidget;
    QPushButton *checkButton;
    QLineEdit *lineEdit;
    QTextEdit *resultText;
    QLabel *label;
    QStatusBar *statusbar;
    QMainWindow *mainWindow; // Member variable to store the main window

    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);

public slots:
    void checkHosts();
};

namespace Ui {
    class HostChecker_Window : public Ui_HostChecker_Window {};
}

QT_END_NAMESPACE

#endif // HOSTCHECKER_H