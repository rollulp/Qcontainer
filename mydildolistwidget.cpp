#include "mydildolistwidget.h"
#include "container.h"

class MyDildoListWidgetItem : public QListWidgetItem {
    Container<Dildo>::iterator iterator;
public:
    MyDildoListWidgetItem(const Container<Dildo>::iterator &it) : QListWidgetItem(), iterator(it) {}
    ~MyDildoListWidgetItem() {
        iterator.delete_and_advance();
    }

    friend class MyDildoListWidget;
};

MyDildoListWidget::MyDildoListWidget(Container<Dildo> *list, QWidget *parent)
    : QListWidget(parent),
      list(list)
{
    setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void MyDildoListWidget::addDildo(const Container<Dildo>::iterator &it, bool hidden) {
    QWidget *w = new QWidget;
    QHBoxLayout *hl = new QHBoxLayout;
    hl->addWidget(new QCheckBox);
    QImage img;
    img.loadFromData( QByteArray::fromBase64( it->getImg().c_str() ) );
    QLabel *imgLabel = new QLabel;
    imgLabel->setScaledContents(true);
    imgLabel->setPixmap( QPixmap::fromImage(img).scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation) );
    hl->addWidget(imgLabel);
    hl->addWidget(new QPushButton("ciao"));

    w->setLayout(hl);

    QListWidgetItem *item = new MyDildoListWidgetItem(it);
    addItem(item);
    item->setSizeHint(w->sizeHint());
    item->setHidden(hidden);
    setItemWidget(item, w);

}

void MyDildoListWidget::clear() {
    list->first = list->last= nullptr;
    QListWidget::clear();
}

void MyDildoListWidget::syncView(Validator<Dildo> *validate) {
    for (int i = count()-1; i >=0 ; i--)
        item(i)->setHidden(!(*validate)(*static_cast<MyDildoListWidgetItem*>(item(i))->iterator));

    delete validate;
}

void MyDildoListWidget::rmSelected(bool) {
    auto selected_items = selectedItems();
    if (!selected_items.count()) return;
    if (QMessageBox::question(this, "Delete", "Delete selected items?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
        for (auto item : selected_items)
            delete item;
}

