#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QCheckbox>


class Preferences : public QDialog {
    Q_OBJECT

public:
    Preferences(QWidget* parent = nullptr);

    int thumbnailSize = 200;
    int tolerance = 100;
    bool drawBorder = true;

private slots:
    void accept();
    void reject();

private:
    QLineEdit* thumbnailSizeEdit;
    QLineEdit* toleranceEdit;
    QCheckBox* borderCheckbox;
    QDialogButtonBox* buttonBox;
};

#endif // PREFERENCES_H