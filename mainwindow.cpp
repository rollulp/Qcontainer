#include "mainwindow.h"
#include "myexception.h"
#include "defaults.h"
#include <QtCore>
#include <QtWidgets>

#include <QDebug>
#include <iostream>
using namespace std;

#include "searchvalidator.h"

MainWindow::~MainWindow() {
    delete dildoListWidget;
    list->first = list->last = nullptr;
    delete list;
}

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    detailsView(new QListView(this)),
    window2(new ListSelector(this)),
    list(new Container_Dildo)
{
    setWindowTitle("Qildo - dildo storage");
    QVBoxLayout *body = new QVBoxLayout(this);
    resize(800, 800);

    ////////////////////////

    load();

    dildoListWidget = new MyDildoListWidget(list);
    body->addWidget(dildoListWidget);

    for (auto it = list->begin(); it; ++it)
        dildoListWidget->addDildo(it);

    ///////////////////////

    QHBoxLayout *bottom = new QHBoxLayout;
    body->addLayout(bottom);

    QPushButton *savebtn = new QPushButton("Save");
    connect(savebtn, &QPushButton::clicked, this, &MainWindow::save);

    QPushButton *add_element = new QPushButton("Add");
    connect(add_element, &QPushButton::clicked, [](bool) {
        qDebug() << "TODO"; // TODO
    });

    QPushButton *delete_selection = new QPushButton("Delete");
    connect(delete_selection, &QPushButton::clicked, dildoListWidget, &MyDildoListWidget::rmSelected);

    QPushButton *restore = new QPushButton("Restore");
    connect(restore, &QPushButton::clicked, [this](bool) {
        if (QMessageBox::question(this, "Restore defaults", "Replace current list and restore default 5 items?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes) {
            dildoListWidget->clear();
            loadDefault();
            update();
            for (auto it = list->begin(); it; ++it)
                dildoListWidget->addDildo(it);
        }
    });

    QPushButton *open_window2 = new QPushButton("Change search params");
    connect(open_window2, &QPushButton::clicked, [&](bool){ window2->show(); });

    bottom->addWidget(savebtn);
    bottom->addWidget(add_element);
    bottom->addWidget(delete_selection);
    bottom->addWidget(restore);
    bottom->addWidget(open_window2);
    open_window2->setFocus();

    ///////////////////////////////////////
    body->addWidget(detailsView);
}

void MainWindow::load() {
    try {
        list->loadFromJSON(DAO::loadFile());
    } catch (MyException e) {
        qDebug() << e.what() << '\n';
    }
}

void MainWindow::loadDefault() {
    try {
        list->loadFromJSON(DAO::string2json(json_data));
    } catch (MyException e) {
        qDebug() << e.what() << '\n';
    }
}

void MainWindow::save() const {
    try {
        DAO::writeFile( list->getJSON() );
    } catch (MyException e) {
        qDebug() << e.what() << '\n';
    }
}

void MainWindow::update() {
     dildoListWidget->syncView(window2->getValidator());
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
    if (e->key() != Qt::Key_Escape)

        QDialog::keyPressEvent(e);
}
