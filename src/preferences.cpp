#include "preferences.h"

#include <QString>
#include <QVBoxLayout>


Preferences::Preferences(QWidget* parent) : QDialog(parent) {
    thumbnailSize = defaultThumbnailSize;
    tolerance = defaultTolerance;

    setWindowTitle("Preferences");
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    // initialize thumbnail line edits
    thumbnailSizeEdit = new QLineEdit(this);
    QHBoxLayout* thumbnailLayout = lineEditWithLabels(this, thumbnailSizeEdit, "Thumbnail size:", "px", "200", "Square size of thumbnails generated and displayed from loaded files", new QIntValidator(1, 10000, this));
    mainLayout->addLayout(thumbnailLayout);

    toleranceEdit = new QLineEdit(this);
    QHBoxLayout* toleranceLayout = lineEditWithLabels(this, toleranceEdit, "Tolerance:", "px", "100", "Row tolerance when generating image grid coordinates. Recommended to be less than or equal to 50% of the thumbnail size.", new QIntValidator(1, 10000, this));
    mainLayout->addLayout(toleranceLayout);

    // border checkbox and label
    borderCheckbox = new QCheckBox("Draw border on selected image", this);
    borderCheckbox->setChecked(drawBorder);
    mainLayout->addWidget(borderCheckbox);
    
    // Ok/Cancel buttons
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &Preferences::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &Preferences::reject);
    mainLayout->addWidget(buttonBox);
}

void Preferences::accept() {
    if (!thumbnailSizeEdit->text().isEmpty())
        thumbnailSize = thumbnailSizeEdit->text().toInt();  // previously validated with line edit validator
    else
        thumbnailSize = defaultThumbnailSize;

    if (!toleranceEdit->text().isEmpty())
        tolerance = toleranceEdit->text().toInt();
    else
        tolerance = defaultTolerance;

    drawBorder = borderCheckbox->isChecked();

    QDialog::accept();
}

void Preferences::reject() {
    QDialog::reject();
}

QHBoxLayout* lineEditWithLabels(QWidget* parent, QLineEdit* lineEdit, const QString& leadingLabelText, const QString& trailingLabelText, const QString& placeholder, const QString& tooltip, const QIntValidator* validator) {
    // set line edit parameters
    lineEdit->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);
    lineEdit->setPlaceholderText(placeholder);
    lineEdit->setToolTip(tooltip);
    lineEdit->setValidator(validator);
    
    // create label pointers
    QLabel* leadingLabel = new QLabel(leadingLabelText, parent);
    QLabel* trailingLabel = new QLabel(trailingLabelText, parent);

    // layout with labels before and after
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(leadingLabel);
    layout->addWidget(lineEdit);
    layout->addWidget(trailingLabel);

    return layout;
}

QHBoxLayout* lineEditWithLabels(QWidget* parent, QLineEdit* lineEdit, const QString& leadingLabelText, const QString& trailingLabelText, int placeholder, const QString& tooltip, const QIntValidator* validator) {
    QString plString = QString::number(placeholder);
    return lineEditWithLabels(parent, lineEdit, leadingLabelText, trailingLabelText, plString, tooltip, validator);
}
