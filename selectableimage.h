#ifndef DRAGGABLELABEL_H
#define DRAGGABLELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>


class SelectableImage : public QLabel {
    Q_OBJECT

public:
    explicit SelectableImage(QWidget* parent = nullptr) {};

protected:
    void focusInEvent(QFocusEvent* event);
    void focusOutEvent(QFocusEvent* event);
};

#endif // DRAGGABLELABEL_H
