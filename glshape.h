#ifndef GLSHAPE_H
#define GLSHAPE_H

#include <QtOpenGL/QGLFunctions>
#include <QtOpenGL/QGLBuffer>

class GLShape : protected QGLFunctions
{
public:
    GLShape(const QGLContext *context = 0);
	virtual ~GLShape();

    virtual GLenum type() const;
    virtual int offset() const;
    virtual int tupleSize() const = 0;
    virtual int stride() const;

    bool bindVBO();
    void releaseVBO();
    bool bindIBO();
    void releaseIBO();
    virtual void drawWithIBO() = 0;

protected:
    QGLBuffer vbo;
    QGLBuffer ibo;
};

#endif // GLSHAPE_H
