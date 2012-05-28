#ifndef CUBE_H
#define CUBE_H

#include "glshape.h"

class Cube : public GLShape
{
public:
    Cube(const QGLContext *context = 0);

    void drawWithIBO();
    int tupleSize() const;
};

#endif // CUBE_H
