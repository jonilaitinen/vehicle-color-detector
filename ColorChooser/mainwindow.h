#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "opencv2/core/core.hpp"
#include "colordetector.h"

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

    ColorDetector colorDetector;

};

#endif // MAINWINDOW_H
