#ifndef MOVABLEIMAGE_H
#define MOVABLEIMAGE_H

#include <QLabel>
#include <QKeyEvent>
#include <QFocusEvent>


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

private:
    QPixmap original;
    double opacity = 1.0;
};

#endif // MOVABLEIMAGE_H
