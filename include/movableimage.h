#ifndef MOVABLEIMAGE_H
#define MOVABLEIMAGE_H

#include <QLabel>
#include <QKeyEvent>
#include <QFocusEvent>
#include <QMouseEvent>


class MovableImage : public QLabel {
    Q_OBJECT

public:
    explicit MovableImage(QWidget* parent = nullptr, QString filename = "", int thumbnailSize = 200);
    
    void loadPixmap(QString filename);

    void setOpacity(double opacity);
    void incrementOpacity(double step);
    void decrementOpacity(double step);

    bool operator<(const MovableImage& cmp) const;

    int thumbnailSize;
    double opacity = 1.0;
    bool opacityIsDefault = true;
    bool drawBorder = true;

protected:
    void keyPressEvent(QKeyEvent* event);
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
};

#endif // MOVABLEIMAGE_H
