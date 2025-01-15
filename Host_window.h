#ifndef HOST_WINDOW_H
#define HOST_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtWidgets/QWidget>
#include <QtSql/QSqlTableModel> 
#include "Menu.h"
#include "AddForm.h"

QT_BEGIN_NAMESPACE

class Ui_Host_Window : public QObject
{
    Q_OBJECT
public:
    QWidget *centralwidget;
    QTableView *tableView;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSqlTableModel *model;

    void retranslateUi(QMainWindow *MainWindow);
    void setupUi(QMainWindow *MainWindow);

public slots:
void openAddForm();
void deleteRecord();
};

namespace Ui {
    class Host: public Ui_Host_Window{};
} 

QT_END_NAMESPACE

#endif