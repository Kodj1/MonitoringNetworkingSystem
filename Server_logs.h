#ifndef SERVER_LOGS_H
#define SERVER_LOGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class UI_Server_logs : public QObject
{
    Q_OBJECT
public:
    QWidget *centralwidget;
    QListWidget *listWidget;
    QTextEdit *textEdit;

    void retranslateUi(QMainWindow *MainWindow);
    void setupUi(QMainWindow *MainWindow);
    void populateFileList();
    void loadFileContent(const QString &filePath);

private:
    const QString logDirectory = "/home/ilyaveretennikov/MonitoringNetworkingSystem/Problems";
};

namespace Ui {
    class Server_logs: public UI_Server_logs {};
}

QT_END_NAMESPACE

#endif