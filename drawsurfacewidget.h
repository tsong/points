#ifndef DRAWSURFACEWIDGET_H
#define DRAWSURFACEWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>

#include "vector.h"
#include "pointsalgorithm.h"

#define VERTEX_RADIUS 6

using namespace std;

class DrawSurfaceWidget : public QGLWidget {
    Q_OBJECT
public:
    DrawSurfaceWidget(QWidget *parent = 0);
    ~DrawSurfaceWidget();

public slots:
    void clear();
    void changeAlgorithm(PointsAlgorithm *algorithm);
    void toggleVertices(bool on);
    void toggleEdges(bool on);
    void toggleDualVertices(bool on);
    void toggleDualEdges(bool on);

protected:
    void toggle(bool &setting, bool on);
    void updateGraph();

    /*OpenGL methods*/
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);

protected:
    bool drawVertices;
    bool drawEdges;
    bool drawDualVertices;
    bool drawDualEdges;

    vector<Vector2f> vertices;
    list<Edge> edges;

    list<Vector2f> dualVertices;
    list<Edge> dualEdges;

    PointsAlgorithm *pointsAlgorithm;

    bool selected;
    uint selectedIndex;
};

#endif // DRAWSURFACEWIDGET_H
