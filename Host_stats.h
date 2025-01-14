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
#include "DiskUsageWidget.h" 
#include "CpuUsageWidget.h"
#include "MemUsageWidget.h"

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
    QWidget *tab_3;
    QLineEdit *lineEdit;
    QListWidget *listWidget;
    QMainWindow *mainWindow;
    DiskUsageWidget *diskUsageWidget;
    CpuUsageWidget *cpuUsageWidget;
    MemUsageWidget *memUsageWidget;

    void retranslateUi(QMainWindow *MainWindow);
    void setupUi(QMainWindow *MainWindow);

public slots:
    void populateListWidget();
    void updateDiskUsage();
    void updateCpuUsage(qreal usage);
    void updateMemUsage(qreal usage);

};

namespace Ui {
    class Host_stats: public Ui_Host_stats {};
} 

QT_END_NAMESPACE

#endif
