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
#include "Menu.h"

QT_BEGIN_NAMESPACE

class Ui_Network_window : public QObject
{
    Q_OBJECT
public:
    QWidget *centralwidget;
    QTreeView *treeView;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;

    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);

public slots:
    void openWindow();
};

namespace Ui {
    class Network_Window: public Ui_Network_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif
