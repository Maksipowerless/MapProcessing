#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTextItem>
#include <QTime>
#include <QMap>
#include <QPair>

#define N 20

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int map[N][N];
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
    void bresenhamLine(int x1, int y1, int x2, int y2);//стоит линию по Брезенхэму(первый парамнтр стационарная точка)
    void drawLineOnGrid(int x1, int y1, int x2, int y2);
    void findDarkArea(QVector<QPair<int,int>>& coord, QVector<QPair<int,int>>& versities, int xS, int yS);
};

#endif // MAINWINDOW_H
