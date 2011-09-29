#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define MAIN_WINDOW_DEFAULT_WIDTH 500
#define MAIN_WINDOW_DEFAULT_HEIGHT 500

#include <QMainWindow>

#include "drawsurfacewidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    DrawSurfaceWidget *drawSurfaceWidget;
};

#endif // MAINWINDOW_H
