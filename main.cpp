#include "widget.h"
#include <QApplication>
#include "GetCG.h"
#include "TheGui.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    (new TheGui)->makeGui();
    return a.exec();
}
