#include "mainwindow.h"

#include <QFileDialog>
#include <QPixmap>
#include <QPoint>
#include <QMenuBar>


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), preferences(new Preferences(this)) {
    // create menu bar
    QMenuBar* menuBar = new QMenuBar(this);
    QMenu* fileMenu = new QMenu("File", this);
    menuBar->addMenu(fileMenu);

    // add menu options
    createAction(fileMenu, "Open Image", SLOT(openImage()));
    createAction(fileMenu, "Open Image Directory", SLOT(openDir()));
    createAction(fileMenu, "Generate Grid", SLOT(generateGrid()));
    createAction(fileMenu, "Preferences", SLOT(openPreferences()));

    setMenuBar(menuBar);

    // create central widget
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    resize(640, 480);
}

MainWindow::~MainWindow() {
    delete preferences;
}

void MainWindow::createAction(QMenu* menu, const QString& text, const char* member) {
    QAction* action = new QAction(text, this);
    menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, member);
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
            MovableImage* image = new MovableImage(centralWidget(), fileInfo.absoluteFilePath(), preferences->thumbnailSize);
            images.push_back(image);
        }
    }
}

void MainWindow::generateGrid() {
    if (images.empty())
        return;

    std::vector<std::vector<MovableImage*>> rows = { { images[0] } };
    int tolerance = preferences->tolerance;

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
    for (std::vector< MovableImage*> row : rows) {
        std::stable_sort(row.begin(), row.end(),[](MovableImage* a, MovableImage* b) { return *a < *b; });
    }

    // sort rows by y-coordinate
    std::sort(rows.begin(), rows.end(),
        [](std::vector<MovableImage*> a, std::vector<MovableImage*> b) { return a[0] < b[0]; });

    // need to decide some output acceptable by the other application
}

void MainWindow::openPreferences() {
    preferences->show();
    preferences->raise();
    preferences->activateWindow();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Delete) {
        QWidget* fw = focusWidget();

        // remove widget from images vector
        auto it = std::remove(images.begin(), images.end(), fw);
        images.erase(it, images.end());

        // deallocate image
        delete fw;
    }
}
