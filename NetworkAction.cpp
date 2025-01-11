#include "NetworkAction.h"
#include "Menu.h"
#include <QApplication>


void Ui_Network_window::setupUi(QMainWindow *MainWindow)
    {
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
        pushButton->setGeometry(QRect(10, 450, 121, 27));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(530, 450, 31, 27));
        QIcon icon;
        icon.addFile(QString::fromUtf8("MonitoringNetworkingSystem/icons/icons8-\320\277\320\276\320\270\321\201\320\272-50.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_2->setIcon(icon);
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(410, 450, 113, 27));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void Ui_Network_window::retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\241\320\265\321\202\320\265\320\262\320\260\321\217 \320\260\320\272\321\202\320\270\320\262\320\275\320\276\321\201\321\202\321\214", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\222 \320\263\320\273\320\260\320\262\320\275\320\276\320\265 \320\274\320\265\320\275\321\216", nullptr));
        pushButton_2->setText(QString());
    }

 	void Ui_Network_window::openWindow()
	{
    QMainWindow *networkWindow = new QMainWindow();
    Ui::Network_Window *net_win = new Ui::Network_Window();
    net_win->setupUi(networkWindow);
    networkWindow->show();
	}