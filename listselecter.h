#ifndef LISTSELECTER_H
#define LISTSELECTER_H

#include <QObject>
#include <QtWidgets>
#include <QDialog>
#include "container.h"
#include "searchvalidator.h"

class MyHLayout;

class ListSelecter : public QDialog {
    Q_OBJECT
    QCheckBox *cb_simple, *cb_double, *cb_thermo, *cb_vibrator, *cb_deluxe;
    QComboBox *colorChoiceDropDown;
    MyHLayout *h_price, *h_len, *h_diam, *h_diam2, *h_watt, *h_freq, *h_temp;
public:
    ListSelecter(QWidget *parent);
    SearchValidator getValidator() const;
public slots:
    void enabledisablelayouts(int);
};

class MyHLayout : public QHBoxLayout {

    QCheckBox *checkbox;
    QSpinBox *min, *max;
public:
    MyHLayout(QString label, QWidget *parent = 0);
    void on() const;
    void off() const;
    bool isApplicableBound() const;
    int getMin() const;
    int getMax() const;
};
#endif // LISTSELECTER_H
