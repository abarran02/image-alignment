#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "movableimage.h"

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void openImage();
    void openDir();
    void generateGrid();

private:
    Ui::MainWindow* ui;
    std::vector<MovableImage*> images;
};

#endif // MAINWINDOW_H
