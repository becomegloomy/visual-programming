#include "PrintBufferWidget.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    PrintBufferWidget printBufferWidget;
    printBufferWidget.show();
    return app.exec();
}
