#ifndef DRAWSURFACEWIDGET_H
#define DRAWSURFACEWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>

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
    std::vector< std::pair<double,double> > points;

};

#endif // DRAWSURFACEWIDGET_H
