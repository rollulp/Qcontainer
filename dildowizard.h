#ifndef DILDOWIZARD_H
#define DILDOWIZARD_H

#include <QDialog>
#include <QtWidgets>
#include "dildo.h"

/*!
 * \class DildoWizard
 * Qdialog per aggiungere un nuovo dildo alla lista.
 * chiede percorso immagine, tipo di dildo, colore e titolo
 * ed aggiunge a static_cast<MainWindow*>(parent()).list
 * un nuovo elemento
 */
class DildoWizard : public QDialog {
    Q_OBJECT
    QVBoxLayout *body;
    QComboBox *colorCB;
    QComboBox *typeCB;
    QLineEdit *titleLineEdit;
    QString path;
public:
    DildoWizard(QWidget *parent = 0);
};

#endif // DILDOWIZARD_H
