#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "movableimage.h"
#include "preferences.h"

#include <QMainWindow>


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
    void createAction(QMenu* menu, const QString& text, const char* member);

    std::vector<MovableImage*> images;
    Preferences* preferences;
};

#endif // MAINWINDOW_H
