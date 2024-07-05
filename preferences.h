#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>

class Preferences : public QDialog {
    Q_OBJECT

public:
    explicit Preferences(QWidget* parent = nullptr);
};

#endif // PREFERENCES_H