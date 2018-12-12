#include "listselecter.h"
#include "dildo.h"

ListSelecter::ListSelecter(QWidget *parent)
    : QDialog(parent)
{
    this->setWindowTitle("Qildo selecter");
    QVBoxLayout * layout = new QVBoxLayout(this);

    grid = new QGridLayout;
    grid->setContentsMargins(15, 15, 15, 15);

    layout->addLayout(grid);

    //part1
    QLabel *label = new QLabel;
    label->setText("Choose types :");
    grid->addWidget(label, 0, 0, 1, 1);

    QCheckBox *cb1 = new QCheckBox;
    cb1->setText("Simple");
    grid->addWidget(cb1, 0, 3, 1, 1);

    QCheckBox *cb2 = new QCheckBox;
    cb2->setText("Double");
    grid->addWidget(cb2, 1, 2, 1, 1);

    QCheckBox *cb3 = new QCheckBox;
    cb3->setText("Thermo");
    grid->addWidget(cb3, 1, 3, 1, 1);

    QCheckBox *cb4 = new QCheckBox;
    cb4->setText("Vibrating");
    grid->addWidget(cb4, 2, 2, 1, 1);

    QCheckBox *cb5 = new QCheckBox;
    cb5->setText("Deluxe");
    grid->addWidget(cb5, 2, 3, 1, 1);

    //part2

    label = new QLabel;
    label->setText("By color :");
    grid->addWidget(label, 3, 0, 1, 1);

    QComboBox *colorChoiceDropDown = new QComboBox;
    colorChoiceDropDown->addItem("All");
    for(size_t i = 0; i < sizeof(Dildo::color_names)/sizeof(*Dildo::color_names); i++)
        colorChoiceDropDown->addItem(Dildo::color_names[i]);
    grid->addWidget(colorChoiceDropDown, 3, 2, 1, 2);

    //part3.1

    label = new QLabel;
    label->setText("By values :");
    grid->addWidget(label, 4, 0, 1, 1);

    label = new QLabel;
    label->setText("min");
    grid->addWidget(label, 4, 2, 1, 1);

    label = new QLabel;
    label->setText("max");
    grid->addWidget(label, 4, 3, 1, 1);

    //part3.2
    QRegExpValidator * validator = new QRegExpValidator(QRegExp("\\d*"), this);

    QSpinBox *lineEdit_2 = new QSpinBox;
    lineEdit_2->setValue(1);
    grid->addWidget(lineEdit_2, 5, 3, 1, 1);

    label = new QLabel;
    label->setText("meters");
    grid->addWidget(label, 5, 4, 1, 1);

    QLabel *label_13 = new QLabel;
    label_13->setText("label_13");
    grid->addWidget(label_13, 9, 4, 1, 1);

    QSpinBox *lineEdit = new QSpinBox;
    lineEdit->setValue(2);
    grid->addWidget(lineEdit, 5, 1, 1, 2);

    QCheckBox *checkBox_6 = new QCheckBox;
    checkBox_6->setText("checkBox_6");
    grid->addWidget(checkBox_6, 5, 0, 1, 1);

    QSpinBox *lineEdit_9 = new QSpinBox;
    lineEdit_9->setValue(3);
    grid->addWidget(lineEdit_9, 9, 3, 1, 1);

    QSpinBox *lineEdit_8 = new QSpinBox;
    lineEdit_8->setValue(4);
    grid->addWidget(lineEdit_8, 8, 3, 1, 1);

    QCheckBox *checkBox_9 = new QCheckBox;
    checkBox_9->setText("checkBox_9");
    grid->addWidget(checkBox_9, 8, 0, 1, 1);

    QSpinBox *lineEdit_5 = new QSpinBox;
    lineEdit_5->setValue(5);
    grid->addWidget(lineEdit_5, 7, 3, 1, 1);

    QCheckBox *checkBox_8 = new QCheckBox;
    checkBox_8->setText("checkBox_8");
    grid->addWidget(checkBox_8, 7, 0, 1, 1);

    QLabel *label_5 = new QLabel;
    label_5->setText("label_5");
    grid->addWidget(label_5, 6, 4, 1, 1);

    QSpinBox *lineEdit_6 = new QSpinBox;
    lineEdit_6->setValue(6);
    grid->addWidget(lineEdit_6, 8, 1, 1, 2);

    QSpinBox *lineEdit_15 = new QSpinBox;
    lineEdit_15->setValue(7);
    grid->addWidget(lineEdit_15, 9, 1, 1, 2);

    QLabel *label_10 = new QLabel;
    label_10->setText("label_10");
    grid->addWidget(label_10, 8, 4, 1, 1);

    QCheckBox *checkBox_10 = new QCheckBox;
    checkBox_10->setText("checkBox_10");
    grid->addWidget(checkBox_10, 9, 0, 1, 1);

    QCheckBox *checkBox_13 = new QCheckBox;
    checkBox_13->setText("checkBox_13");
    grid->addWidget(checkBox_13, 10, 0, 1, 1);

    QSpinBox *lineEdit_7 = new QSpinBox;
    lineEdit_7->setValue(12);
    grid->addWidget(lineEdit_7, 7, 1, 1, 2);

    QLabel *label_8 = new QLabel;
    label_8->setText("label_8");
    grid->addWidget(label_8, 10, 4, 1, 1);

    QLabel *label_9 = new QLabel;
    label_9->setText("label_9");
    grid->addWidget(label_9, 7, 4, 1, 1);

    QCheckBox *checkBox_7 = new QCheckBox;
    checkBox_7->setText("checkBox_7");
    grid->addWidget(checkBox_7, 6, 0, 1, 1);

    QSpinBox *lineEdit_4 = new QSpinBox;
    lineEdit_4->setValue(8);
    grid->addWidget(lineEdit_4, 6, 1, 1, 2);

    QSpinBox *lineEdit_3 = new QSpinBox;
    lineEdit_3->setValue(9);
    grid->addWidget(lineEdit_3, 6, 3, 1, 1);

    QSpinBox *lineEdit_10 = new QSpinBox;
    lineEdit_10->setValue(10);
    grid->addWidget(lineEdit_10, 10, 1, 1, 2);

    QSpinBox *lineEdit_16 = new QSpinBox;
    lineEdit_16->setValue(11);
    grid->addWidget(lineEdit_16, 10, 3, 1, 1);

    QDialogButtonBox *ok = new QDialogButtonBox;
    ok->setOrientation(Qt::Horizontal);
    ok->setStandardButtons(QDialogButtonBox::Apply);
    layout->addWidget(ok);
}
