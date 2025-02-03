#include <QApplication>
#include <QMainWindow>
#include <QListWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "Server_logs.h"

void UI_Server_logs::setupUi(QMainWindow *MainWindow)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(993, 570);

    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));

    listWidget = new QListWidget(centralwidget);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));
    listWidget->setGeometry(QRect(10, 10, 191, 551));

    textEdit = new QTextEdit(centralwidget);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
    textEdit->setGeometry(QRect(210, 10, 781, 551));

    MainWindow->setCentralWidget(centralwidget);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);

    populateFileList();
}

void UI_Server_logs::retranslateUi(QMainWindow *MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Журнал системы", nullptr));
}

void UI_Server_logs::populateFileList()
{
    QDir directory(logDirectory);
    QStringList files = directory.entryList(QStringList() << "*.txt", QDir::Files);

    foreach (QString filename, files) {
        QListWidgetItem *item = new QListWidgetItem(filename, listWidget);
        item->setData(Qt::UserRole, directory.absoluteFilePath(filename));
    }

    connect(listWidget, &QListWidget::itemClicked, [this](QListWidgetItem *item) {
        loadFileContent(item->data(Qt::UserRole).toString());
    });
}

void UI_Server_logs::loadFileContent(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "Failed to open file.");
        return;
    }
    QTextStream in(&file);
    textEdit->setPlainText(in.readAll());
    file.close();
}