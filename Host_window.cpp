#include "Host_window.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QModelIndex>
#include <QStyledItemDelegate>
#include <QMainWindow>
#include <QPushButton>
#include <QTableView>
#include <QSqlTableModel>

class ReadOnlyDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    ReadOnlyDelegate(int editableColumns, QObject *parent = nullptr)
        : QStyledItemDelegate(parent), m_editableColumns(editableColumns) {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        if (index.column() >= m_editableColumns) {
            return nullptr; // Prevent editing for columns after m_editableColumns
        }
        return QStyledItemDelegate::createEditor(parent, option, index);
    }

private:
    int m_editableColumns;
};

void Ui_Host_Window::setupUi(QMainWindow *MainWindow)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(793, 326);

    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    
    tableView = new QTableView(centralwidget);
    tableView->setObjectName(QString::fromUtf8("tableView"));
    tableView->setGeometry(QRect(0, 0, 791, 281));
    tableView->setSelectionMode(QAbstractItemView::SingleSelection); // Single selection
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // Select rows

    // Create and set up the model
    model = new QSqlTableModel(this); // Initialize model
    model->setTable("host"); // Set table name
    model->select(); // Execute query

    // Set the model to the tableView
    tableView->setModel(model);
    tableView->setColumnHidden(model->fieldIndex("id"), true); // Hide id column

    // Set delegate for read-only columns
    int ipAddressColumn = model->fieldIndex("ip_address");
    tableView->setItemDelegate(new ReadOnlyDelegate(ipAddressColumn + 1, this));

    // Set up buttons
    pushButton = new QPushButton(centralwidget);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(10, 290, 81, 27));
    
    pushButton_2 = new QPushButton(centralwidget);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setGeometry(QRect(110, 290, 111, 27));
    
    pushButton_3 = new QPushButton(centralwidget);
    pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
    pushButton_3->setGeometry(QRect(240, 290, 71, 27));
    
    MainWindow->setCentralWidget(centralwidget);

    retranslateUi(MainWindow);

    // Connect signals to slots
    QObject::connect(pushButton_3, &QPushButton::clicked, this, &Ui_Host_Window::deleteRecord);
    QObject::connect(pushButton, &QPushButton::clicked, this, &Ui_Host_Window::openAddForm);

    QMetaObject::connectSlotsByName(MainWindow);
}

void Ui_Host_Window::retranslateUi(QMainWindow *MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Хосты", nullptr));
    pushButton->setText(QCoreApplication::translate("MainWindow", "Добавить", nullptr));
    pushButton_2->setText(QCoreApplication::translate("MainWindow", "Редактировать", nullptr));
    pushButton_3->setText(QCoreApplication::translate("MainWindow", "Удалить", nullptr));
}

void Ui_Host_Window::deleteRecord()
{
    QModelIndex index = tableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(nullptr, QObject::tr("Selection Error"),
                             QObject::tr("Please select a row to delete."));
        return;
    }

    int row = index.row();
    int id = model->data(model->index(row, model->fieldIndex("id"))).toInt(); // Assuming there is an id column

    QSqlQuery query;
    query.prepare("DELETE FROM host WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, QObject::tr("Database Error"),
                              query.lastError().text());
    } else {
        model->removeRow(row); // Remove row from model
        model->select(); // Refresh model
        QMessageBox::information(nullptr, QObject::tr("Success"),
                                 QObject::tr("Record deleted successfully."));
    }
}

void Ui_Host_Window::openAddForm()
{
    QMainWindow *Open_Add_form = new QMainWindow();
    Ui::AddForm *Add_form = new Ui::AddForm();
    Add_form->setupUi(Open_Add_form);
    Open_Add_form->show();
}