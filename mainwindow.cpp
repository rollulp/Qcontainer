#include "mainwindow.h"
#include "myexception.h"
#include "defaults.h"
#include "dildowizard.h"
#include <QtCore>
#include <QtWidgets>

#include <QDebug>

#include "searchvalidator.h"

MainWindow::~MainWindow() {
    delete dildoListWidget;
    list->first = list->last = nullptr;
    delete list;
}

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    detailsLayout(new DetailsLayout),
    window2(new ListSelector(this)),
    list(new Container_Dildo)
{
    setWindowTitle("Qildo - dildo storage");
    QHBoxLayout *body = new QHBoxLayout(this);
    resize(600, 500);

    ////////////////////////

    load();

    QVBoxLayout *left = new QVBoxLayout;
    QHBoxLayout *topBtns = new QHBoxLayout;
    QHBoxLayout *bottomBtns = new QHBoxLayout;
    dildoListWidget = new MyDildoListWidget(list);
    connect(dildoListWidget, &MyDildoListWidget::itemSelectionChanged, [this] () {
        auto items = dildoListWidget->selectedItems();
        if (items.length() != 1)
            detailsLayout->clear();
        else
            detailsLayout->showDildo(*static_cast<MyDildoListWidgetItem*>(items[0])->getDildo());
    });
    left->addLayout(topBtns);
    left->addWidget(dildoListWidget);
    left->addLayout(bottomBtns);
    body->addLayout(left, 33);


    for (auto it = list->begin(); it; ++it)
        dildoListWidget->addEntry(it);

    ///////////////////////


    QPushButton *savebtn = new QPushButton("Save");
    connect(savebtn, &QPushButton::clicked, this, &MainWindow::save);

    QPushButton *add_element = new QPushButton("Add");
    connect(add_element, &QPushButton::clicked, [this] (bool) { DildoWizard(this).exec(); });

    QPushButton *delete_selection = new QPushButton("Delete");
    connect(delete_selection, &QPushButton::clicked, dildoListWidget, &MyDildoListWidget::rmSelected);

    QPushButton *restore = new QPushButton("Restore");
    connect(restore, &QPushButton::clicked, [this](bool) {
        if (QMessageBox::question(this, "Restore defaults", "Replace current list and restore default 5 items?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes) {
            dildoListWidget->clear();
            loadDefault();
            update();
            for (auto it = list->begin(); it; ++it)
                dildoListWidget->addEntry(it);
        }
    });

    QPushButton *open_window2 = new QPushButton("Search..");
    connect(open_window2, &QPushButton::clicked, [&](bool){ window2->show(); });

    topBtns->addWidget(savebtn);
    topBtns->addWidget(restore);
    topBtns->addWidget(open_window2);
    bottomBtns->addWidget(add_element);
    bottomBtns->addWidget(delete_selection);
    open_window2->setFocus();

    body->addLayout(detailsLayout, 66);

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
        list->loadFromJSON(DAO::string2json(defaults::json_data));
    } catch (MyException e) {
        qDebug() << e.what() << '\n';
    }
}

void MainWindow::save() {
    if (QMessageBox::question(this, "Save", "Save current list?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes) {
        try {
            DAO::writeFile( list->getJSON() );
        } catch (MyException e) {
            qDebug() << e.what() << '\n';
        }
    }
}

void MainWindow::update() {
    dildoListWidget->syncView(window2->getValidator());
}

void MainWindow::addDildo(Dildo *dildo) {
    list->push_back(dildo);
    dildoListWidget->addEntry(list->end());
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
    switch( e->key() ) {
    case Qt::Key_Delete:
        dildoListWidget->rmSelected(0);
        break;
    case Qt::Key_Escape:
        return;
    default:
        QDialog::keyPressEvent(e);
    }
}
