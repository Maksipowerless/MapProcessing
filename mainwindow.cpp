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
    heightOfRobot = 50;
    heightOfStantion = 120;

    for(int i=0; i<numOfCell; i++)
        for(int j=0; j<numOfCell; j++)
            map[i][j] = qrand() % 80 +5;

    map[xStatic][yStatic] = heightOfStantion;

    for(int i=0; i< numOfCell; i++)
    {
        scene->addLine(0,i* scaleOfCell,scaleOfCell*(numOfCell-1),i* scaleOfCell);
        scene->addLine(i* scaleOfCell,0,i* scaleOfCell,scaleOfCell*(numOfCell-1));
    }

    for(int i=0; i<numOfCell; i++)
    {
        QVector<QGraphicsEllipseItem*> temp;
        for(int j =0; j<numOfCell; j++)
        {
            temp.push_back(scene->addEllipse(i*scaleOfCell - 5,-(j*scaleOfCell)+(numOfCell-1)*scaleOfCell - 5,
                              scaleOfCell/4,scaleOfCell/4));
            temp.last()->setBrush(Qt::green);
        }
        points.push_back(temp);
    }

    for(int i =0; i<numOfCell; i++)
    {
        drawLineOnGrid(xStatic, yStatic, i,0);
        drawLineOnGrid(xStatic, yStatic,i,numOfCell-1);
        drawLineOnGrid(xStatic, yStatic,0,i);
        drawLineOnGrid(xStatic, yStatic,numOfCell-1, i);
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
    int count = 0;//cчеткик кол-ва точек

    QVector<QPair<int,int>> versities;
    QVector<QPair<int,int>> coord;

    while(x1 != x2 || y1 != y2)
    {
        count++;
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
    findDarkArea(coord,versities);
}

void MainWindow::drawLineOnGrid(int x1, int y1, int x2, int y2)
{
    QPen pen;
    pen.setBrush(Qt::red);

    scene->addLine(x1*scaleOfCell,-(y1*scaleOfCell)+(numOfCell-1)*scaleOfCell,x2*scaleOfCell,
                   -(y2*scaleOfCell)+(numOfCell-1)*scaleOfCell,pen);
    bresenhamLine(x1, y1, x2, y2);
}

void MainWindow::findDarkArea(QVector<QPair<int, int> >& coord, QVector<QPair<int, int> >& versities)
{
    float alpha = 0;
    QPair<int,int> tempPair;
    QPair<int,int> currentPoint;
    while(versities.size() != 0)
    {
        //поиск точки с меньшим полярным углом от стационарной
        for(int i=0; i<versities.size(); i++)
        {
            float A = versities[i].first;
            float B = sqrt(pow(versities[i].first, 2) + pow((heightOfStantion - versities[i].second), 2));
            float temp = 0;
            temp = A/B;
            if(temp > alpha)
            {
                alpha = temp;
                tempPair = coord[i];
                currentPoint = versities[i];
            }
        }

        //удаление точки, если она последняя
        int maxPoint = 0;
        for(int i=0; i<versities.size(); i++)
        {
            if(versities[i].first > maxPoint)
                maxPoint = versities[i].first;
        }

        if(currentPoint.first == maxPoint)
        {
            coord.removeOne(tempPair);
            versities.removeOne(currentPoint);
        }
        else
        {
            //проверка на видимость всех точек за текущей
            for(int i = versities.lastIndexOf(currentPoint) + 1; i< versities.size(); i++)
            {
                if(versities[i].second + heightOfRobot < currentPoint.second)
                {
                   // scene->addEllipse(coord[i].first*scaleOfCell - 5,-(coord[i].second*scaleOfCell)+(numOfCell-1)*scaleOfCell - 5,
                     //           scaleOfCell/4,scaleOfCell/4)->setBrush(Qt::black);
                    points[coord[i].first][coord[i].second]->setBrush(Qt::black);
                    coord.remove(i);
                    versities.remove(i);
                }
            }
            coord.removeOne(tempPair);
            versities.removeOne(currentPoint);
        }
        alpha = 0;
    }
}

