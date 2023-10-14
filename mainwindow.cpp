#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->qcustomPlot->setInteractions(QCP::iRangeDrag  | QCP::iSelectAxes | QCP::iSelectPlottables | QCP::iRangeZoom );
    ui->qcustomPlot->xAxis->setRange(-8, 8);
    ui->qcustomPlot->yAxis->setRange(-5, 5);

    ui->qcustomPlot->xAxis->setLabel("x Axis");
    ui->qcustomPlot->yAxis->setLabel("y Axis");
    ui->qcustomPlot->legend->setVisible(true);

    ui->qcustomPlot2->setInteractions(QCP::iRangeDrag  | QCP::iSelectAxes | QCP::iSelectPlottables | QCP::iRangeZoom );
    ui->qcustomPlot2->xAxis->setRange(-8, 8);
    ui->qcustomPlot2->yAxis->setRange(-5, 5);

    ui->qcustomPlot2->xAxis->setLabel("x Axis");
    ui->qcustomPlot2->yAxis->setLabel("y Axis");
    ui->qcustomPlot2->legend->setVisible(true);

    connect(ui->qcustomPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->qcustomPlot2->xAxis, SLOT(QCustomPlot::setRange(QCPRange)));
    //connect(ui->qcustomPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->qcustomPlot2->yAxis, SLOT(QCustomPlot::setRange(QCPRange)));

    connect(ui->qcustomPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(setRange(QCPRange)));


    addRandomGraph(ui->qcustomPlot);
    addRandomGraph(ui->qcustomPlot2);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_clicked()
{
    QCPRange rng = ui->qcustomPlot->xAxis->range();
    ui->qcustomPlot2->xAxis->setRange(rng);
    qDebug() << __FUNCTION__ << rng;
    ui->qcustomPlot2->replot();
}

void MainWindow::addRandomGraph(QCustomPlot *wdg)
{
  int n = 50; // number of points in graph
  double xScale = (rand()/(double)RAND_MAX + 0.5)*2;
  double yScale = (rand()/(double)RAND_MAX + 0.5)*2;
  double xOffset = (rand()/(double)RAND_MAX - 0.5)*4;
  double yOffset = (rand()/(double)RAND_MAX - 0.5)*10;
  double r1 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r2 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r3 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r4 = (rand()/(double)RAND_MAX - 0.5)*2;
  QVector<double> x(n), y(n);
  for (int i=0; i<n; i++)
  {
    x[i] = (i/(double)n-0.5)*10.0*xScale + xOffset;
    y[i] = (qSin(x[i]*r1*5)*qSin(qCos(x[i]*r2)*r4*3)+r3*qCos(qSin(x[i])*r4*2))*yScale + yOffset;
  }

  wdg->addGraph();
  wdg->graph()->setName(QString("New graph %1").arg(wdg->graphCount()-1));
  wdg->graph()->setData(x, y);
  wdg->graph()->setLineStyle((QCPGraph::LineStyle)(rand()%5+1));
  if (rand()%100 > 50)
    wdg->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1)));
  QPen graphPen;
  graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
  graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
  wdg->graph()->setPen(graphPen);
  wdg->replot();
}

void MainWindow::setRange(QCPRange rng)
{
    ui->qcustomPlot2->xAxis->setRange(rng);
    qDebug() << __FUNCTION__ << rng;
    ui->qcustomPlot2->replot();
}
