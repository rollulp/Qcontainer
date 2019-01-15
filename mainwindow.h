#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "container_dildo.h"
#include "dildo.h"
#include "listselector.h"
#include "mydildolistwidget.h"
#include "detailslayout.h"

/*!
 * \class MainWindow
 * La classe MainWindow è il QDialog principale, che possiede la lista
 * di dildi e gli altri QDialog. A sinistra mostra una visualizzazione
 * della lista (MyDildoListWidget) con i vari elementi e a destra
 * una visualizzazione dei dettagli (DetailsLayout) dell' elemento selezionato
 */
class MainWindow : public QDialog {

    Q_OBJECT

    MyDildoListWidget *dildoListWidget;
    DetailsLayout *detailsLayout;
    ListSelector *window2;
    Container_Dildo *list;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /// per gesire Esc e Delete
    void keyPressEvent(QKeyEvent *e);

    /// aggiungere un dildo alla lista!
    /// viene chiamata da dildoWizard
    void addDildo(Dildo *dildo);

private slots:
    /// \brief save on JSON file
    void save();
    /// \brief load from JSON file
    void load();
    /// \brief sync list from validator conditions
    void update();

private:
    /// \brief load from defaults.h file
    void loadDefault();
};

#endif // MAINWINDOW_H
