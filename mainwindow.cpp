#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QPixmap>
#include <QPoint>


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // create menu bar actions 
    QMenu* fileMenu = menuBar()->addMenu("File");
    QAction* openAction = new QAction("Open Image", this);
    fileMenu->addAction(openAction);

    // connect the open action to the openImage slot
    connect(openAction, &QAction::triggered, this, &MainWindow::openImage);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openImage() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image File", "", "Images (*.png *.xpm *.jpg *.jpeg *.bmp *.gif)");
    if (!fileName.isEmpty()) {
        QPixmap pixmap(fileName);  // load file

        // create image widget and adjust to pixmap size
        MovableImage* image = new MovableImage(this);
        image->setFixedSize(pixmap.size());
        image->setPixmap(pixmap);
        image->setFocusPolicy(Qt::ClickFocus);
        image->move(QPoint(0, 0));

        // render widget
        image->setParent(centralWidget());
        image->show();
    }
}
