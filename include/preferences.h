#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QCheckbox>
#include <QHBoxLayout>
#include <QIntValidator>


class Preferences : public QDialog {
    Q_OBJECT

public:
    Preferences(QWidget* parent = nullptr);

    int thumbnailSize;
    int tolerance;
    bool drawBorder = true;

private slots:
    void accept();
    void reject();

private:
    QLineEdit* thumbnailSizeEdit;
    QLineEdit* toleranceEdit;
    QCheckBox* borderCheckbox;
    QDialogButtonBox* buttonBox;

    int defaultThumbnailSize = 200;
    int defaultTolerance = 100;
};

QHBoxLayout* lineEditWithLabels(QWidget* parent, QLineEdit* lineEdit, const QString& leadingLabelText, const QString& trailingLabelText, const QString& placeholder, const QString& tooltip, const QIntValidator* validator);
QHBoxLayout* lineEditWithLabels(QWidget* parent, QLineEdit* lineEdit, const QString& leadingLabelText, const QString& trailingLabelText, int placeholder, const QString& tooltip, const QIntValidator* validator);

#endif // PREFERENCES_H
