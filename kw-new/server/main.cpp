#include "serverui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    int port = 27030;
    if (argc > 1) {
        port = atoi(argv[1]);
    }

    QApplication a(argc, argv);
    ServerUi w(port);
    w.show();

    return a.exec();
}
