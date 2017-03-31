#include <QApplication>
#include "glwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(a.applicationPid());



    GLWidget w(QGLFormat::defaultFormat());
    w.show();
    
    return a.exec();
}
