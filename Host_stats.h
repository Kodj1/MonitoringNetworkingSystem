#ifndef HOST_STATS_H
#define HOST_STATS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "Menu.h"

QT_BEGIN_NAMESPACE

class Ui_Host_stats : public QObject
{
    Q_OBJECT
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QLineEdit *lineEdit;
    QListWidget *listWidget;

    void retranslateUi(QMainWindow *MainWindow);
    void setupUi(QMainWindow *MainWindow);

public slots:
};

namespace Ui {
    class Host_stats: public Ui_Host_stats {};
} 

QT_END_NAMESPACE

#endif
