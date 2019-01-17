#include "mydildolistwidget.h"
#include "container.h"

MyDildoListWidgetItem::MyDildoListWidgetItem(const Container<Dildo>::iterator &it)
    : QListWidgetItem(), iterator(it)
{}

Container<Dildo>::iterator MyDildoListWidgetItem::getDildo() const {
    return iterator;
}

MyDildoListWidget::MyDildoListWidget(Container<Dildo> *list, QWidget *parent)
    : QListWidget(parent),
      list(list)
{
    setSelectionMode(QAbstractItemView::ExtendedSelection);
}

namespace {
QLabel* getImg(const Container<Dildo>::iterator &it) {
    QImage img;
    img.loadFromData( QByteArray::fromBase64( it->getImg().c_str() ) );
    QLabel *imgLabel = new QLabel;
    imgLabel->setPixmap( QPixmap::fromImage(img).scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation) );
    imgLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    return imgLabel;
}
}
void MyDildoListWidget::addEntry(const Container<Dildo>::iterator &it, bool hidden) {
    QWidget *w = new QWidget;
    QHBoxLayout *hl = new QHBoxLayout;

    //color
    QPixmap pm(10,10);
    pm.fill();
    QPainter p(&pm);
    p.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::black, 0);
    p.setPen(pen);
    QColor color;
    switch (it->getColor()) {
    case Dildo::WHITE:  color.setRgb(255, 255, 255);   break;
    case Dildo::BLACK:  color.setRgb(000, 000, 000);   break;
    case Dildo::GREY:   color.setRgb(127, 127, 127);   break;
    case Dildo::RED:    color.setRgb(230, 000, 000);   break;
    case Dildo::PINK:   color.setRgb(255, 000, 255);   break;
    case Dildo::ORANGE: color.setRgb(255, 127, 000);   break;
    case Dildo::YELLOW: color.setRgb(255, 255, 000);   break;
    case Dildo::PURPLE: color.setRgb(127, 000, 127);   break;
    case Dildo::BLUE:   color.setRgb(000, 000, 180);   break;
    case Dildo::SILVER: color.setRgb(180, 180, 180);   break;
    case Dildo::GOLD:   color.setRgb(184, 134, 011);   break;
    default:
        throw MyException("MyDildoListWidget::addEntry color error");
    }
    QBrush brush(color);
    p.setBrush(brush);
    p.drawEllipse(0, 0, 10, 10);
    QLabel *l = new QLabel;
    l->setPixmap(pm);
    l->setMaximumSize(20, 20);
    hl->addWidget(l);

    // img
    hl->addWidget(getImg(it));

    //title
    hl->addWidget(new QLabel( QString::fromStdString("  " + it->getTitle()) ));

    w->setLayout(hl);

    QListWidgetItem *item = new MyDildoListWidgetItem(it);
    addItem(item);
    item->setSizeHint(w->sizeHint());
    item->setHidden(hidden);
    setItemWidget(item, w);

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
        for (auto item : selected_items) {
            list->remove( static_cast<MyDildoListWidgetItem*>(item)->getDildo() );
            delete item;
        }
}

