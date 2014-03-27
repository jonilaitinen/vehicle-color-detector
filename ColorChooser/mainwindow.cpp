#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qdebug.h>
#include <QGraphicsPixmapItem>

#include "opencv2/core/core.hpp"
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


    //processImage(fileName);
    //processKmean("C:/Users/user/Desktop/lorry/lorry204.jpg");

    //QVector<QColor> colors = kmeans(fileName, clusters, satThreshold);
    QVector<QColor> colors = kmeansFiltered(fileName, clusters, satThreshold);
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

void MainWindow::processImage(QString fileName){

    QPixmap pixmap(fileName);
    QImage image = pixmap.toImage();

    ui->imageLabel->setPixmap(pixmap);

    QRgb col;
    QMap<QRgb,int> rgbcount;
    QRgb greatest = 0;

    int width = pixmap.width();
    int height = pixmap.height();

    int count = 0;
    for (int i = 0; i < width; ++i){
        for (int j = 0; j < height; ++j){
            col = image.pixel(i, j);
            if (rgbcount.contains(col)) {
                rgbcount[col] = rgbcount[col] + 1;
            }
            else  {
                rgbcount[col] = 1;
            }

            if (rgbcount[col] > count)  {
                greatest = col;
                count = rgbcount[col];
            }

        }
    }
    qDebug() << "count: " << count << " greatest rgb: " << qRed(greatest) << " " << qGreen(greatest) << " " << qBlue(greatest);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(greatest));
    ui->color1->setAutoFillBackground(true);
    ui->color1->setPalette(pal);

}

QVector<QColor> MainWindow::kmeansFiltered(QString filename, int clusters, int satThreshold){

    std::string file = filename.toUtf8().constData();
    QPixmap pixmap(filename);
    ui->imageLabel->setPixmap(pixmap);

    cv::Mat src = cv::imread(file);
    src = src(cv::Rect(0, src.rows / 2, src.cols, src.rows / 2));
    cv::Mat srcHSV;
    // filter by saturation
    cv::cvtColor(src, srcHSV, CV_BGR2HSV);

    std::vector<cv::Mat> hsv_planes;
    cv::split(srcHSV, hsv_planes);
    cv::Mat saturation = hsv_planes[1];

    imshow("sat", saturation);

    QVector<cv::Vec3b> filtered;
    cv::Vec3b black;
    black[0] = 0;
    black[1] = 0;
    black[2] = 0;

    qDebug() << "filter";
    for( int y = 0; y < src.rows; y++ ){
        for( int x = 0; x < src.cols; x++ ){
            int pixel = saturation.at<unsigned char>(y, x);
            if(pixel > satThreshold){
                filtered.append(src.at<cv::Vec3b>(y,x));
            }
        }
    }

    qDebug() << "samples";
    cv::Mat samples(filtered.length(), 3, CV_32F);
    for(int count = 0; count < filtered.length(); count++ ){
        samples.at<float>(count, 0) = filtered.at(count)[0];
        samples.at<float>(count, 1) = filtered.at(count)[1];
        samples.at<float>(count, 2) = filtered.at(count)[2];
    }

    qDebug() << "calculate kmeans";

    cv::Mat labels;
    int attempts = 5;
    cv::Mat centers;
    cv::kmeans(samples, clusters, labels,
               cv::TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10, 0.1),
               attempts, cv::KMEANS_PP_CENTERS, centers);

   QVector<QColor> colors;

   for(int i = 0; i < clusters; i++){
       float b = centers.at<float>(i, 0);
       float g = centers.at<float>(i, 1);
       float r = centers.at<float>(i, 2);
       qDebug() << "cluster r: " << r << " g: " << g << " b: " << b;
       colors.push_back(QColor(r, g, b));
   }

   return colors;

}

QVector<QColor> MainWindow::kmeans(QString filename, int clusters, int satThreshold){

    std::string file = filename.toUtf8().constData();
    QPixmap pixmap(filename);
    ui->imageLabel->setPixmap(pixmap);

    cv::Mat src = cv::imread(file);
    src = src(cv::Rect(0, src.rows / 2, src.cols, src.rows / 2));
    cv::Mat srcHSV;
    // filter by saturation
    cv::cvtColor(src, srcHSV, CV_BGR2HSV);

    std::vector<cv::Mat> hsv_planes;
    cv::split(srcHSV, hsv_planes);
    cv::Mat saturation = hsv_planes[1];

    imshow("sat", saturation);

    cv::Vec3b black;
    black[0] = 0;
    black[1] = 0;
    black[2] = 0;


    cv::Mat samples(src.rows * src.cols, 3, CV_32F);
    for( int y = 0; y < src.rows; y++ ){
        for( int x = 0; x < src.cols; x++ ){
            int pixel = saturation.at<unsigned char>(y, x);
            //qDebug() << "sat: " << pixel;
            for( int z = 0; z < 3; z++){
                if(pixel > satThreshold){
                    samples.at<float>(y + x*src.rows, z) = src.at<cv::Vec3b>(y,x)[z];
                } else {
                    samples.at<float>(y + x*src.rows, z) = black[z];
                }
            }
        }
    }


    qDebug() << "calculate kmeans";

    cv::Mat labels;
    int attempts = 5;
    cv::Mat centers;
    cv::kmeans(samples, clusters, labels,
               cv::TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10, 0.1),
               attempts, cv::KMEANS_PP_CENTERS, centers);

    cv::Mat new_image( src.size(), src.type() );
    for( int y = 0; y < src.rows; y++ ){
       for( int x = 0; x < src.cols; x++ ){
           int cluster_idx = labels.at<int>(y + x*src.rows,0);
           new_image.at<cv::Vec3b>(y,x)[0] = centers.at<float>(cluster_idx, 0);
           new_image.at<cv::Vec3b>(y,x)[1] = centers.at<float>(cluster_idx, 1);
           new_image.at<cv::Vec3b>(y,x)[2] = centers.at<float>(cluster_idx, 2);
       }
   }
   imshow( "clustered image", new_image );

   QVector<QColor> colors;

   for(int i = 0; i < clusters; i++){
       float b = centers.at<float>(i, 0);
       float g = centers.at<float>(i, 1);
       float r = centers.at<float>(i, 2);
       qDebug() << "cluster r: " << r << " g: " << g << " b: " << b;
       colors.push_back(QColor(r, g, b));
   }

   return colors;

}
