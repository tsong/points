#ifndef DRAWSURFACEWIDGET_H
#define DRAWSURFACEWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>

#include "vector.h"

using namespace std;

class DrawSurfaceWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit DrawSurfaceWidget(QWidget *parent = 0);

protected:
    /*OpenGL methods*/
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);

protected:
    list<Vector2f> vertices;

};

#endif // DRAWSURFACEWIDGET_H
