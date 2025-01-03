#include <QApplication>
#include <QMainWindow>
#include "Autorization.h"
#include "Menu.h"
#include "Hosts.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow Autorization_Win;               // Главное окно
    Ui::Autorization_Window Autorization;       // Объект UI
    Autorization.setupUi(&Autorization_Win);    // Настройка интерфейса

    Autorization_Win.show();                    // Отображение окна


    QMainWindow MainMenu;               // Главное окно
    Ui::Menu Main_Menu;       // Объект UI
    Main_Menu.setupUi(&MainMenu);    // Настройка интерфейса

    MainMenu.show();                    // Отображение окна


  QMainWindow Hosts;               // Главное окно
    Ui::hosts Hosts_Win;       // Объект UI
    Hosts_Win.setupUi(&Hosts);    // Настройка интерфейса

    Hosts.show();                    // Отображение окна

    return app.exec();
}
