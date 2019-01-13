#ifndef MYDILDOLISTWIDGET_H
#define MYDILDOLISTWIDGET_H

#include <QObject>
#include <QtWidgets>
#include "dildo.h"
#include "container.h"

class MyDildoListWidgetItem : public QListWidgetItem {
    Container<Dildo>::iterator iterator;
    MyDildoListWidgetItem(const Container<Dildo>::iterator &it);
public:
    Container<Dildo>::iterator getDildo() const;
    friend class MyDildoListWidget;
};

class MyDildoListWidget : public QListWidget {
	Container<Dildo> *list;
public:
    void addEntry(const Container<Dildo>::iterator &d, bool hidden = false);
    MyDildoListWidget(Container<Dildo> *list, QWidget *parent = 0);
    void clear();
    void syncView(Validator<Dildo> *validate);

public slots:
    void rmSelected(bool);
};

#endif // MYDILDOLISTWIDGET_H
