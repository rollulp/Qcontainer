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
      dildo(nullptr)
{
    // immagine al centro
    addWidget(&image);
    setAlignment(&image, Qt::AlignHCenter);

    // salvataggio
    saveBtn.setText("Save");
    connect(&saveBtn, &QPushButton::clicked, [this] (bool) {
        // per ogni campo salvo il valore immesso col giusto setter
        // e avanzo con l'iteratore.
        /* una soluzione possibile sarebbe stata dare il puntaore al metodo giusto
         * da chiamare per salvare il valore ad ogni singolo EditableLayout,
         * ma non posso chiamare un metodo della classe derivata da un puntatore
         * alla classe base senza castarlo ad un puntatore della classe derivata
         * se l'eredità è virtuale, perchè bisogna correggere il puntatore in base
         * alla vtable della relatica classe, e solo dynamic_cast sa fare questo.
         */
        auto it = lines.begin();
        this->dildo->setPrice((*it).getValue()); ++it;
        this->dildo->setDiam((*it).getValue()); ++it;
        this->dildo->setLength((*it).getValue()); ++it;
        auto cat = this->dildo->getCategory();
        if (cat == SimpleDildo::category) {
            ;
        } else if (cat == DoubleDildo::category) {
            dynamic_cast<DoubleDildo*>(this->dildo)->setDiam2((*it).getValue()); ++it;
        } else if (cat == InternalVibrator::category) {
            dynamic_cast<ElectricDildo*>(this->dildo)->setWatts((*it).getValue()); ++it;
            dynamic_cast<InternalVibrator*>(this->dildo)->setFrequency((*it).getValue()); ++it;
        } else if (cat == ThermoDildo::category) {
            dynamic_cast<ElectricDildo*>(this->dildo)->setWatts((*it).getValue()); ++it;
            dynamic_cast<ThermoDildo*>(this->dildo)->setTemp((*it).getValue()); ++it;
        } else if (cat == DildoDeluxe::category) {
            dynamic_cast<ElectricDildo*>(this->dildo)->setWatts((*it).getValue()); ++it;
            dynamic_cast<ThermoDildo*>(this->dildo)->setTemp((*it).getValue()); ++it;
            dynamic_cast<InternalVibrator*>(this->dildo)->setFrequency((*it).getValue()); ++it;
        }
    });
}

void DetailsLayout::showDildo(Dildo &dildo) {
    clear();
    this->dildo = &dildo;
    image.setPixmap( getPixmap(dildo.getImg().c_str()) );
    image.show();

    EditableLayout *lay;

    /// Aggiungo tutti i nuovi campi tramite un define per semplificare la sintassi

#define addField(CLASS, NAME) do { \
    lay = new EditableLayout(QString(#NAME" : "), dynamic_cast<CLASS*>(this->dildo)->get ## NAME()); \
    lines.push_back(lay); \
    addLayout(lay); \
} while (0)

    addField(Dildo, Price);
    addField(Dildo, Diam);
    addField(Dildo, Length);
    if (dildo.getCategory() == SimpleDildo::category) {
        ;
    } else if (dildo.getCategory() == DoubleDildo::category) {
        addField(DoubleDildo, Diam2);
    } else if (dildo.getCategory() == InternalVibrator::category) {
        addField(ElectricDildo, Watts);
        addField(InternalVibrator, Frequency);
    } else if (dildo.getCategory() == ThermoDildo::category) {
        addField(ElectricDildo, Watts);
        addField(ThermoDildo, Temp);
    } else if (dildo.getCategory() == DildoDeluxe::category) {
        addField(ElectricDildo, Watts);
        addField(ThermoDildo, Temp);
        addField(InternalVibrator, Frequency);
    }

#undef addField

    addWidget(&saveBtn);
    saveBtn.show();
}

void DetailsLayout::clear() {
    image.hide();

    //ok, questa prossima riga è solo per divertirsi un po'
    // svuoto il container e lo ricostruisco al suo posto.
    // ho trovato la riga troppo bella e dovevo metterla.
    // chiamo il distruttore e uso il new per costruire nella locazione che voglio io
    lines.~Container(), (void) new (const_cast<Container<EditableLayout>*>(&lines)) Container<EditableLayout*>;

    removeWidget(&saveBtn);
    saveBtn.hide();
    dildo = nullptr;
}
