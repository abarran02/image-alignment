#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QPixmap>
#include <QKeyEvent>
#include <iostream>


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // create menu bar actions 
    QMenu* fileMenu = menuBar()->addMenu("File");
    QAction* openAction = new QAction("Open Image", this);
    fileMenu->addAction(openAction);

    // Connect the open action to the openImage slot
    connect(openAction, &QAction::triggered, this, &MainWindow::openImage);

    // Create and set the vertical layout
    QVBoxLayout* layout = new QVBoxLayout(centralWidget());
    centralWidget()->setLayout(layout);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openImage() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image File", "", "Images (*.png *.xpm *.jpg *.jpeg *.bmp *.gif)");
    if (!fileName.isEmpty()) {
        QPixmap pixmap(fileName);  // load file

        // create image widget and adjust to pixmap size
        SelectableImage* image = new SelectableImage(this);
        image->setFixedSize(pixmap.size());
        image->setPixmap(pixmap);
        image->setFocusPolicy(Qt::ClickFocus);

        // render widget and adjust the size of the vertical layout to fit the image
        ui->verticalLayout->addWidget(image);
        ui->verticalLayout->setGeometry(QRect(image->pos(), pixmap.size()));
    }
}
