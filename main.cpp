#include "converter.hpp"

#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Converter w;
    //w.resize(700, 400);
    w.show();

    return a.exec();
}
