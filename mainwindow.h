#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define MAIN_WINDOW_DEFAULT_WIDTH 640
#define MAIN_WINDOW_DEFAULT_HEIGHT 480

#include <QMainWindow>

#include "drawsurfacewidget.h"
#include "mstalgorithm.h"
#include "triangulationalgorithm.h"
#include "voronoialgorithm.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    /*Changes the mode of the draw surface */
    void noneMode();
    void mstMode();
    void delaunayMode();
    void voronoiMode();
    void delaunayVoronoiMode();

protected:
    void setDefaultDrawingMode();
    void createMenus();

protected:
    //surface which users interact with and draw the points
    DrawSurfaceWidget *drawSurfaceWidget;

    /*Points algorithms*/
    MSTAlgorithm mstAlgorithm;
    TriangulationAlgorithm triangulationAlgorithm;
    VoronoiAlgorithm voronoiAlgorithm;
};

#endif // MAINWINDOW_H
