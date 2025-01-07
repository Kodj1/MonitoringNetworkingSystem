#include "Autorization.h"
#include "Menu.h"
#include <QApplication>

void Ui_Autorization_Window::setupUi(QMainWindow *MainWindow)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(271, 236);
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    pushButton = new QPushButton(centralwidget);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(90, 160, 87, 27));
    lineEdit = new QLineEdit(centralwidget);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
    lineEdit->setGeometry(QRect(40, 70, 191, 27));
    lineEdit_2 = new QLineEdit(centralwidget);
    lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
    lineEdit_2->setGeometry(QRect(40, 110, 191, 27));
    label = new QLabel(centralwidget);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(90, 30, 91, 19));
    MainWindow->setCentralWidget(centralwidget);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);

    retranslateUi(MainWindow);

    // Store the main window pointer
    mainWindow = MainWindow;

    // Connect the signal clicked to the slot openMenu
    QObject::connect(pushButton, &QPushButton::clicked, this, &Ui_Autorization_Window::openMenu);

    QMetaObject::connectSlotsByName(MainWindow);
}

void Ui_Autorization_Window::retranslateUi(QMainWindow *MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Авторизация", nullptr));
    pushButton->setText(QCoreApplication::translate("MainWindow", "Войти", nullptr));
    label->setText(QCoreApplication::translate("MainWindow", "Авторизация", nullptr));
}

void Ui_Autorization_Window::openMenu()
{
    // Create a new Menu window
    QMainWindow *menuWindow = new QMainWindow();
    Ui::Menu *menu = new Ui::Menu();
    menu->setupUi(menuWindow);
    menuWindow->show();
    
    // Close the Authorization window
    mainWindow->close();
}