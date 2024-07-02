#include "movableimage.h"

#include <QPainter>


MovableImage::MovableImage(QWidget* parent, QString filename) {
    setParent(parent);
    loadPixmap(filename);
    original = pixmap()->copy();
}

void MovableImage::loadPixmap(QString filename) {
    QPixmap pixmap(filename);  // load file

    // create image widget and adjust to pixmap size
    setFixedSize(pixmap.size());
    setPixmap(pixmap);
    setFocusPolicy(Qt::ClickFocus);
    move(QPoint(0, 0));

    show();  // render widget
}

void MovableImage::setOpacity(double newOpacity) {
    opacity = newOpacity;

    QPixmap result(original.size());
    result.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&result);
    painter.setOpacity(opacity);
    painter.drawPixmap(0, 0, original);
    painter.end();

    setPixmap(result);
}

void MovableImage::incrementOpacity(double step) {
    double newOpacity = opacity + step;
    setOpacity(newOpacity > 1.0 ? 1.0 : newOpacity);
}

void MovableImage::decrementOpacity(double step) {
    double newOpacity = opacity - step;
    setOpacity(newOpacity < 0.1 ? 0.1 : newOpacity);
}

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
    case Qt::Key_N:
        decrementOpacity(0.1);
        break;
    case Qt::Key_M:
        incrementOpacity(0.1);
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
