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
    Container_DAO<int> list(16);
    for(size_t i = 0; i < list.size(); i++)
        list[i] = i;

    Container<int> list2 = list;
    list2.delete_at(3);
    list2.delete_at(3);
    for(size_t i = 0; i < list2.size(); i++)
        cout << list2[i] << endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}
