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
    label = new QLabel("Thumbnail size:", this);
    thumbnailSize = new QLineEdit(this);
    thumbnailSize->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);
    thumbnailSize->setPlaceholderText("200");
    thumbnailSize->setValidator(new QIntValidator(1, 10000, this));
    label_2 = new QLabel("px", this);

    // layouts
    QHBoxLayout* inputLayout = new QHBoxLayout;
    inputLayout->addWidget(label);
    inputLayout->addWidget(thumbnailSize);
    inputLayout->addWidget(label_2);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
}

void Preferences::accept()
{
    QDialog::accept();
}

void Preferences::reject()
{
    QDialog::reject();
}
