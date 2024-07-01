#include "movableimage.h"

void MovableImage::keyPressEvent(QKeyEvent* event) {
    int step = 10;

    switch (event->key()) {
        case Qt::Key_Left:
            move(x() - step, y());
            break;
        case Qt::Key_Right:
            move(x() + step, y());
            break;
        case Qt::Key_Up:
            move(x(), y() - step);
            break;
        case Qt::Key_Down:
            move(x(), y() + step);
            break;
        case Qt::Key_Z:
            lower();
            break;
        case Qt::Key_X:
            raise();
            break;
        case Qt::Key_Delete:
            delete this;
            break;
        default:
            QLabel::keyPressEvent(event); // Pass other keys to base class
    }
}

void MovableImage::focusInEvent(QFocusEvent* event) {
    this->setStyleSheet("border: 1px solid red");
}

void MovableImage::focusOutEvent(QFocusEvent* event) {
    this->setStyleSheet("");
}
