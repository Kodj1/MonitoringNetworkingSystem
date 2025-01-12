#ifndef NETWORK_TRAFFIC_H
#define NETWORK_TRAFFIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>
#include "Menu.h"

QT_BEGIN_NAMESPACE

class Ui_Network_Traffic : public QObject
{
    Q_OBJECT
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton;
    QTableView *tableView;

    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);

public slots:
    
};

namespace Ui {
    class Network_Traffic: public Ui_Network_Traffic {};
} 

QT_END_NAMESPACE

#endif
