#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100,100, 700,700);
    view = new QGraphicsView(this);
    view->setGeometry(50,50,600,600);
    view->showFullScreen();

    scene = new QGraphicsScene;
    view->setScene(scene);

    scaleOfCell = 40;
    numOfCell = 100;
    for(int i =0; i< numOfCell; i++)
    {
        scene->addLine(0,i* scaleOfCell,scaleOfCell*(numOfCell-1),i* scaleOfCell);
        scene->addLine(i* scaleOfCell,0,i* scaleOfCell,scaleOfCell*(numOfCell-1));
    }

    xStatic = 10;
    yStatic = 5;

    for(int i =0; i< numOfCell; i++)
    {
      drawLineOnGrid(i,0,xStatic, yStatic);
      drawLineOnGrid(i,numOfCell-1, xStatic, yStatic);
      drawLineOnGrid(0,i,xStatic, yStatic);
      drawLineOnGrid(numOfCell-1, i, xStatic, yStatic);
    }


    //drawLineOnGrid(1,2,19,8);

}
MainWindow::~MainWindow()
{

}

void MainWindow::bresenhamLine(int x1, int y1, int x2, int y2)
{
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    scene->addEllipse(x2*scaleOfCell,-(y2*scaleOfCell)+(numOfCell-1)*scaleOfCell,scaleOfCell/4,scaleOfCell/4);
    while(x1 != x2 || y1 != y2)
    {
        scene->addEllipse(x1*scaleOfCell,-(y1*scaleOfCell)+(numOfCell-1)*scaleOfCell,scaleOfCell/4,scaleOfCell/4);
        const int error2 = error * 2;
        if(error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
    }

}

void MainWindow::drawLineOnGrid(int x1, int y1, int x2, int y2)
{
    QPen pen;
    pen.setBrush(Qt::red);

    scene->addLine(x1*scaleOfCell,-(y1*scaleOfCell)+(numOfCell-1)*scaleOfCell,x2*scaleOfCell,-(y2*scaleOfCell)+(numOfCell-1)*scaleOfCell,pen);
    bresenhamLine(x1, y1, x2, y2);
}
