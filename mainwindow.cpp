#include "mainwindow.h"
#include "myexception.h"
#include "defaults.h"
#include <QtCore>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Qildo - dildo storage");

    window2 = new ListSelector(this);
    window2->show();

    loadDefault();

    for(size_t i = 0; i < list.size(); i++) {
        qDebug() << list[i].getCategory()
             << "\tprice: " << list[i].getPrice()
             << "\tcolor: " << list[i].getColorName()
             << "\tleng: " << list[i].getLength()
             << "\tdiam: " << list[i].getDiam();
        if(auto ptr = dynamic_cast<SimpleDildo*>(&list[i]))
            (void)ptr; // no new fields
        else if(auto ptr = dynamic_cast<DoubleDildo*>(&list[i]))
            qDebug() << "\tdiam2: " << ptr->getDiam2();
        else if(auto ptr = dynamic_cast<ElectricDildo*>(&list[i])) {
            qDebug() << "\twatts: " << ptr->getWatts();
            if(auto ptr2 = dynamic_cast<ThermoDildo*>(ptr))
                qDebug() << "\ttemp: " << ptr2->getTemp();
            if(auto ptr2 = dynamic_cast<InternalVibrator*>(ptr))
                qDebug() << "\tfreq: " << ptr2->getFrequency();
        }
        qDebug() << "\timg: " << QString::fromStdString(list[i].getImg().substr(0, 20)) << '\n';
    }

    QHBoxLayout * main = new QHBoxLayout(this);
    QVBoxLayout *right = new QVBoxLayout; //  search and select
    QVBoxLayout *left = new QVBoxLayout;
    main->addLayout(left);
    main->addLayout(right);

    resize(800, 800);
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

MainWindow::~MainWindow() {

}
