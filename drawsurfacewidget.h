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
    //clears all vertices and edges
    void clear();

    //change the algorithm and reapply with current points
    void changeAlgorithm(PointsAlgorithm *algorithm);

    /*toggle draw settings*/
    void toggleVertices(bool on);
    void toggleEdges(bool on);
    void toggleDualVertices(bool on);
    void toggleDualEdges(bool on);

protected:
    //toggles a setting on or off and repaints the scene
    void toggle(bool &setting, bool on);

    //updates the vertices and edges and repaints the scene
    void updateGraph();

    /*OpenGL events*/
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    /*mouse events*/
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);

protected:
    /*controls which elements to draw*/
    bool drawVertices;
    bool drawEdges;
    bool drawDualVertices;
    bool drawDualEdges;

    //primary vertices and edges
    vector<Vector2f> vertices;
    list<Edge> edges;

    //secondary vertices and edges
    list<Vector2f> dualVertices;
    list<Edge> dualEdges;

    //algorithm used to generate vertices and edges
    PointsAlgorithm *pointsAlgorithm;

    //tracks selected vertex for movement
    bool selected;
    uint selectedIndex;
};

#endif // DRAWSURFACEWIDGET_H
