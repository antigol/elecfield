#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLShaderProgram>
#include <QtOpenGL/QGLBuffer>
#include <QtOpenGL/QGLFramebufferObject>
#include "cube.h"
#include "sphere.h"

#include <QTime>

class GLWidget : public QGLWidget
{
    Q_OBJECT
    
public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void paintEvent(QPaintEvent *e);
    void timerEvent(QTimerEvent * e);
    void keyPressEvent(QKeyEvent *e);

private:
    void initializeCharge(int i);
    void initializeAllCharges();

    QGLShaderProgram *program;
    Cube *cube;
    Sphere *sphere;
    GLShape *current;

    int vertexLocation;
    int matrixProjectionLocation;
    int matrixViewLocation;
    int matrixModelLocation;
    int chargesPositionLocation;
    int chargesValueLocation;

    QVector<QVector3D> chargesPos;
    QVector<QVector3D> chargesSpe;
    QVector<GLfloat> chargesVal;

    QTime time;
    float angle;
    int fps;
};

#endif // GLWIDGET_H
