#include "mainwindow.h"
#include "myexception.h"
#include "defaults.h"
#include <QtCore>
#include <QtWidgets>

#include <QDebug>
#include <iostream>
using namespace std;

#include "searchvalidator.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    window2(new ListSelector(this))
{
    setWindowTitle("Qildo - dildo storage");
    QVBoxLayout *main = new QVBoxLayout(this);
    resize(800, 800);

    loadDefault();



    QPushButton *open_window2 = new QPushButton("Change search params");
    connect(open_window2, &QPushButton::clicked, [this] (bool) { this->window2->show(); });
    main->addWidget(open_window2);

    ///////////////////////////////////////
#define cqDebug() cout
    for(size_t i = 0; i < list.size(); i++) {
        cqDebug() << list[i].getCategory()
             << "\tprice: " << list[i].getPrice()
             << "\tcolor: " << list[i].getColorName()
             << "\tleng: " << list[i].getLength()
             << "\tdiam: " << list[i].getDiam();
        if(auto ptr = dynamic_cast<SimpleDildo*>(&list[i]))
            (void)ptr; // no new fields
        else if(auto ptr = dynamic_cast<DoubleDildo*>(&list[i]))
            cqDebug() << "\tdiam2: " << ptr->getDiam2();
        else if(auto ptr = dynamic_cast<ElectricDildo*>(&list[i])) {
            cqDebug() << "\twatts: " << ptr->getWatts();
            if(auto ptr2 = dynamic_cast<ThermoDildo*>(ptr))
                cqDebug() << "\ttemp: " << ptr2->getTemp();
            if(auto ptr2 = dynamic_cast<InternalVibrator*>(ptr))
                cqDebug() << "\tfreq: " << ptr2->getFrequency();
        }
        cqDebug() << "\timg: " << (list[i].getImg().substr(0, 20)) << endl;
    }

}

void MainWindow::load() {
    try {
        list.loadFromJSON(DAO::loadFile());
    } catch (MyException e) {
        qDebug() << e.what() << '\n';
    }
}

void MainWindow::loadDefault() {
    try {
        list.loadFromJSON(DAO::string2json(json_data));
    } catch (MyException e) {
        qDebug() << e.what() << '\n';
    }
}

void MainWindow::save() const {
    try {
        DAO::writeFile( list.getJSON() );
    } catch (MyException e) {
        qDebug() << e.what() << '\n';
    }
}

void MainWindow::get_and_apply_validator() {

    // TODO apply to model new data

    Container<Dildo>::Stream stream = list.getStream(window2->getValidator());
    cqDebug() << "init search" << endl;
    try {
        int i = 0;
        while (const Dildo* d = stream.getNext()) {
            cqDebug() << ++i << (": ") << d->getCategory() << endl;;
        }
    } catch (MyException) {}
    cout << "end search" << endl;
    return;
}
