#include "movableimage.h"

#include <QPainter>


MovableImage::MovableImage(QWidget* parent, QString filename)
    : filename(filename)
{
    setParent(parent);
    loadPixmap(filename);
    setMouseTracking(true);
}

void MovableImage::loadPixmap(QString filename) {
    QPixmap pixmap(filename);  // load file

    // save image and thumbnail
    QSize size(200, 200);
    original = pixmap;
    thumbnail = pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // create image widget and adjust to pixmap size
    setFixedSize(thumbnail.size());
    setPixmap(thumbnail);
    setFocusPolicy(Qt::ClickFocus);
    move(QPoint(0, 0));

    show();  // render widget
}

void MovableImage::setOpacity(double newOpacity) {
    opacity = newOpacity;

    QPixmap result(thumbnail.size());
    result.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&result);
    painter.setOpacity(opacity);
    painter.drawPixmap(0, 0, thumbnail);
    painter.end();

    setPixmap(result);
}

void MovableImage::incrementOpacity(double step) {
    double newOpacity = opacity + step;
    setOpacity(newOpacity > 1.0 ? 1.0 : newOpacity);

    opacityIsDefault = opacity == 1.0;
}

void MovableImage::decrementOpacity(double step) {
    double newOpacity = opacity - step;
    setOpacity(newOpacity < 0.1 ? 0.1 : newOpacity);

    opacityIsDefault = false;
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
    setStyleSheet("border: 1px solid red");
}

void MovableImage::focusOutEvent(QFocusEvent* event) {
    setStyleSheet("");
}

void MovableImage::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        grabMouse();
        mouseGrabPoint = event->globalPos();
        imageGrabPoint = pos();
            
        raise();
        if (opacityIsDefault)
            setOpacity(0.7);
    }
    else {
        event->ignore();
    }
}

void MovableImage::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        releaseMouse();

        if (opacityIsDefault)
            setOpacity(1.0);
    }
    else {
        event->ignore();
    }
}

void MovableImage::mouseMoveEvent(QMouseEvent* event) {
    if (hasFocus() && event->buttons() & Qt::LeftButton) {
        QPoint difference = event->globalPos() - mouseGrabPoint;
        move(imageGrabPoint + difference);
    }
    else {
        event->ignore();
    }
}
