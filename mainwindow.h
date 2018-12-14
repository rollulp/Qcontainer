#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "container_dao.h"
#include "dildo.h"
#include "listselector.h"

class MainWindow : public QDialog {

    Q_OBJECT

    QVBoxLayout *main;
    Container_DAO<Dildo> list;
    ListSelector* window2;

public:
    MainWindow(QWidget *parent = 0);

public slots:
    void get_and_apply_validator();

private slots:
    void save() const;
    void load();

private:
    void loadDefault();
};

#endif // MAINWINDOW_H
