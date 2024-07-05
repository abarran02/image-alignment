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

private slots:
    void accept();
    void reject();

private:
    QDialogButtonBox* buttonBox;
    QLabel* label;
    QLabel* label_2;
    QLineEdit* thumbnailSize;
};

#endif // PREFERENCES_H