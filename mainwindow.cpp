#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), drawSurfaceWidget(0)
{
    drawSurfaceWidget = new DrawSurfaceWidget(parent);
    this->setCentralWidget(drawSurfaceWidget);

    resize(MAIN_WINDOW_DEFAULT_WIDTH, MAIN_WINDOW_DEFAULT_HEIGHT);
}

MainWindow::~MainWindow()
{
    delete drawSurfaceWidget;
}
