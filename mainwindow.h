#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTextItem>

#define N 100
#define M 100

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int map[N][M];
    int heightOfRobot;
    int xStatic;
    int yStatic;
    int scaleOfCell;//масштаб клеток
    int numOfCell;//количество точек в сетке
    QGraphicsScene* scene;
    QGraphicsView* view;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void bresenhamLine(int x1, int y1, int x2, int y2);
    void drawLineOnGrid(int x1, int y1, int x2, int y2);
};

#endif // MAINWINDOW_H
