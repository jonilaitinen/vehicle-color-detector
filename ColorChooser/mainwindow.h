#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_loadButton_clicked();

private:
    Ui::MainWindow *ui;


    void processImage(QString fileName);
    void processKmean(QString filename);
    QVector<QColor> kmeans(QString file, int clusters, int satThreshold);
    QVector<QColor> kmeansFiltered(QString file, int clusters, int satThreshold);

};

#endif // MAINWINDOW_H
