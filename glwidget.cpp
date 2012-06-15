#include "glwidget.h"
#include <QDebug>

GLWidget::GLWidget(const QGLFormat & format, QWidget *parent)
    : QGLWidget(format, parent), cube(0), sphere(0), current(0)
{
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAutoFillBackground(false);

    lastTime = 0.0;
    time.start();
    startTimer(0);
}

GLWidget::~GLWidget()
{
    if (cube) delete cube;
    if (sphere) delete sphere;
}

void GLWidget::initializeGL()
{
    program = new QGLShaderProgram(context(), this);
    program->addShaderFromSourceFile(QGLShader::Vertex, ":/shader/gl.vert");
    program->addShaderFromSourceFile(QGLShader::Fragment, ":/shader/gl.frag");
    if (!program->link())
        qDebug() << program->log();

    vertexLocation = program->attributeLocation("vertex");
    matrixProjectionLocation = program->uniformLocation("matrixp");
    matrixViewLocation = program->uniformLocation("matrixv");
    matrixModelLocation = program->uniformLocation("matrixm");
    chargesPositionLocation = program->uniformLocation("charges_position");
    chargesValueLocation = program->uniformLocation("charges_value");


    cube = new Cube(context());
    sphere = new Sphere(50.0, 50.0, context());
    current = cube;

    program->bind();
    program->setUniformValue("fixed_color", QColor(Qt::white));
    program->release();

    initializeAllCharges();
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    QMatrix4x4 m;
    m.perspective(45.0, qreal(w)/qreal(h?h:1), 0.1, 1000.0);

    if (!program->bind())
        qDebug() << program->log() << " (bind error)";

    program->setUniformValue(matrixProjectionLocation, m);
    program->release();
}

void GLWidget::paintGL()
{
    // test de profondeur
    glEnable(GL_DEPTH_TEST);

    // ne dessine pas les faces arrières
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    // gère la transparance
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 view;
    view.lookAt(QVector3D(3, 0, 2), QVector3D(0, 0, 0), QVector3D(0, 0, 1));

    QMatrix4x4 model;
    if (current == sphere)
        model.scale(1.5, 1.0, 1.0);

    view.rotate(angle, 0, 0, 1);

    if (!program->bind())
        qDebug() << program->log() << " (bind error)";

    program->enableAttributeArray(vertexLocation);
    program->setUniformValueArray(chargesPositionLocation, chargesPos.constData(), 4);
    program->setUniformValueArray(chargesValueLocation, (const GLfloat *)chargesVal.constData(), 4, 1);
    program->setUniformValue(matrixViewLocation, view);

    current->bindVBO();
    program->setAttributeBuffer(vertexLocation, current->type(), current->offset(), current->tupleSize());
    current->releaseVBO();

    /*
      0.2 * 1.1^n = 1
      1.1^n = 5
      ln(1.1^n) = ln(5)
      n*ln(1.1) = ln(5)
      n = ln(5) / ln(1.1)
      n = 17
      */
    current->bindIBO();
    model.scale(0.2);

    for (int i = 0; i < 17; ++i) {
        program->setUniformValue(matrixModelLocation, model);
        current->drawWithIBO();
        model.scale(1.1);
    }
    current->releaseIBO();

    program->disableAttributeArray(vertexLocation);
    program->release();
}

void GLWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    paintGL();

    QPainter painter(this);
    painter.setPen(Qt::yellow);
    painter.drawText(10, 20, "fps : " + QString::number(fps));

    painter.setPen(Qt::gray);
    painter.setFont(QFont("Helvetica", 8));
    painter.drawText(QRectF(10, 30, 210, 50), "press C to change object shape\npress Space to reinitialize charges");

    painter.end();
}

void GLWidget::timerEvent(QTimerEvent *)
{
    float t = float(time.elapsed());
    if (t - lastTime == 0.0)
        return;

    float dt = t - lastTime;
    lastTime = t;

    for (int i = 0; i < 4; ++i) {
        if (chargesPos[i].lengthSquared() > 100.0)
            initializeCharge(i);

        chargesPos[i] += dt * chargesSpe[i];
    }
    angle += dt * 0.005;
    fps = 1000.0 / dt;

    update();
}

#include <QKeyEvent>
void GLWidget::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Space) {
        initializeAllCharges();
        update();
    }
    if (e->key() == Qt::Key_C) {
        if (current == cube)
            current = sphere;
        else
            current = cube;
    }
}

void GLWidget::initializeCharge(int i)
{
    chargesPos[i] = QVector3D(double(qrand() % 1000 - 500) / 500.0,
                              double(qrand() % 1000 - 500) / 500.0,
                              double(qrand() % 1000 - 500) / 500.0);
    chargesSpe[i] = QVector3D(double(qrand() % 1000 - 500) / 500.0,
                              double(qrand() % 1000 - 500) / 500.0,
                              double(qrand() % 1000 - 500) / 500.0) * 0.00005;
    chargesVal[i] = 1e-6 * (qrand() % 30 - 15);
}

void GLWidget::initializeAllCharges()
{
    chargesPos.resize(4);
    chargesSpe.resize(4);
    chargesVal.resize(4);
    for (int i = 0; i < 4; ++i) {
        initializeCharge(i);
    }
}
