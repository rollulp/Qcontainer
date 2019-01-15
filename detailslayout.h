#ifndef DETAILSLAYOUT_H
#define DETAILSLAYOUT_H
#include <QtWidgets>
#include "dildo.h"
#include "defaults.h"
#include "container.h"

class DetailsLayout;

/*!
 * \class EditableLayout
 * Horizontal layout per visualizzare le
 * varie righe tutte con lo stesso format
 */
class EditableLayout : public QHBoxLayout {
    Q_OBJECT
    QLabel label;
    QSpinBox value;
public:
    /*!
     * \brief costruttore di una riga di dettaglio
     * \param field testo per la label di descrizione campo
     * \param initial_val valore dello spinner
     * \param min spinner_min
     * \param max spinner_max
     */
    EditableLayout(QString field, int initial_val, int min = defaults::spinner_min, int max = defaults::spinner_max);

    /// ritorna il valore dello spinner
    int getValue() const;
};

/*!
 * \class DetailsLayout
 * Tutta la parte destra dell' applicazione,
 * visualizza un Dildo in tutte le sue proprietà
 * e permette di modificarle e salvarle
 */
class DetailsLayout : public QVBoxLayout {

    Q_OBJECT
    QLabel image;
    Container<EditableLayout> lines;
    QPushButton saveBtn;
    Dildo *dildo;

public:
    DetailsLayout(QWidget *parent = 0);

    /// carica in visuale un dildo
    void showDildo(Dildo &dildo);

    /// scarica la visuale e visualizza niente
    void clear();

};

#endif // DETAILSLAYOUT_H
