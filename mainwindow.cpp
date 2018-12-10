#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "container_dao.h"
#include "myexception.h"
#include "defaults.h"
#include <QDialog>

#include<iostream>
using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Qildo - dildo storage");

    Container_DAO<Dildo> list;
    try {
        list.loadFromJSON(DAO::loadFile());
        //list.loadFromJSON(DAO::string2json(json_data));
    } catch (MyException e) {
        cerr << e.what() << endl;
    }
    for(size_t i = 0; i < list.size(); i++) {
        cout << list[i].getCategory()
             << "\tprice: " << list[i].getPrice()
             << "\tcolor: " << list[i].getColorName()
             << "\tleng: " << list[i].getLength()
             << "\tdiam: " << list[i].getDiam();
        if(auto ptr = dynamic_cast<SimpleDildo*>(&list[i]))
            (void)ptr; // no new fields
        else if(auto ptr = dynamic_cast<DoubleDildo*>(&list[i]))
            cout << "\tdiam2: " << ptr->getDiam2();
        else if(auto ptr = dynamic_cast<ElectricDildo*>(&list[i])) {
            cout << "\twatts: " << ptr->getWatts();
            if(auto ptr2 = dynamic_cast<ThermoDildo*>(ptr))
                cout << "\ttemp: " << ptr2->getTemp();
            if(auto ptr2 = dynamic_cast<InternalVibrator*>(ptr))
                cout << "\tfreq: " << ptr2->getFrequency();
        }
        cout << "\timg: " << list[i].getImg().substr(0, 20) << endl;
    }

    try {
        DAO::writeFile(list.getJSON());
    } catch (MyException e) {
        cerr << e.what() << endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
