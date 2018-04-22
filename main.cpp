#include <QApplication>
#include "demo.h"
int main(int argc,char **argv)
{
    QApplication a(argc,argv);
    Demo dialog;

    dialog.show();
    return a.exec();
}
