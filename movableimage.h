#ifndef MOVABLEIMAGE_H
#define MOVABLEIMAGE_H

#include <QLabel>
#include <QKeyEvent>
#include <QFocusEvent>
#include <QMouseEvent>


class MovableImage : public QLabel {
    Q_OBJECT

public:
    explicit MovableImage(QWidget* parent = nullptr, QString filename = "");
    
    void loadPixmap(QString filename);

    void setOpacity(double opacity);
    void incrementOpacity(double step);
    void decrementOpacity(double step);

protected:
    void keyPressEvent(QKeyEvent* event);
    void focusInEvent(QFocusEvent* event);
    void focusOutEvent(QFocusEvent* event);

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QString filename;
    QPixmap original;
    QPixmap thumbnail;

    QPoint mouseGrabPoint;
    QPoint imageGrabPoint;

    double opacity = 1.0;
    bool opacityIsDefault = true;
};

#endif // MOVABLEIMAGE_H
