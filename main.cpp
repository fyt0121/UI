#include "MainWinWithVBar.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FMainWinWithVBar w;
    w.showMaximized();

    return a.exec();
}
