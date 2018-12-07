#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "container_dao.h"
#include "myexception.h"
#include "defaults.h"

#include<iostream>
using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DAO::setPath("/home/studente/Desktop/a");
    Container_DAO<Dildo> list;
    try {
        //list.loadFromJSON(DAO::loadFile());
        list.loadFromJSON(DAO::string2json(json_data));
    } catch (MyException e) {
        cerr << e.what() << endl;
    }
    /*
    list.push_back(new SimpleDildo(3,4,5, Dildo::Color::RED, "a"));
    list.push_back(new DoubleDildo(3,4,5, Dildo::Color::RED, "b", 6));
    list.push_back(new ThermoDildo(13,14,15, Dildo::Color::RED, "c",16,17));
    list.push_back(new InternalVibrator(23,24,25, Dildo::Color::RED, "d",26,27));
    list.push_back(new UltraDildo(33,34,35, Dildo::Color::RED, "e",36,37,38));
    */
    cout << list.size() << endl;
    for(size_t i = 0; i < list.size(); i++) {
        cout << list[i].getCategory()
             << "\tprice: " << list[i].getPrice()
             << "\tcolor: " << list[i].getColorName()
             << "\tleng: " << list[i].getLength()
             << "\tdiam: " << list[i].getDiam()
             << "\timg: " << list[i].getImg();
        if(auto ptr = dynamic_cast<SimpleDildo*>(&list[i]))
            ptr->getCategory(); // no new fields
        else if(auto ptr = dynamic_cast<DoubleDildo*>(&list[i]))
            cout << "\tdiam2: " << ptr->getDiam2();
        else if(auto ptr = dynamic_cast<ElectricDildo*>(&list[i])) {
            cout << "\twatts: " << ptr->getWatts();
            if(auto ptr2 = dynamic_cast<ThermoDildo*>(ptr))
                cout << "\ttemp: " << ptr2->getTemp();
            if(auto ptr2 = dynamic_cast<InternalVibrator*>(ptr))
                cout << "\tfreq: " << ptr2->getFrequency();
        }
        cout << endl;
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
