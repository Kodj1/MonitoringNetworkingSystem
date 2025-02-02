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
    tabWidget->setGeometry(QRect(210, 10, 801, 708));

    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    QVBoxLayout *tabLayout = new QVBoxLayout(tab);
    tabLayout->setContentsMargins(0, 0, 0, 0); 
    tabWidget->addTab(tab, QString());

    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    QVBoxLayout *tab2Layout = new QVBoxLayout(tab_2);
    tab2Layout->setContentsMargins(0, 0, 0, 0);
    tabWidget->addTab(tab_2, QString());

    tab_3 = new QWidget();
    tab_3->setObjectName(QString::fromUtf8("tab_3"));
    QVBoxLayout *tab3Layout = new QVBoxLayout(tab_3);
    tab3Layout->setContentsMargins(0, 0, 0, 0);
    tabWidget->addTab(tab_3, QString());

    lineEdit = new QLineEdit(centralwidget);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
    lineEdit->setGeometry(QRect(10, 10, 121, 27));

    listWidget = new QListWidget(centralwidget);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));
    listWidget->setGeometry(QRect(10, 50, 191, 708));

    diskUsageWidget = new DiskUsageWidget(tab_2);
    tab2Layout->addWidget(diskUsageWidget);

    cpuUsageWidget = new CpuUsageWidget(tab_3);
    tab3Layout->addWidget(cpuUsageWidget);

    memUsageWidget = new MemUsageWidget(tab);
    tabLayout->addWidget(memUsageWidget);

    MainWindow->setCentralWidget(centralwidget);

    retranslateUi(MainWindow);

    tabWidget->setCurrentIndex(0);

    this->mainWindow = MainWindow;

    populateListWidget();

    // Подключение сигнала к слоту
    connect(listWidget, &QListWidget::itemClicked, this, &Ui_Host_stats::onListWidgetItemClicked);

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

void Ui_Host_stats::updateDiskUsage(qreal used_disk, qreal total_disk)
{
    diskUsageWidget->setDiskUsage(used_disk, total_disk);
}

void Ui_Host_stats::updateCpuUsage(qreal used_cpu, qreal total_cpu)
{
    cpuUsageWidget->setCpuUsage(used_cpu, total_cpu);
}

void Ui_Host_stats::updateMemUsage(qreal used_mem, qreal total_mem)
{
    memUsageWidget->setMemUsage(used_mem, total_mem);
}

void Ui_Host_stats::onListWidgetItemClicked(QListWidgetItem *item)
{
    QString hostname = item->text();

    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(mainWindow, "Database Error", "Database is not open.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT cpu_usage, total_cpu, memory_usage, total_memory, disk_usage_gb, total_disk_gb FROM metrics WHERE hostname = :hostname");
    query.bindValue(":hostname", hostname);

    if (!query.exec()) {
        QMessageBox::critical(mainWindow, "Query Error", query.lastError().text());
        return;
    }

    if (query.next()) {
        qreal cpuUsage = query.value(0).toDouble();
        qreal totalCpu = query.value(1).toDouble();
        qreal memUsage = query.value(2).toDouble();
        qreal totalMemory = query.value(3).toDouble();
        qreal diskUsage = query.value(4).toDouble();
        qreal totalDisk = query.value(5).toDouble();
        
        updateCpuUsage(cpuUsage,totalCpu);
        updateMemUsage(memUsage,totalMemory);
        updateDiskUsage(diskUsage, totalDisk);  // Пример общего объема, замените на реальное значение если необходимо
    } else {
        QMessageBox::information(mainWindow, "No Data", "No metrics found for the selected host.");
    }
}