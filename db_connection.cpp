// db_connection.cpp
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QString>
#include <QDebug>

class Database {
public:
    Database(const QString &connectionName) {
        db = QSqlDatabase::addDatabase("QPSQL", connectionName);
        db.setHostName("127.0.0.1");
        db.setDatabaseName("mns");
        db.setUserName("postgres");
        db.setPassword("your_password");

        if (!db.open()) {
            QMessageBox::critical(nullptr, "Database Error", db.lastError().text());
        } else {
            qDebug() << "Connected to database successfully";
        }
    }

    ~Database() {
        QString connectionName = db.connectionName();
        db.close();
        QSqlDatabase::removeDatabase(connectionName);
        qDebug() << "Closed database connection successfully";
    }

    bool isOpen() const {
        return db.isOpen();
    }

    QSqlError lastError() const {
        return db.lastError();
    }

private:
    QSqlDatabase db;
};