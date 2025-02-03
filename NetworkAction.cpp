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
    pushButton->setGeometry(QRect(410, 450, 141, 27));
    pushButton->setText(QCoreApplication::translate("MainWindow", "Сканирование сети", nullptr));
   
    lineEdit = new QLineEdit(centralwidget);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
    lineEdit->setGeometry(QRect(10, 450, 113, 27));
    
    label = new QLabel(centralwidget);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(140, 450, 16, 20));
    
    lineEdit_2 = new QLineEdit(centralwidget);
    lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
    lineEdit_2->setGeometry(QRect(160, 450, 113, 27));

    MainWindow->setCentralWidget(centralwidget);

    retranslateUi(MainWindow);

    QObject::connect(pushButton, &QPushButton::clicked, this, [this]() {
        QString startIP = lineEdit->text();
        QString endIP = lineEdit_2->text();
        ScanNetwork(startIP, endIP);
    });
 
    QMetaObject::connectSlotsByName(MainWindow);
}

void Ui_Network_Window::retranslateUi(QMainWindow *MainWindow) {
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Сетевое сканирование", nullptr));
    pushButton->setText(QCoreApplication::translate("MainWindow", "Сканирование сети", nullptr));
    label->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
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
    QProcess pingProcess;
    QString command = "ping";
    QStringList arguments;
    arguments << "-c" << "1" << "-W" << "1" << ip; // "-c 1" для одного пакета и "-W 1" для таймаута в 1 секунду

    pingProcess.start(command, arguments);
    pingProcess.waitForFinished();
    
    QString output = pingProcess.readAllStandardOutput();
    QRegularExpression re("1 received");
    QRegularExpressionMatch match = re.match(output);
    
    return match.hasMatch();
}

QStringList Ui_Network_Window::scanPorts(const QHostAddress &address, const QList<int> &portsToScan) {
    QStringList openPorts;
    for (int port : portsToScan) {
        QTcpSocket socket;
        socket.connectToHost(address, port);
        if (socket.waitForConnected(2000)) { // Увеличиваем время ожидания до 2000 миллисекунд (2 секунды)
            openPorts.append(QString::number(port));
            socket.disconnectFromHost();
        }
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

    QList<QFuture<void>> futures;
    QMutex mutex;

    QThreadPool::globalInstance()->setMaxThreadCount(100);

    QFutureWatcher<void> watcher;

    try {
        for (quint32 ip = start; ip <= end; ++ip) {
            QHostAddress address(ip);
            QString addressStr = address.toString();

            futures.append(QtConcurrent::run([this, address, addressStr, &portsToScan, model, &mutex]() {
                if (isHostAlive(addressStr)) {
                    QStringList openPorts = scanPorts(address, portsToScan);
                    QString hostName = getHostName(address);
                    QMutexLocker locker(&mutex);
                    QStandardItem *hostNameItem = new QStandardItem(hostName);
                    QStandardItem *ipItem = new QStandardItem(addressStr);
                    QStandardItem *portsItem = new QStandardItem(openPorts.join(", "));
                    model->appendRow({hostNameItem, ipItem, portsItem});
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