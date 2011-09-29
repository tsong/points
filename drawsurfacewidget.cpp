#include <QDebug>
#include "drawsurfacewidget.h"
#include "glutils.h"



DrawSurfaceWidget::DrawSurfaceWidget(QWidget *parent) :
    QGLWidget(parent), pointsAlgorithm(0)
{
    pointsAlgorithm = MSTAlgorithm::getInstance();
}

DrawSurfaceWidget::~DrawSurfaceWidget() {}

void DrawSurfaceWidget::initializeGL() {
    //set background color to white
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glPointSize(6.0);
}

void DrawSurfaceWidget::resizeGL(int width, int height) {
    //change viewport to new dimensions
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);

    //the projection matrix is a square of width and length 1.0
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
}

void DrawSurfaceWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(0,0,0);

    //draw vertices
    for (vector<Vector2f>::iterator it = vertices.begin(); it != vertices.end(); it++) {
        Vector2f v = *it;
        glDrawCircle(v[0], v[1]);
    }

    //draw edges
    for (list<Edge>::iterator it = edges.begin(); it != edges.end(); it++) {
        Edge e = *it;
        Vector2f v1 = *e.u;
        Vector2f v2 = *e.v;

        glBegin(GL_LINES);
        glVertex2f(v1[0],v1[1]);
        glVertex2f(v2[0],v2[1]);
        glEnd();

        //qDebug() << e[0] << " " << e[1];
        //qDebug() << QString("(%1,%2) -- (%3,%4)").arg(v1[0]).arg(v1[1]).arg(v2[0]).arg(v2[1]);
    }
}


void DrawSurfaceWidget::mousePressEvent(QMouseEvent *event) {
    //normalize mouse coordinates
    float x = (double)event->x() / (double)this->width();
    float y = 1.0 - (double)event->y() / (double) this->height();

    Vector2f v(x,y);
    //qDebug() << v[0] << " " << v[1];

    vertices.push_back(Vector2f(x,y));
    if (pointsAlgorithm)
        edges = pointsAlgorithm->getEdges(vertices);

    qDebug() << "# Edges: " << edges.size();
    repaint();
}
