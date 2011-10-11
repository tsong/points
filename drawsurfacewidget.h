#ifndef DRAWSURFACEWIDGET_H
#define DRAWSURFACEWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>

#include "vector.h"
#include "mstalgorithm.h"

#define VERTEX_RADIUS 5

using namespace std;

class DrawSurfaceWidget : public QGLWidget {
    Q_OBJECT
public:
    DrawSurfaceWidget(QWidget *parent = 0);
    ~DrawSurfaceWidget();

protected:
    void updateGraph();

    /*OpenGL methods*/
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);

protected:
    vector<Vector2f> vertices;
    list<Edge> edges;

    list<Vector2f> dualVertices;
    list<Edge> dualEdges;

    PointsAlgorithm *pointsAlgorithm;

    bool selected;
    uint selectedIndex;
};

#endif // DRAWSURFACEWIDGET_H
