#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QGraphicsPixmapItem>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked(){

    QString fileName = ui->fileName->text();
    int clusters = ui->clusterSpinBox->value();
    int satThreshold = ui->satSpinBox->value();


    std::string file = fileName.toUtf8().constData();
    QPixmap pixmap(fileName);
    ui->imageLabel->setPixmap(pixmap);

    QColor color = colorDetector.kmeansFiltered(file, clusters, satThreshold);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, color);
    QFrame* frame = ui->color1;
    frame->setAutoFillBackground(true);
    frame->setPalette(pal);

}
