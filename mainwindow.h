#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "movableimage.h"
#include "preferences.h"

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
    void openPreferences();

private:
    Ui::MainWindow* ui;
    std::vector<MovableImage*> images;
    Preferences* preferences;
};

#endif // MAINWINDOW_H
