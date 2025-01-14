#include <QApplication>
#include "Autorization.h"
#include "db_connection.cpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString connectionName = "my_unique_connection";
    Database db(connectionName);

    if (!db.isOpen()) {
        return -1; // Завершите приложение, если не удалось подключиться к базе данных
    }

    QMainWindow w;
    Ui::Autorization_Window auth;
    auth.setupUi(&w);
    w.show();
    return a.exec();
}