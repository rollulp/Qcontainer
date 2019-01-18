#include "detailslayout.h"
#include "myexception.h"

namespace {
QPixmap getPixmap(const char * img_arr) {
    QImage img;
    img.loadFromData( QByteArray::fromBase64( img_arr ) );
    return QPixmap::fromImage(img).scaled(230, 230, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}
} //namespace

EditableLayout::EditableLayout(QString field, int initial_val, int min, int max)
    : QHBoxLayout()
{
    label.setText(field);
    addWidget(&label);
    addWidget(&value);
    value.setMinimum(min);
    value.setMaximum(max);
    value.setValue(initial_val);
}

int EditableLayout::getValue() const {
    return value.value();
}


DetailsLayout::DetailsLayout(QWidget *parent)
    : QVBoxLayout(parent),
      price(new QLabel),
      dildo(nullptr),
      priceRow(new QWidget)
{
    // immagine al centro
    addWidget(&image);
    setAlignment(&image, Qt::AlignHCenter);

    // prezzo
    QHBoxLayout *priceLayout = new QHBoxLayout(priceRow);
    priceLayout->addWidget(new QLabel("Price: "));
    priceLayout->addStretch();
    priceLayout->addWidget(price);
    addWidget(priceRow);
    priceRow->setHidden(true);

    // salvataggio
    saveBtn.setText("Save");
    connect(&saveBtn, &QPushButton::clicked, [this] (bool) {
        price->setText(QString::number(this->dildo->getPrice()));
        // per ogni campo salvo il valore immesso col giusto setter
        // e avanzo con l'iteratore.
        /* una soluzione possibile sarebbe stata dare il puntatore al metodo giusto
         * da chiamare per salvare il valore ad ogni singolo EditableLayout,
         * ma non posso chiamare un metodo della classe derivata da un puntatore
         * alla classe base senza castarlo ad un puntatore della classe derivata
         * se l'eredità è virtuale, perchè bisogna correggere il puntatore in base
         * alla vtable della relativa classe, e solo dynamic_cast sa fare questo.
         */
        auto it = lines.begin();
        this->dildo->setDiam((*it).getValue()); ++it;
        this->dildo->setLength((*it).getValue()); ++it;
        auto cat = this->dildo->getCategory();
        if (cat == SimpleDildo::category) {
            ;
        } else if (cat == DoubleDildo::category) {
            static_cast<DoubleDildo*>(this->dildo)->setDiam2((*it).getValue()); ++it;
        } else if (cat == InternalVibrator::category) {
            auto dildo = dynamic_cast<InternalVibrator*>(this->dildo); ///< non posso usare static_cast<>()
            dildo->setWatts((*it).getValue()); ++it;
            dildo->setFrequency((*it).getValue()); ++it;
        } else if (cat == ThermoDildo::category) {
            auto dildo = dynamic_cast<ThermoDildo*>(this->dildo); ///< non posso usare static_cast<>()
            dildo->setWatts((*it).getValue()); ++it;
            dildo->setTemp((*it).getValue()); ++it;
        } else if (cat == DildoDeluxe::category) {
            auto dildo = dynamic_cast<DildoDeluxe*>(this->dildo); ///< non posso usare static_cast<>()
            dildo->setWatts((*it).getValue()); ++it;
            dildo->setTemp((*it).getValue()); ++it;
            dildo->setFrequency((*it).getValue()); ++it;
        }
    });
}

void DetailsLayout::showDildo(Dildo &dildo) {
    clear();
    this->dildo = &dildo;
    image.setPixmap( getPixmap(dildo.getImg().c_str()) );
    image.show();

    priceRow->setHidden(false);
    price->setText(QString::number(this->dildo->getPrice()));

    EditableLayout *lay;

    /// Aggiungo tutti i nuovi campi tramite un define per semplificare la sintassi
    /// uso dynamic_cast forse un po' troppo ma non importa se ci mette quale µs in più
#define addField(PTR, NAME) do { \
    lay = new EditableLayout(QString(#NAME" : "), PTR->get ## NAME()); \
    lines.push_back(lay); \
    addLayout(lay); \
} while (0)

    addField(this->dildo, Diam);
    addField(this->dildo, Length);
    if (dildo.getCategory() == SimpleDildo::category) {
        ;
    } else if (dildo.getCategory() == DoubleDildo::category) {
        addField(static_cast<DoubleDildo*>(this->dildo), Diam2);
    } else if (dildo.getCategory() == InternalVibrator::category) {
        addField(static_cast<ElectricDildo*>(this->dildo), Watts);
        addField(dynamic_cast<InternalVibrator*>(this->dildo), Frequency);
    } else if (dildo.getCategory() == ThermoDildo::category) {
        addField(static_cast<ElectricDildo*>(this->dildo), Watts);
        addField(dynamic_cast<ThermoDildo*>(this->dildo), Temp);
    } else if (dildo.getCategory() == DildoDeluxe::category) {
        auto ptr = dynamic_cast<DildoDeluxe*>(this->dildo);
        addField(ptr, Watts);
        addField(ptr, Temp);
        addField(ptr, Frequency);
    }

#undef addField

    addWidget(&saveBtn);
    saveBtn.show();
}

void DetailsLayout::clear() {
    image.setHidden(true);
    priceRow->hide();

    //ok, questa prossima riga è solo per divertirsi un po'
    // svuoto il container e lo ricostruisco al suo posto.
    // ho trovato la riga troppo bella e dovevo metterla.
    // chiamo il distruttore e uso il placement new per costruire nella locazione che voglio io
    lines.~Container(), (void) new (const_cast<Container<EditableLayout>*>(&lines)) Container<EditableLayout*>;

    saveBtn.hide();
    dildo = nullptr;
}
