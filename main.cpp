#include "createfieldwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CreateFieldWindow w;
    w.show();
    return a.exec();
}
