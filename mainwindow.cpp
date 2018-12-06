#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "container_dao.h"
#include "myexception.h"

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
        list.loadFromJSON(DAO::loadFile());
    } catch (MyException e) {
        cerr << e.what().toStdString() << endl;
    }
    list.push_back(new DoubleDildo(1,1,1, Dildo::Color::RED, 2));
    list.push_back(list[0].clone());
    list.push_back(new ThermoDildo(13,2,2, Dildo::Color::RED,2,4));
    for(size_t i = 0; i < list.size(); i++)
        cout << list[i].getCategory() << "\tprice: " << list[i].getPrice() << endl;

    try {
        DAO::writeFile(list.getJSON());
    } catch (MyException e) {
        cerr << e.what().toStdString() << endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
