#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H

#include <QObject>
#include <QVector>
#include <QColor>

#include "opencv2/core.hpp"

class ColorDetector : public QObject
{
    Q_OBJECT
public:
    ColorDetector();

    QColor kmeansFiltered(std::string file, int clusters, int satThreshold);

    QVector<QColor> kmeansClustering(std::string file, int clusters, int satThreshold);
    QColor findMostCommonColor(QPixmap pixmap);

private:
    cv::Mat saturationFilter(cv::Mat src, int satThreshold);
    QColor chooseColor(QVector<QColor> clusters);

};

#endif // COLORDETECTOR_H
