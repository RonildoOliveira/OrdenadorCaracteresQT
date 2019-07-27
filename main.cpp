#include "selecaopjwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SelecaoPJWindow w;
    w.show();

    return a.exec();
}
