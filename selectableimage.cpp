#include "SelectableImage.h"
#include <QApplication>
#include <QMimeData>
#include <QKeyEvent>
#include <iostream>


void SelectableImage::focusInEvent(QFocusEvent* event) {
    this->setStyleSheet("border: 1px solid red");
}

void SelectableImage::focusOutEvent(QFocusEvent* event) {
    this->setStyleSheet("");
}
