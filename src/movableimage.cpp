#include "movableimage.h"

#include <QPainter>


MovableImage::MovableImage(QWidget* parent, QString filename, int thumbnailSize)
    : filename(filename), thumbnailSize(thumbnailSize)
{
    setParent(parent);
    loadPixmap(filename);
    setMouseTracking(true);
}

void MovableImage::loadPixmap(QString filename) {
    QPixmap pixmap(filename);  // load file

    // save image and thumbnail
    QSize size(thumbnailSize, thumbnailSize);
    original = pixmap;
    thumbnail = pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // create image widget and adjust to pixmap size
    setFixedSize(thumbnail.size());
    setPixmap(thumbnail);
    setFocusPolicy(Qt::ClickFocus);
    move(QPoint(0, 0));

    show();  // render widget
}

std::string MovableImage::getFilename() {
    return filename.toStdString();
}

void MovableImage::setOpacity(double newOpacity) {
    opacity = newOpacity;

    QPixmap result(thumbnail.size());
    result.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&result);
    painter.setOpacity(opacity);
    painter.drawPixmap(0, 0, thumbnail);

    // draw 1px red border if in focus
    // won't resize image like with setStyleSheet()
    if (hasFocus() && drawBorder) {
        QPen pen(Qt::red, 1);
        painter.setPen(pen);
        painter.drawRect(0, 0, width() - 1, height() - 1);
    }

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
    int step = 2;

    switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_A:
        move(x() - step, y());
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        move(x() + step, y());
        break;
    case Qt::Key_Up:
    case Qt::Key_W:
        move(x(), y() - step);
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
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
    default:
        QLabel::keyPressEvent(event); // Pass other keys to base class
    }
}

void MovableImage::focusOutEvent(QFocusEvent* event) {
    setOpacity(opacity);  // force redraw without red border
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

bool MovableImage::operator<(const MovableImage& cmp) const {
    return x() < cmp.x();
}
