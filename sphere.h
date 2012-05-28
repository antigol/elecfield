#ifndef SPHERE_H
#define SPHERE_H

#include "glshape.h"

class Sphere : public GLShape
{
public:
    Sphere(const QGLContext *context = 0);
    Sphere(GLint slices, GLint stacks, const QGLContext *context = 0);
    ~Sphere();

    void drawWithIBO();
    int tupleSize() const;

private:
    void init(GLint slices , GLint stacks);

    GLuint vbo_sz;
    GLuint ibo_sz[3];
};

#endif // SPHERE_H
