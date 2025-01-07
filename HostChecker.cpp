#include "HostChecker.h"
#include "Menu.h"
#include <QApplication>

void Ui_HostChecker_Window::setupUi(QMainWindow *MainWindow)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(400, 300);
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    checkButton = new QPushButton(centralwidget);
    checkButton->setObjectName(QString::fromUtf8("checkButton"));
    checkButton->setGeometry(QRect(150, 200, 100, 30));
    lineEdit = new QLineEdit(centralwidget);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
    lineEdit->setGeometry(QRect(50, 50, 300, 27));
    resultText = new QTextEdit(centralwidget);
    resultText->setObjectName(QString::fromUtf8("resultText"));
    resultText->setGeometry(QRect(50, 100, 300, 80));
    resultText->setReadOnly(true);
    label = new QLabel(centralwidget);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(150, 20, 100, 19));
    MainWindow->setCentralWidget(centralwidget);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);

    retranslateUi(MainWindow);

    // Store the main window pointer
    mainWindow = MainWindow;

    // Connect the signal clicked to the slot checkHosts
    QObject::connect(checkButton, &QPushButton::clicked, this, &Ui_HostChecker_Window::checkHosts);

    QMetaObject::connectSlotsByName(MainWindow);
}

void Ui_HostChecker_Window::retranslateUi(QMainWindow *MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Проверка хостов", nullptr));
    checkButton->setText(QCoreApplication::translate("MainWindow", "Проверить", nullptr));
    label->setText(QCoreApplication::translate("MainWindow", "Проверка хостов", nullptr));
}

void Ui_HostChecker_Window::checkHosts()
{
    QStringList hosts = lineEdit->text().split(",", QString::SkipEmptyParts);
    resultText->clear();

    for (const QString &host : hosts) {
        QProcess process;
        process.start("ping", QStringList() << "-c" << "1" << host.trimmed());
        process.waitForFinished();
        resultText->append(process.readAllStandardOutput());
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    Ui_HostChecker_Window ui;
    ui.setupUi(&w);
    w.show();
    return a.exec();
}