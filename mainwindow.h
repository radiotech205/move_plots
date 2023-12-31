#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_toolButton_clicked();
    void addRandomGraph(QCustomPlot *wdg);
    void setRange(QCPRange rng);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
