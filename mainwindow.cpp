#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QPixmap>
#include <QPoint>
#include <QDebug>


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

    // repeat for generateGrid
    QAction* generateGrid = new QAction("Generate Grid", this);
    fileMenu->addAction(generateGrid);
    connect(generateGrid, &QAction::triggered, this, &MainWindow::generateGrid);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openImage() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image File", "", "Images (*.png *.jpg *.jpeg *.tif)");
    if (!fileName.isEmpty()) {
        MovableImage* image = new MovableImage(centralWidget(), fileName);
        images.push_back(image);
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
            images.push_back(image);
        }
    }
}

void MainWindow::generateGrid() {
    if (images.empty())
        return;

    std::vector<std::vector<MovableImage*>> rows = { { images[0] } };
    int tolerance = 100;

    // iterate over images 1...
    for (int img = 1; img < images.size(); img++) {
        bool added = false;
        // check whether it belongs in each row
        for (int row = 0; row < rows.size(); row++) {
            if (images[img]->y() < rows[row][0]->y() + tolerance
                && images[img]->y() > rows[row][0]->y() - tolerance) {  // within +/- tolerance of the top edge of the first image in the row
                rows[row].push_back(images[img]);
                added = true;
            }
        }

        if (!added)
            // wasn't within the tolerance of any row, so add new row
            rows.push_back({ images[img] });
    }

    // sort images in each row by x-coordinate
    for (auto& row : rows) {
        std::sort(row.begin(), row.end());
    }

    // need to decide some output acceptable by the other application
}
