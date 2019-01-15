#ifndef LISTSELECTER_H
#define LISTSELECTER_H

#include <QObject>
#include <QtWidgets>
#include <QDialog>
#include "container.h"
#include "searchvalidator.h"

class MyHLayout;

class ListSelector : public QDialog {
    Q_OBJECT
    QCheckBox *cb_simple, *cb_double, *cb_thermo, *cb_vibrator, *cb_deluxe;
    QComboBox *colorChoiceDropDown;
    MyHLayout *h_price, *h_len, *h_diam, *h_diam2, *h_watt, *h_freq, *h_temp;

public:
    ListSelector(QWidget *parent);
    /// \return Validator<>* che soddisfa i criteri impostati
    SearchValidator *getValidator() const;

public slots:
    /// updates disable
    void enabledisablelayouts(int);
};

/*!
 * \class MyHLayout
 * Un Layout orizzontale che comprende label descrittiva,
 * un checkbox di attivazione e due spinbox
 * per i valori di minimo e di massimo
 */
class MyHLayout : public QHBoxLayout {

    QCheckBox *checkbox;
    QSpinBox *min, *max;
public:
    MyHLayout(QString label, QWidget *parent = 0);

    /// \brief activate line
    void on() const;
    /// \brief deactivate line
    void off() const;
    /// \brief check if condition has to be applied to SearchValidator
    bool isApplicableBound() const;
    /// \brief getMinValue
    int getMin() const;
    /// \brief getMaxValue
    int getMax() const;
};
#endif // LISTSELECTER_H
