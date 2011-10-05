#include "mainwindow.h"
#include <QDebug>

#include "matrix.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), drawSurfaceWidget(0)
{
    drawSurfaceWidget = new DrawSurfaceWidget(parent);
    this->setCentralWidget(drawSurfaceWidget);

    resize(MAIN_WINDOW_DEFAULT_WIDTH, MAIN_WINDOW_DEFAULT_HEIGHT);

    Vector4f v(1,2,3,4);
    qDebug() << v[0] << v[1] << v[2] << v[3];

    Matrix4f M;
    M[0] = Vector4f(-2,2,-3,4);
    M[1] = Vector4f(-1,1,3,4);
    M[2] = Vector4f(2,0,-1,4);
    M[3] = Vector4f(1,-2,-3,4);
    qDebug() << M.det();
    /*qDebug() << "Matrix" << 0;
    for (uint i = 0; i < 3; i++) {
        qDebug() << M[i][0] << M[i][1] << M[i][2];
    }

    Matrix<int,2,2> C = M.cofactor(0,0);
    qDebug() << "Sub-matrix" << 0;
    for (uint i = 0; i < 3-1; i++) {
        qDebug() << C[i][0] << C[i][1];
    }*/

}

MainWindow::~MainWindow()
{
    delete drawSurfaceWidget;
}
