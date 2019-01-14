#include <QtCore>
#include "dildowizard.h"
#include "myexception.h"
#include "mainwindow.h"

DildoWizard::DildoWizard(QWidget *parent)
    : QDialog(parent),
      body(new QVBoxLayout(this)),
      colorCB(new QComboBox),
      typeCB(new QComboBox),
      titleLineEdit(new QLineEdit)
{
    setWindowTitle("Add new dildo");

    QStringList types, colors;
    types << SimpleDildo::category
          << DoubleDildo::category
          << InternalVibrator::category
          << ThermoDildo::category
          << DildoDeluxe::category;
    colors << "White" << "Black" << "Grey" << "Red" << "Pink" << "Orange" << "Yellow"
           << "Purple" << "Green" << "Blue" << "Silver" << "Gold";
    typeCB->addItems(types);
    colorCB->addItems(colors);

    QPushButton *browse = new QPushButton("Browse");
    QLabel *path_preview = new QLabel("...");
    path_preview->setStyleSheet("QLabel { color : grey; }");
    connect(browse, &QPushButton::clicked, [this, path_preview] (bool) {
        QString path = QFileDialog::getOpenFileName(this, "Select Image", "/home", "Image (*.jpeg *.jpg *.png)");
        if ( path.endsWith("jpg") || path.endsWith("png") || path.endsWith("jpeg") ) {
            path_preview->setText(path.split("/").back());
            this->path = path;
        }
    });


    QDialogButtonBox * bb = new QDialogButtonBox;
    bb->setOrientation(Qt::Horizontal);
    bb->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    connect(bb, &QDialogButtonBox::rejected, this, &DildoWizard::close);
    connect(bb, &QDialogButtonBox::accepted, [this] () {
        Dildo *dildo = nullptr;
        QString result = typeCB->currentText();
        if (result == QLatin1String(SimpleDildo::category))
            dildo = new SimpleDildo(0,0,0,Dildo::WHITE,"","");
        else if (result == QLatin1String(DoubleDildo::category))
            dildo = new DoubleDildo(0,0,0,Dildo::WHITE,"","",0);
        else if (result == QLatin1String(InternalVibrator::category))
            dildo = new InternalVibrator(0,0,0,Dildo::WHITE,"","",0,0);
        else if (result == QLatin1String(ThermoDildo::category))
            dildo = new ThermoDildo(0,0,0,Dildo::WHITE,"","",0,0);
        else if (result == QLatin1String(DildoDeluxe::category))
            dildo = new DildoDeluxe(0,0,0,Dildo::WHITE,"","",0,0,0);
        else throw MyException("DildoWizard::DildoWizard err");

        //img
        QImage image(path);
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        image.save(&buffer, "PNG");
        dildo->setImg(QString(byteArray.toBase64()).toStdString());

        dildo->setTitle(titleLineEdit->text().toStdString());

        dildo->setColor(static_cast<Dildo::Color>(colorCB->currentIndex()));

        dynamic_cast<MainWindow*>(this->parent())->addDildo(dildo);
        this->close();
    });

    /// ADD TO LAYOUT

    QHBoxLayout *hl;

    hl = new QHBoxLayout;
    hl->addWidget(new QLabel("Dildo Type : "));
    hl->addWidget(typeCB);
    body->addLayout(hl);

    hl = new QHBoxLayout;
    hl->addWidget(new QLabel("Color : "));
    hl->addWidget(colorCB);
    body->addLayout(hl);

    hl = new QHBoxLayout;
    hl->addWidget(new QLabel("Title : "));
    hl->addWidget(titleLineEdit);
    body->addLayout(hl);

    hl = new QHBoxLayout;
    hl->addWidget(new QLabel("Select image file:"));
    hl->addWidget(browse);
    body->addLayout(hl);

    body->addWidget(path_preview);
    body->setAlignment(path_preview, Qt::AlignHCenter);

    body->addWidget(bb);

    resize(300, 100);
}
