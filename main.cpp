#include <QtWidgets/QApplication>
#include "ElysiaUpdater.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    ElysiaUpdater window;
    window.show();
    
    return app.exec();
}