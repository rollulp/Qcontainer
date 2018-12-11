#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "container_dao.h"
#include "dildo.h"

class MainWindow : public QDialog {

    Q_OBJECT

    Container_DAO<Dildo> list;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void save() const;
    void load();

private:
    void loadDefault();
};

#endif // MAINWINDOW_H
