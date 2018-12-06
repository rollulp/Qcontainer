#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "container_dao.h"

#include<iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DAO::setPath("/home/studente/Desktop/a");
    Container<Dildo> list;
    list.push_back(new DoubleDildo(1,1,1, Dildo::Color::RED, 2));
    list.push_back(list[0].clone());
    list.push_back(new ThermoDildo(13,2,2, Dildo::Color::RED,2,4));
    for(size_t i = 0; i < list.size(); i++)
        cout << list[i].getCategory() << "\tprice: " << list[i].getPrice() << endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}
