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


    //QVector<QColor> colors = kmeans(fileName, clusters, satThreshold);

    std::string file = fileName.toUtf8().constData();
    QPixmap pixmap(fileName);
    ui->imageLabel->setPixmap(pixmap);

    QVector<QColor> colors = colorDetector.kmeansFiltered(file, clusters, satThreshold);
    QVector<QFrame*> frames;
    frames.push_back(ui->color1);
    frames.push_back(ui->color2);
    frames.push_back(ui->color3);
    frames.push_back(ui->color4);
    frames.push_back(ui->color5);

    for(int i = 0; i < colors.size(); i++){
        QPalette pal(palette());
        pal.setColor(QPalette::Background, colors.at(i));
        QFrame* frame = frames.at(i);
        frame->setAutoFillBackground(true);
        frame->setPalette(pal);
    }

}
