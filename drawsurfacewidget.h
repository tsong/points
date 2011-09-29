#ifndef DRAWSURFACEWIDGET_H
#define DRAWSURFACEWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>

#include "vector.h"
#include "mstalgorithm.h"

using namespace std;

class DrawSurfaceWidget : public QGLWidget {
    Q_OBJECT
public:
    DrawSurfaceWidget(QWidget *parent = 0);
    ~DrawSurfaceWidget();

protected:
    /*OpenGL methods*/
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);

protected:
    vector<Vector2f> vertices;
    list<Edge> edges;
    PointsAlgorithm *pointsAlgorithm;

};

#endif // DRAWSURFACEWIDGET_H
