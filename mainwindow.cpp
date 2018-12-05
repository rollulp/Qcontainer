#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "container_dao.h"
#include<iostream>
using namespace std;
struct C{
    int i;
    int n;
    static int f;
    C(int i = 0) : i(i), n(f++) {
          cout <<"new C " << n  << ' ' << this << endl;
    }
    ~C() {
        cout << "del C " << n  << ' ' << this << endl;
    }
    C(const C&c) : C(c.i) {}
    operator int() {return i;}
    int& operator = (int i) {
        this->i = i;
        return this->i;
    }
};
int C::f = 0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    size_t t = 0;

    DAO::setPath("/home/studente/Desktop/a.dat");
    Container_DAO<C> list(t);
    for(size_t i = 0; i < t; i++)
        list[i] = i;
    for(size_t i = 0; i < list.size(); i++)
        cout << i << ": " << list[i] << endl;

}

MainWindow::~MainWindow()
{
    delete ui;
}
