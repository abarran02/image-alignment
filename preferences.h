#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>


class Preferences : public QDialog {
    Q_OBJECT

public:
    Preferences(QWidget* parent = nullptr);

    int thumbnailSize = 200;
    int tolerance = 100;

private slots:
    void accept();
    void reject();

private:
    QLineEdit* thumbnailSizeEdit;
    QLineEdit* toleranceEdit;
    QDialogButtonBox* buttonBox;
};

#endif // PREFERENCES_H