#ifndef ADDFORM_H
#define ADDFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Add_Form : public QObject
{
    Q_OBJECT
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton; 

    void retranslateUi(QMainWindow *MainWindow);
    void setupUi(QMainWindow *MainWindow);

public slots:
    void onAddButtonClicked();
};

namespace Ui {
    class AddForm: public Ui_Add_Form {};
}

QT_END_NAMESPACE

#endif
