#include "mainwindow.h"
#include <QDebug>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), drawSurfaceWidget(0)
{
    drawSurfaceWidget = new DrawSurfaceWidget(parent);
    this->setCentralWidget(drawSurfaceWidget);

    createMenus();

    resize(MAIN_WINDOW_DEFAULT_WIDTH, MAIN_WINDOW_DEFAULT_HEIGHT);
}

MainWindow::~MainWindow()
{
    delete drawSurfaceWidget;
}

void MainWindow::createMenus() {
    //file menu
    QMenu *fileMenu = menuBar()->addMenu("&File");
    QAction *exitAction = new QAction("E&xit",this);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    fileMenu->addAction(exitAction);

    //edit menu
    QMenu *editMenu = menuBar()->addMenu("&Edit");
    QAction *clearAction = new QAction("&Clear", this);
    connect(clearAction, SIGNAL(triggered()), drawSurfaceWidget, SLOT(clear()));
    editMenu->addAction(clearAction);

}
