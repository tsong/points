#include <QDebug>
#include "drawsurfacewidget.h"

DrawSurfaceWidget::DrawSurfaceWidget(QWidget *parent) :
    QGLWidget(parent)
{
}


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

    //draw points
    glBegin(GL_POINTS);
    {
        for (int i = 0; i < points.size(); i++) {
            std::pair<double,double> p = points[i];
            glVertex2f(p.first, p.second);
            qDebug() << p.first << " " << p.second;
        }
    }
    glEnd();

}


void DrawSurfaceWidget::mousePressEvent(QMouseEvent *event) {
    //normalize mouse coordinates
    double x = (double)event->x() / (double)this->width();
    double y = 1.0 - (double)event->y() / (double) this->height();

    points.push_back(std::pair<double,double>(x,y));
    repaint();
}
