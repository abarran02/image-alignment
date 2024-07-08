#include "preferences.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIntValidator>


Preferences::Preferences(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Preferences");

    // Ok/Cancel buttons
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &Preferences::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &Preferences::reject);

    // thumbnail size line edit
    QLabel* thumbailSizeLabel = new QLabel("Thumbnail size:", this);
    thumbnailSizeEdit = new QLineEdit(this);
    thumbnailSizeEdit->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);
    thumbnailSizeEdit->setPlaceholderText("200");
    thumbnailSizeEdit->setToolTip("Square size of thumbnails generated and displayed from loaded files");
    thumbnailSizeEdit->setValidator(new QIntValidator(1, 10000, this));

    // tolerance
    QLabel* toleranceLabel = new QLabel("Tolerance:", this);
    toleranceEdit = new QLineEdit(this);
    toleranceEdit->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);
    toleranceEdit->setPlaceholderText("100");
    toleranceEdit->setToolTip("Row tolerance when generating image grid coordinates. Recommended to be less than or equal to 50% of the thumbnail size.");
    toleranceEdit->setValidator(new QIntValidator(1, 10000, this));

    // layouts
    QHBoxLayout* thumbnailLayout = new QHBoxLayout;
    thumbnailLayout->addWidget(thumbailSizeLabel);
    thumbnailLayout->addWidget(thumbnailSizeEdit);
    thumbnailLayout->addWidget(new QLabel("px", this));

    QHBoxLayout* toleranceLayout = new QHBoxLayout;
    toleranceLayout->addWidget(toleranceLabel);
    toleranceLayout->addWidget(toleranceEdit);
    toleranceLayout->addWidget(new QLabel("px", this));

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(thumbnailLayout);
    mainLayout->addLayout(toleranceLayout);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
}

void Preferences::accept() {
    bool ok;
    if (!thumbnailSizeEdit->text().isEmpty())
        thumbnailSize = thumbnailSizeEdit->text().toInt(&ok);

    if (!toleranceEdit->text().isEmpty())
        tolerance = toleranceEdit->text().toInt(&ok);

    QDialog::accept();
}

void Preferences::reject() {
    QDialog::reject();
}
