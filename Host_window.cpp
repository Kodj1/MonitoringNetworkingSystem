#include "Host_window.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QModelIndex>
#include <QSqlTableModel> 
#include "AddForm.h"


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
    tableView->setSelectionMode(QAbstractItemView::SingleSelection); // Выбор только одного элемента
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // Выбор строк
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


    // Создание и настройка модели для таблицы
    model = new QSqlTableModel(this); // Инициализация модели
    model->setTable("nodes"); // Укажите имя вашей таблицы
    model->select(); // Выполнение запроса к базе данных
    
    // Установка модели в tableView
    tableView->setModel(model);

    tableView->setColumnHidden(model->fieldIndex("id"), true);

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

    // Подключите сигнал нажатия кнопки к слоту
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
    int id = model->data(model->index(row, model->fieldIndex("id"))).toInt(); // Предполагается, что есть столбец id

    QSqlQuery query;
    query.prepare("DELETE FROM nodes WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, QObject::tr("Database Error"),
                              query.lastError().text());
    } else {
        model->removeRow(row); // Удаляем строку из модели
        model->select(); // Обновляем модель
        QMessageBox::information(nullptr, QObject::tr("Success"),
                                 QObject::tr("Record deleted successfully."));
    }
}

void Ui_Host_Window::openAddForm ()
{
    QMainWindow *Open_Add_form= new QMainWindow();
    Ui::AddForm *Add_form= new Ui::AddForm();
    Add_form->setupUi(Open_Add_form);
    Open_Add_form->show();
}