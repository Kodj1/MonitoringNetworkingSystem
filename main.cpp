#include <QApplication>
#include <QMainWindow>
#include "Autorization.h"
#include "Menu.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow Autorization_Win;               // Главное окно
    Ui::Autorization_Window Autorization;       // Объект UI
    Autorization.setupUi(&Autorization_Win);    // Настройка интерфейса

    Autorization_Win.show();                    // Отображение окна

    return app.exec();
}
