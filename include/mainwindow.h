#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "movableimage.h"
#include "preferences.h"
#include "gridimg.h"

#include <QMainWindow>
#include <QKeyEvent>


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void openImage();
    void openDir();
    void openPreferences();
    void setBorderPreference();

    std::vector<GridImg> generateGrid();

protected:
    void keyPressEvent(QKeyEvent* event);

private:
    void createAction(QMenu* menu, const QString& text, const char* member);

    std::vector<MovableImage*> images;
    Preferences* preferences;
};

#endif // MAINWINDOW_H
