#ifndef MOVABLEIMAGE_H
#define MOVABLEIMAGE_H

#include <QLabel>
#include <QKeyEvent>
#include <QFocusEvent>


class MovableImage : public QLabel {
    Q_OBJECT

public:
    explicit MovableImage(QWidget* parent = nullptr) {};

protected:
    void keyPressEvent(QKeyEvent* event);
    void focusInEvent(QFocusEvent* event);
    void focusOutEvent(QFocusEvent* event);
};

#endif // MOVABLEIMAGE_H
