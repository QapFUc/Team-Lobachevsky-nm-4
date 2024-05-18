#include "widget.h"

#include <QApplication>

sig_atomic_t exitFlag = 0;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Widget w;
    w.show();
    return app.exec();
}
