#include <QDebug>
#include "drawsurfacewidget.h"
#include "glutils.h"

#define ABS(x) (x < 0 ? -x : x)

DrawSurfaceWidget::DrawSurfaceWidget(QWidget *parent) :
    QGLWidget(parent), drawVertices(true), drawEdges(true), drawDualVertices(true),
    drawDualEdges(true), pointsAlgorithm(0), selected(false)
{
}

DrawSurfaceWidget::~DrawSurfaceWidget() {}

void DrawSurfaceWidget::initializeGL() {
    //set background color to white
    glClearColor(1.0, 1.0, 1.0, 1.0);

    //nice looking anti-aliased lines
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLineWidth(0.75);
}

void DrawSurfaceWidget::resizeGL(int width, int height) {
    //change viewport to new dimensions
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);

    //use an orthographic projection in the same dimensions as the draw surface
    glOrtho(0, width, height, 0, -1, 0);

    glMatrixMode(GL_MODELVIEW);
}

void DrawSurfaceWidget::paintGL() {
    //clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //draw vertices
    if (drawVertices) {
        glColor3f(0,0,0);
        for (uint i = 0; i < vertices.size(); i++) {
            Vector2f v = vertices[i];
            if (selected && selectedIndex == i) {
                glColor3f(0,0,1);
                glDrawCircle(v[0], v[1], VERTEX_RADIUS);
                glColor3f(0,0,0);
            } else {
                glDrawCircle(v[0], v[1], VERTEX_RADIUS);
            }
        }
    }

    //draw edges
    if (drawEdges) {
        glColor3f(0,0,0);
        for (list<Edge>::iterator it = edges.begin(); it != edges.end(); it++) {
            Edge e = *it;
            Vector2f v1 = e.u;
            Vector2f v2 = e.v;

            glBegin(GL_LINES);
            glVertex2f(v1[0],v1[1]);
            glVertex2f(v2[0],v2[1]);
            glEnd();
        }
    }

    //draw dual vertices;
    if (drawDualVertices) {
        glColor3f(1,0,0);
        for (list<Vector2f>::iterator it = dualVertices.begin(); it != dualVertices.end(); it++) {
            Vector2f v = *it;
            glDrawCircle(v[0], v[1], VERTEX_RADIUS);
        }
    }

    //draw dual edges
    if (drawDualEdges) {
        for (list<Edge>::iterator it = dualEdges.begin(); it != dualEdges.end(); it++) {
            Edge e = *it;
            Vector2f v1 = e.u;
            Vector2f v2 = e.v;

            glBegin(GL_LINES);
            glVertex2f(v1[0],v1[1]);
            glVertex2f(v2[0],v2[1]);
            glEnd();
        }
    }
}

void DrawSurfaceWidget::updateGraph() {
    if (pointsAlgorithm) {
        edges = pointsAlgorithm->getEdges();
        dualVertices = pointsAlgorithm->getDualVertices();
        dualEdges = pointsAlgorithm->getDualEdges();
    } else {
        edges.clear();
        dualVertices.clear();
        dualEdges.clear();
    }
}

void DrawSurfaceWidget::mousePressEvent(QMouseEvent *event) {
    float x = (float)event->x();
    float y = (float)event->y();

    //iterate through vertices and see if point clicked is inside a vertex
    selected = false;
    for (uint i = 0; i < vertices.size(); i++) {
        Vector2f v = vertices[i];
        if (abs(v[0]-x) <= VERTEX_RADIUS && abs(v[1]-y) <= VERTEX_RADIUS) {
            selected = true;
            selectedIndex = i;
            break;
        }
    }

    if (selected && event->button() == Qt::RightButton) {
        //remove vertex if right mouse button is clicked
        vertices.erase(vertices.begin() + selectedIndex);
        if (pointsAlgorithm) {
            pointsAlgorithm->removeVertex(selectedIndex);
        }
        selected = false;
    } else if (!selected && event->button() == Qt::LeftButton) {
        //add a new vertex and calculate new edges
        Vector2f v(x,y);
        vertices.push_back(v);
        if (pointsAlgorithm) {
            pointsAlgorithm->addVertex(v);
        }
    }

    updateGraph();
    repaint();
}

void DrawSurfaceWidget::mouseMoveEvent(QMouseEvent *event) {
    if (selected) {
        float x = (float)event->x();
        float y = (float)event->y();
        vertices[selectedIndex] = Vector2f(x,y);

        if (pointsAlgorithm) {
            pointsAlgorithm->moveVertex(selectedIndex,vertices[selectedIndex]);
        }

        updateGraph();
        repaint();
    }
}

void DrawSurfaceWidget::mouseReleaseEvent(QMouseEvent *) {
    selected = false;
    repaint();
}

void DrawSurfaceWidget::clear() {
    if (pointsAlgorithm) {
        pointsAlgorithm->reset();
    }

    vertices.clear();
    edges.clear();
    dualVertices.clear();
    dualEdges.clear();
    repaint();
}

/*SLOTS*/
void DrawSurfaceWidget::changeAlgorithm(PointsAlgorithm *algorithm) {
    this->pointsAlgorithm = algorithm;
    if (this->pointsAlgorithm) {
        this->pointsAlgorithm->setVertices(vertices);
    }

    updateGraph();
    repaint();
}

void DrawSurfaceWidget::toggleVertices(bool on) {
    toggle(drawVertices, on);
}

void DrawSurfaceWidget::toggleEdges(bool on) {
    toggle(drawEdges, on);
}

void DrawSurfaceWidget::toggleDualVertices(bool on) {
    toggle(drawDualVertices, on);
}

void DrawSurfaceWidget::toggleDualEdges(bool on) {
    toggle(drawDualEdges, on);
}

void DrawSurfaceWidget::toggle(bool &setting, bool on) {
    setting = on;
    repaint();
}
