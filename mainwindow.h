#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "container_dildo.h"
#include "dildo.h"
#include "listselector.h"
#include "mydildolistwidget.h"
#include "detailslayout.h"

class MainWindow : public QDialog {

    Q_OBJECT

    MyDildoListWidget *dildoListWidget;
    DetailsLayout *detailsLayout;
    ListSelector* window2;
    Container_Dildo *list;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *e);
    void addDildo(Dildo *dildo);

private slots:
    void save();
    void load();
    void update();

private:
    void loadDefault();
};

#endif // MAINWINDOW_H
