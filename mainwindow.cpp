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

    DAO::setPath("/home/studente/Desktop/a.dat");
    size_t t = 30;
    Container<int> list(t);
    for(size_t i = 0; i < t; i++) {
        list[i] = i;
    }
    for(size_t i = 0; i < list.size(); i++)
        cout << i << ": " << list[i] << endl;

}

MainWindow::~MainWindow()
{
    delete ui;
}
