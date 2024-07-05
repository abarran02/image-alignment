#include "Preferences.h"

#include <QtUiTools/quiloader.h>
#include <QFile>
#include <QVBoxLayout>
#include <QWidget>


Preferences::Preferences(QWidget* parent) : QDialog(parent) {
    QUiLoader loader;

    QFile file(":preferences.ui");
    file.open(QFile::ReadOnly);

    QWidget* loadedWidget = loader.load(&file, this);
    file.close();

    if (loadedWidget) {
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(loadedWidget);
        setLayout(layout);
        resize(loadedWidget->size());
    }
}
