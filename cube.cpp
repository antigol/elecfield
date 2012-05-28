#include "cube.h"
#include <QVector3D>
#include <QDebug>

Cube::Cube(const QGLContext *context) :
    GLShape(context)
{
    if (!vbo.create() || !vbo.bind())
        qDebug() << "VBO error";

    QVector<QVector3D> vertices;
    for (int i = 0; i < 8; ++i)
        vertices << QVector3D((i & 1) ? -1.0 : 1.0,
                              (i & 2) ? -1.0 : 1.0,
                              (i & 4) ? -1.0 : 1.0);
    /*
      front (z = 1)
        1     0

        3     2

      back (z = -1)
        5     4

        7     6

      */

    vbo.allocate(vertices.constData(), vertices.size() * sizeof (GLfloat) * 3);
    vbo.release();

    if (!ibo.create() || !ibo.bind())
        qDebug() << "IBO error";

    const GLubyte indices[] = {
        3, 2, 0, 1,
        2, 6, 4, 0,
        6, 7, 5, 4,
        5, 7, 3, 1,
        1, 0, 4, 5,
        2, 3, 7, 6
    };
    ibo.allocate(indices, 4 * 6 * sizeof (GLubyte));
    ibo.release();
}

void Cube::drawWithIBO()
{
    glDrawElements(GL_QUADS, 4 * 6, GL_UNSIGNED_BYTE, 0);
}

int Cube::tupleSize() const
{
    return 3;
}
