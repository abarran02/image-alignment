#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QPixmap>
#include <QPoint>


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // create menu bar
    QMenu* fileMenu = menuBar()->addMenu("File");

    // create menu bar actions 
    QAction* openImage = new QAction("Open Image", this);
    fileMenu->addAction(openImage);
    connect(openImage, &QAction::triggered, this, &MainWindow::openImage);  // connect to openImage slot

    // repeat for openDir
    QAction* openDir = new QAction("Open Image Directory", this);
    fileMenu->addAction(openDir);
    connect(openDir, &QAction::triggered, this, &MainWindow::openDir);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openImage() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image File", "", "Images (*.png *.jpg *.jpeg *.tif)");
    if (!fileName.isEmpty()) {
        MovableImage* image = new MovableImage(centralWidget(), fileName);
    }
}

void MainWindow::openDir() {
    QString directory = QFileDialog::getExistingDirectory(this, "Open Image Directory", QString(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!directory.isEmpty()) {
        // get images in selected directory
        QDir dir(directory);
        QStringList filters;
        filters << "*.png" << "*.jpg" << "*.jpeg" << "*.tif";
        dir.setNameFilters(filters);
        dir.setFilter(QDir::Files);

        // load each image
        QFileInfoList fileList = dir.entryInfoList();
        foreach(const QFileInfo& fileInfo, fileList) {
            MovableImage* image = new MovableImage(centralWidget(), fileInfo.absoluteFilePath());
        }
    }
}
