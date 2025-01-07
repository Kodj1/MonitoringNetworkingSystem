#include <QApplication>
#include "Autorization.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    Ui::Autorization_Window auth;
    auth.setupUi(&w);
    w.show();
    return a.exec();
}