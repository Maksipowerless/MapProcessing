#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qsrand (QDateTime::currentMSecsSinceEpoch());
    this->setGeometry(100,100, 700,700);
    view = new QGraphicsView(this);
    view->setGeometry(50,50,600,600);
    view->showFullScreen();

    scene = new QGraphicsScene;
    view->setScene(scene);

    scaleOfCell = 40;
    numOfCell = N;
    xStatic = 10;
    yStatic = 5;
    heightOfRobot = 3;

    for(int i=0; i<numOfCell; i++)
        for(int j=0; j<numOfCell; j++)
            map[i][j] = qrand() % 8 +1;

    for(int i=0; i< numOfCell; i++)
    {
        scene->addLine(0,i* scaleOfCell,scaleOfCell*(numOfCell-1),i* scaleOfCell);
        scene->addLine(i* scaleOfCell,0,i* scaleOfCell,scaleOfCell*(numOfCell-1));
    }


    for(int i =0; i< 1; i++)
    {
        drawLineOnGrid(xStatic, yStatic, i,0);
        //drawLineOnGrid(xStatic, yStatic,i,numOfCell-1);
        //drawLineOnGrid(xStatic, yStatic,0,i);
        // drawLineOnGrid(xStatic, yStatic,numOfCell-1, i);
    }

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
    int maxHeight = -123;//самый высокий участок
    int count = 0;//cчеткик кол-ва точек
    int xS = x1;//координаты стационарной
    int yS = y1;//точки
    QVector<QPair<int,int>> versities;
    QVector<QPair<int,int>> coord;

    map[x1][y1] = 10;
    while(x1 != x2 || y1 != y2)
    {
        count++;
        //scene->addEllipse(x1*scaleOfCell,-(y1*scaleOfCell)+(numOfCell-1)*scaleOfCell,scaleOfCell/4,scaleOfCell/4);
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

        QPair<int,int> pair;
        pair.first = count;
        pair.second = map[x1][y1];
        versities.push_back(pair);

        pair.first = x1;
        pair.second = y1;

        coord.push_back(pair);
    }
    findDarkArea(coord,versities, xS, yS);
}

void MainWindow::drawLineOnGrid(int x1, int y1, int x2, int y2)
{
    QPen pen;
    pen.setBrush(Qt::red);

    scene->addLine(x1*scaleOfCell,-(y1*scaleOfCell)+(numOfCell-1)*scaleOfCell,x2*scaleOfCell,
                   -(y2*scaleOfCell)+(numOfCell-1)*scaleOfCell,pen);
    bresenhamLine(x1, y1, x2, y2);
}

void MainWindow::findDarkArea(QVector<QPair<int, int> >& coord, QVector<QPair<int, int> >& versities, int xS, int yS)
{
    float alpha = 0;
    QPair<int,int> tempPair;
    for(int i=0; i<versities.size(); i++)
    {
        float A = versities[i].first;
        float B = sqrt(pow(versities[i].first, 2) + pow((10 - versities[i].second), 2));
        float temp = 0;
        temp = A/B;
        if(temp > alpha)
        {
            alpha = temp;
            tempPair = coord[i];
        }
    }
    scene->addEllipse(tempPair.first*scaleOfCell,-(tempPair.second*scaleOfCell)+(numOfCell-1)*scaleOfCell,
                      scaleOfCell/4,scaleOfCell/4);
}


/* while(x1 != x2 || y1 != y2)
    {
        //scene->addEllipse(x1*scaleOfCell,-(y1*scaleOfCell)+(numOfCell-1)*scaleOfCell,scaleOfCell/4,scaleOfCell/4);
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
        if(maxHeight == -123)
            maxHeight = map[x1][y1];

        if(map[x1][y1] > maxHeight)
            maxHeight = map[x1][y1];

        if(map[x1][y1] + heightOfRobot <= maxHeight)
        {
            map[x1][y1] = 999;
            scene->addEllipse(x1*scaleOfCell,-(y1*scaleOfCell)+(numOfCell-1)*scaleOfCell,scaleOfCell/4,scaleOfCell/4);
        }
    }*/
