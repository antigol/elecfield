#include <QtGui/QApplication>
#include "glwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(a.applicationPid());


    if (QGLFormat::openGLVersionFlags().testFlag(QGLFormat::OpenGL_Version_3_3)) {
        qDebug("Run OpengGL version 3.3");

        // Specify an OpenGL 3.3 format using the Core profile.
        // That is, no old-school fixed pipeline functionality
        QGLFormat glFormat;
        glFormat.setVersion(3, 3);
        glFormat.setProfile(QGLFormat::CoreProfile); // Requires >=Qt-4.8.0
        glFormat.setSampleBuffers(true);
        GLWidget w(glFormat);
        w.show();

        return a.exec();
    } else {
        qDebug("Run OpengGL default version");

        GLWidget w(QGLFormat::defaultFormat());
        w.show();

        return a.exec();
    }
}
