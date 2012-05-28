#include "glshape.h"

GLShape::GLShape(const QGLContext *context) :
    vbo(QGLBuffer::VertexBuffer),
    ibo(QGLBuffer::IndexBuffer)
{
    initializeGLFunctions(context);
}

GLenum GLShape::type() const
{
    return GL_FLOAT;
}

int GLShape::offset() const
{
    return 0;
}

int GLShape::stride() const
{
    return 0;
}

bool GLShape::bindVBO()
{
    return vbo.bind();
}

void GLShape::releaseVBO()
{
    vbo.release();
}

bool GLShape::bindIBO()
{
    return ibo.bind();
}

void GLShape::releaseIBO()
{
    ibo.release();
}
