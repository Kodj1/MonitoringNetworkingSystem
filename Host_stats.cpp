#include "Host_stats.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QVBoxLayout>

void Ui_Host_stats::setupUi(QMainWindow *MainWindow)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(1024, 768); // Увеличьте начальный размер окна

    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));

    pushButton = new QPushButton(centralwidget);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(140, 10, 51, 27));

    tabWidget = new QTabWidget(centralwidget);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tabWidget->setGeometry(QRect(210, 10, 801, 708)); // Увеличьте размер tabWidget

    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    QVBoxLayout *tabLayout = new QVBoxLayout(tab);
    tabLayout->setContentsMargins(0, 0, 0, 0); 
    tabWidget->addTab(tab, QString());

    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    QVBoxLayout *tab2Layout = new QVBoxLayout(tab_2);
    tab2Layout->setContentsMargins(0, 0, 0, 0);  // Уберите отступы, чтобы график занимал все пространство
    tabWidget->addTab(tab_2, QString());

    tab_3 = new QWidget();
    tab_3->setObjectName(QString::fromUtf8("tab_3"));
    QVBoxLayout *tab3Layout = new QVBoxLayout(tab_3);
    tab3Layout->setContentsMargins(0, 0, 0, 0);  // Уберите отступы, чтобы график занимал все пространство
    tabWidget->addTab(tab_3, QString());

    lineEdit = new QLineEdit(centralwidget);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
    lineEdit->setGeometry(QRect(10, 10, 121, 27));

    listWidget = new QListWidget(centralwidget);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));
    listWidget->setGeometry(QRect(10, 50, 191, 708)); // Увеличьте высоту listWidget

    diskUsageWidget = new DiskUsageWidget(tab_2);
    tab2Layout->addWidget(diskUsageWidget);

    cpuUsageWidget = new CpuUsageWidget(tab_3);
    tab3Layout->addWidget(cpuUsageWidget);

    memUsageWidget = new MemUsageWidget(tab);  // Инициализируйте новый виджет
    tabLayout->addWidget(memUsageWidget);

    MainWindow->setCentralWidget(centralwidget);

    retranslateUi(MainWindow);

    tabWidget->setCurrentIndex(0);

    this->mainWindow = MainWindow;

    // Populate the list widget when the UI is set up
    populateListWidget();
    updateDiskUsage();
    updateCpuUsage(75);
    updateMemUsage(50);  // Обновите использование памяти с тестовым значением

    QMetaObject::connectSlotsByName(MainWindow);
}

void Ui_Host_stats::retranslateUi(QMainWindow *MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Статистика хостов", nullptr));
    pushButton->setText(QCoreApplication::translate("MainWindow", "Найти", nullptr));
    tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Загрузка памяти", nullptr));
    tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Информация о дисках", nullptr));
    tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Загрузка процессора", nullptr));
}

void Ui_Host_stats::populateListWidget()
{
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(mainWindow, "Database Error", "Database is not open.");
        return;
    }

    listWidget->clear();

    QSqlQuery query;
    query.prepare("SELECT hostname FROM nodes");

    if (!query.exec()) {
        QMessageBox::critical(mainWindow, "Query Error", query.lastError().text());
        return;
    }

    while (query.next()) {
        QString hostname = query.value(0).toString();
        listWidget->addItem(hostname);
    }
}

void Ui_Host_stats::updateDiskUsage()
{
    qreal used = 300;  // пример значения использования
    qreal total = 1000;  // пример общего объема

    diskUsageWidget->setDiskUsage(used, total);
}

void Ui_Host_stats::updateCpuUsage(qreal usage)
{
    cpuUsageWidget->setCpuUsage(usage);
}

void Ui_Host_stats::updateMemUsage(double usage)
{
    memUsageWidget->setMemUsage(usage);
}