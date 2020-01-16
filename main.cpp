#include "QHtml.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QHtml w;
    w.show();
    return a.exec();
}
