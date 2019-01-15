#ifndef MYDILDOLISTWIDGET_H
#define MYDILDOLISTWIDGET_H

#include <QObject>
#include <QtWidgets>
#include "dildo.h"
#include "container.h"

/*!
 * \class MyDildoListWidgetItem
 * Consiste nel singolo elemento della lista MyDildoListWidget,
 * si costruisce con un iteratore al dildo che serve
 * per mostrarne immagine colore e titolo.
 */
class MyDildoListWidgetItem : public QListWidgetItem {
    Container<Dildo>::iterator iterator;
    /// costruttore privato! solo friend class MyDildoListWidget può instanziare
    MyDildoListWidgetItem(const Container<Dildo>::iterator &it);
public:
    /// per recuperare l' iteratore al dildo
    Container<Dildo>::iterator getDildo() const;
    friend class MyDildoListWidget;
};

/*!
 * \class MyDildoListWidget
 * La lista visualizzata a sinistra del MainWindow
 * composta da una serie di MyDildoListWidgetItem.
 * contiene un puntatore alla lista di partenza da cui si
 * costruisce, e può dinamicamente aggiungere e togliere
 * elementi. Aggiungere tramite addEntry (chiamato da DildoWizard) e dalla GUI si rimuove
 * col pulsante col tasto Delete o col bottone, che chiamano rmSelected.
 */
class MyDildoListWidget : public QListWidget {
	Container<Dildo> *list;
public:

    MyDildoListWidget(Container<Dildo> *list, QWidget *parent = 0);
    void addEntry(const Container<Dildo>::iterator &d, bool hidden = false);
    void syncView(Validator<Dildo> *validate);

public slots:
    void rmSelected(bool);
};

#endif // MYDILDOLISTWIDGET_H
