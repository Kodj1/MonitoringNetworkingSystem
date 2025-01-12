#ifndef NETWORKACTION_H
#define NETWORKACTION_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QStandardItemModel>
#include <QHostAddress>
#include "Menu.h"

QT_BEGIN_NAMESPACE

class Ui_Network_Window : public QObject
{
    Q_OBJECT
public:
    QWidget *centralwidget;
    QTreeView *treeView;
    QPushButton *pushButton;
    QStandardItemModel *model;
    QLineEdit *lineEdit;
    QLabel *label;
    QLineEdit *lineEdit_2;

    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);

public slots:
    void ScanNetwork(const QString &startIP, const QString &endIP);
    bool isHostAlive(const QString &ip);
    QStringList scanPorts(const QHostAddress &address, const QList<int> &portsToScan);
    QString getHostIpAddress();
    QString getHostName(const QHostAddress &address);
};

namespace Ui {
    class Network_Window: public Ui_Network_Window {};
}

QT_END_NAMESPACE

#endif
