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

    delaunayMode();
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
    clearAction->setShortcut(QKeySequence("Ctrl+C"));
    connect(clearAction, SIGNAL(triggered()), drawSurfaceWidget, SLOT(clear()));
    editMenu->addAction(clearAction);

    //mode menu
    QMenu *modeMenu = menuBar()->addMenu("&Mode");
    QAction *mstAction = new QAction("&Minimum Spanning Tree", this);
    QAction *delaunayAction = new QAction("Delaunay &Triangulation", this);
    QAction *voronoiAction = new QAction("&Voronoi Diagram", this);
    QAction *delaunayVoronoiAction = new QAction("&Delaunay/Voronoi", this);

    connect(mstAction, SIGNAL(triggered()), this, SLOT(mstMode()));
    connect(delaunayAction, SIGNAL(triggered()), this, SLOT(delaunayMode()));
    connect(voronoiAction, SIGNAL(triggered()), this, SLOT(voronoiMode()));
    connect(delaunayVoronoiAction, SIGNAL(triggered()), this, SLOT(delaunayVoronoiMode()));

    modeMenu->addAction(mstAction);
    modeMenu->addAction(delaunayAction);
    modeMenu->addAction(voronoiAction);
    modeMenu->addAction(delaunayVoronoiAction);
}

void MainWindow::mstMode() {
    drawSurfaceWidget->changeAlgorithm(&mstAlgorithm);
    drawSurfaceWidget->toggleVertices(true);
    drawSurfaceWidget->toggleEdges(true);
    drawSurfaceWidget->toggleDualEdges(false);
    drawSurfaceWidget->toggleDualVertices(false);
}

void MainWindow::delaunayMode() {
    drawSurfaceWidget->changeAlgorithm(&triangulationAlgorithm);
    drawSurfaceWidget->toggleVertices(true);
    drawSurfaceWidget->toggleEdges(true);
    drawSurfaceWidget->toggleDualEdges(false);
    drawSurfaceWidget->toggleDualVertices(false);
}

void MainWindow::voronoiMode() {
    drawSurfaceWidget->changeAlgorithm(&voronoiAlgorithm);
    drawSurfaceWidget->toggleVertices(true);
    drawSurfaceWidget->toggleEdges(false);
    drawSurfaceWidget->toggleDualEdges(true);
    drawSurfaceWidget->toggleDualVertices(true);
}

void MainWindow::delaunayVoronoiMode() {
    drawSurfaceWidget->changeAlgorithm(&voronoiAlgorithm);
    drawSurfaceWidget->toggleVertices(true);
    drawSurfaceWidget->toggleEdges(true);
    drawSurfaceWidget->toggleDualEdges(true);
    drawSurfaceWidget->toggleDualVertices(true);
}

