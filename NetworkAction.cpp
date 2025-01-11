#include "NetworkAction.h"
#include "Menu.h"
#include <QApplication>
#include <QMainWindow>
#include <QNetworkInterface>
#include <QTcpSocket>
#include <QStandardItemModel>
#include <QTreeView>
#include <QHostAddress>
#include <QList>
#include <QStringList>
#include <QPushButton>
#include <QLineEdit>
#include <QIcon>
#include <QProcess>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QMutex>
#include <QMutexLocker>
#include <QException>
#include <QMessageBox>
#include <QThreadPool>
#include <QFutureWatcher>
#include <QHostInfo>

void Ui_Network_Window::setupUi(QMainWindow *MainWindow) {
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(570, 485);
    
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    
    treeView = new QTreeView(centralwidget);
    treeView->setObjectName(QString::fromUtf8("treeView"));
    treeView->setGeometry(QRect(0, 0, 571, 441));
    
    pushButton = new QPushButton(centralwidget);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(10, 450, 140, 27));
    pushButton->setText(QCoreApplication::translate("MainWindow", "Сканирование сети", nullptr));
   
    MainWindow->setCentralWidget(centralwidget);

    retranslateUi(MainWindow);

    QObject::connect(pushButton, &QPushButton::clicked, this, [this]() {
        QString startIP = "192.168.0.0";
        QString endIP = "192.168.0.255";
        ScanNetwork(startIP, endIP);
    });

    QMetaObject::connectSlotsByName(MainWindow);
}

void Ui_Network_Window::retranslateUi(QMainWindow *MainWindow) {
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Сетевое сканирование", nullptr));
    pushButton->setText(QCoreApplication::translate("MainWindow", "Сканирование сети", nullptr));
   }

QString Ui_Network_Window::getHostIpAddress() {
    QString ipAddress;
    const QList<QHostAddress> &addresses = QNetworkInterface::allAddresses();
    for (const QHostAddress &address : addresses) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress::LocalHost) {
            ipAddress = address.toString();
            break;
        }
    }
    return ipAddress;
}

QString Ui_Network_Window::getHostName(const QHostAddress &address) {
    QHostInfo hostInfo = QHostInfo::fromName(address.toString());
    if (!hostInfo.hostName().isEmpty()) {
        return hostInfo.hostName();
    } else {
        return "Unknown";
    }
}

bool Ui_Network_Window::isHostAlive(const QString &ip) {
    QTcpSocket socket;
    socket.connectToHost(ip, 80); // Проверка доступности хоста по порту 80
    return socket.waitForConnected(100);
}

QStringList Ui_Network_Window::scanPorts(const QHostAddress &address, const QList<int> &portsToScan) {
    QStringList openPorts;
    for (int port : portsToScan) {
        QTcpSocket *socket = new QTcpSocket();
        socket->connectToHost(address, port);
        if (socket->waitForConnected(10)) {
            openPorts.append(QString::number(port));
            socket->disconnectFromHost();
        }
        socket->deleteLater();
    }
    return openPorts;
}

void Ui_Network_Window::ScanNetwork(const QString &startIP, const QString &endIP) {
    QStandardItemModel *model = new QStandardItemModel(treeView);
    model->setHorizontalHeaderLabels({"Host Name", "IP Address", "Ports"});

    QList<int> portsToScan = {80, 443, 8080};

    QHostAddress startAddress(startIP);
    QHostAddress endAddress(endIP);
    quint32 start = startAddress.toIPv4Address();
    quint32 end = endAddress.toIPv4Address();

    QString hostIpAddress = getHostIpAddress();
    QStringList hostOpenPorts = scanPorts(QHostAddress(hostIpAddress), portsToScan);
    QString hostName = getHostName(QHostAddress(hostIpAddress));

    QStandardItem *hostNameItem = new QStandardItem(hostName);
    QStandardItem *hostItem = new QStandardItem(hostIpAddress);
    QStandardItem *hostPortsItem = new QStandardItem(hostOpenPorts.join(", "));
    model->appendRow({hostNameItem, hostItem, hostPortsItem});

    QList<QFuture<void>> futures;
    QMutex mutex;

    QThreadPool::globalInstance()->setMaxThreadCount(50);

    QFutureWatcher<void> watcher;

    try {
        for (quint32 ip = start; ip <= end; ++ip) {
            QHostAddress address(ip);
            QString addressStr = address.toString();

            futures.append(QtConcurrent::run([this, address, addressStr, &portsToScan, model, &mutex]() {
                if (isHostAlive(addressStr)) {
                    QStringList openPorts = scanPorts(address, portsToScan);
                    QString hostName = getHostName(address);
                    if (!openPorts.isEmpty()) {
                        QString portsString = openPorts.join(", ");
                        QStandardItem *hostNameItem = new QStandardItem(hostName);
                        QStandardItem *ipItem = new QStandardItem(addressStr);
                        QStandardItem *portsItem = new QStandardItem(portsString);

                        QList<QStandardItem *> rowItems;
                        rowItems.append(hostNameItem);
                        rowItems.append(ipItem);
                        rowItems.append(portsItem);

                        QMutexLocker locker(&mutex);
                        model->appendRow(rowItems);
                    }
                }
            }));
        }

        watcher.setFuture(QtConcurrent::run([&futures]() {
            for (auto &future : futures) {
                future.waitForFinished();
            }
        }));

        watcher.waitForFinished();
    }
    catch (const std::exception &e) {
        QMessageBox::critical(nullptr, "Ошибка", e.what());
    }

    treeView->setModel(model);
}