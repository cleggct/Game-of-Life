#include "life.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    life w;
    w.show();

    return a.exec();
}
