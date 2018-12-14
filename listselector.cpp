#include "listselector.h"
#include "dildo.h"

ListSelector::ListSelector(QWidget *parent)
    : QDialog(parent),
      cb_simple(new QCheckBox("Simple")),
      cb_double(new QCheckBox("Double")),
      cb_thermo(new QCheckBox("Thermo")),
      cb_vibrator(new QCheckBox("Vibrating")),
      cb_deluxe(new QCheckBox("Deluxe")),
      colorChoiceDropDown(new QComboBox),
      h_price(new MyHLayout("price")),
      h_len(new MyHLayout("len")),
      h_diam(new MyHLayout("diam")),
      h_diam2(new MyHLayout("diam2")),
      h_watt(new MyHLayout("watt")),
      h_freq(new MyHLayout("freq")),
      h_temp(new MyHLayout("temp"))
{
    this->setWindowTitle("Qildo selecter");
    QVBoxLayout * layout = new QVBoxLayout(this);

    //grid

    QGridLayout *grid = new QGridLayout;
    grid->setContentsMargins(15, 15, 15, 15);
    layout->addLayout(grid);

    //part1

    cb_simple->setChecked(true);
    cb_double->setChecked(true);
    cb_thermo->setChecked(true);
    cb_vibrator->setChecked(true);
    cb_deluxe->setChecked(true);
    grid->addWidget(new QLabel("Choose types :"), 0, 0, 1, 1);
    grid->addWidget(cb_simple, 0, 3, 1, 1);
    grid->addWidget(cb_double, 1, 2, 1, 1);
    grid->addWidget(cb_thermo, 1, 3, 1, 1);
    grid->addWidget(cb_vibrator, 2, 2, 1, 1);
    grid->addWidget(cb_deluxe, 2, 3, 1, 1);

    connect(cb_simple, SIGNAL(stateChanged(int)), this, SLOT(enabledisablelayouts(int)));
    connect(cb_double, SIGNAL(stateChanged(int)), this, SLOT(enabledisablelayouts(int)));
    connect(cb_thermo, SIGNAL(stateChanged(int)), this, SLOT(enabledisablelayouts(int)));
    connect(cb_vibrator, SIGNAL(stateChanged(int)), this, SLOT(enabledisablelayouts(int)));
    connect(cb_deluxe, SIGNAL(stateChanged(int)), this, SLOT(enabledisablelayouts(int)));

    //part2

    grid->addWidget(new QLabel("By color :"), 3, 0, 1, 1);
    colorChoiceDropDown->addItem("All");
    for(size_t i = 0; i < sizeof(Dildo::color_names)/sizeof(*Dildo::color_names); i++)
        colorChoiceDropDown->addItem(Dildo::color_names[i]);
    grid->addWidget(colorChoiceDropDown, 3, 2, 1, 2);

    //part3

    layout->addLayout(h_price);
    layout->addLayout(h_len);
    layout->addLayout(h_diam);
    layout->addLayout(h_diam2);
    layout->addLayout(h_watt);
    layout->addLayout(h_freq);
    layout->addLayout(h_temp);
    enabledisablelayouts(0);

    //part4

    QDialogButtonBox *ok = new QDialogButtonBox;
    ok->setOrientation(Qt::Horizontal);
    ok->setStandardButtons(QDialogButtonBox::Ok);
    layout->addWidget(ok);
    connect(ok, SIGNAL(accepted()), parent, SLOT(get_and_apply_validator()));
}

void ListSelector::enabledisablelayouts(int) {
    //TODO funziona ma devo riscriverla meglio è inguardabile
    h_len->on();
    h_price->on();
    h_diam->on();
    h_diam2->off();
    h_watt->off();
    h_freq->off();
    h_temp->off();
    if (cb_simple->isChecked() || cb_double->isChecked()) {
        if ( ! (cb_simple->isChecked() || cb_thermo->isChecked() || cb_vibrator->isChecked() || cb_deluxe->isChecked()) )
            h_diam2->on();
        return;
    }
    if (cb_thermo->isChecked() || cb_vibrator->isChecked() || cb_deluxe->isChecked())
        h_watt->on();
    if (cb_thermo->isChecked() and ! cb_vibrator->isChecked()) {
        h_temp->on();
        return;
    }
    if (cb_vibrator->isChecked() and ! cb_thermo->isChecked()) {
        h_freq->on();
        return;
    }
    if ( !cb_vibrator->isChecked() and !cb_thermo->isChecked() and cb_deluxe->isChecked() ) {
        h_freq->on();
        h_temp->on();
        return;
    }
    if (cb_vibrator->isChecked() and cb_thermo->isChecked())
        return;
    //no Dildos
    h_len->off();
    h_price->off();
    h_diam->off();
}

SearchValidator ListSelector::getValidator() const {

    using Category = SearchValidator::Category;

    SearchValidator::AttributeBoundaries bounds;
    bounds.categoryBitMap = 0;
    if ( cb_simple->isChecked() )
        bounds.categoryBitMap |= Category::SimpleDildo;
    if ( cb_double->isChecked() )
        bounds.categoryBitMap |= Category::DoubleDildo;
    if ( cb_thermo->isChecked() )
        bounds.categoryBitMap |= Category::ThermoDildo;
    if ( cb_vibrator->isChecked() )
        bounds.categoryBitMap |= Category::InternalVibrator;
    if ( cb_deluxe->isChecked() )
        bounds.categoryBitMap |= Category::DildoDeluxe;

    //color
    if (int i = colorChoiceDropDown->currentIndex() )
        bounds.colorCheck = (bounds.color = static_cast<Dildo::Color>( i ));

    //attributes
    if ((bounds.len = h_len->isApplicableBound())) {
        bounds.lenmin = h_len->getMin();
        bounds.lenmax = h_len->getMax();
    }
    if ((bounds.price = h_price->isApplicableBound())) {
        bounds.pricemin = h_price->getMin();
        bounds.pricemax = h_price->getMax();
    }
    if ((bounds.diam = h_diam->isApplicableBound())) {
        bounds.diammin = h_diam->getMin();
        bounds.diammax = h_diam->getMax();
    }
    if ((bounds.diam2 = h_diam2->isApplicableBound())) {
        bounds.diam2min = h_diam2->getMin();
        bounds.diam2max = h_diam2->getMax();
    }
    if ((bounds.watt = h_watt->isApplicableBound())) {
        bounds.wattmin = h_watt->getMin();
        bounds.wattmax = h_watt->getMax();
    }
    if ((bounds.freq = h_freq->isApplicableBound())) {
        bounds.freqmin = h_freq->getMin();
        bounds.freqmax = h_freq->getMax();
    }
    if ((bounds.temp = h_temp->isApplicableBound())) {
        bounds.tempmin = h_temp->getMin();
        bounds.tempmax = h_temp->getMax();
    }

    return SearchValidator(bounds);
}

MyHLayout::MyHLayout(QString label, QWidget *parent)
    : QHBoxLayout(parent),
      checkbox(new QCheckBox(label)),
      min(new QSpinBox),
      max(new QSpinBox)
{
    addWidget(checkbox);
    addWidget(min);
    addWidget(new QLabel(" < value < "));
    addWidget(max);
    auto minmaxlambda = [this]()->void{
                if (this->min->value() > this->max->value())
                this->max->setValue(this->min->value());
            };
    connect(min, &QSpinBox::editingFinished, minmaxlambda);
    connect(max, &QSpinBox::editingFinished, minmaxlambda);
}

void MyHLayout::on() const {
    checkbox->setEnabled(true);
    min->setEnabled(true);
    max->setEnabled(true);
}

void MyHLayout::off() const {
    checkbox->setEnabled(false);
    min->setEnabled(false);
    max->setEnabled(false);
}

bool MyHLayout::isApplicableBound() const {
    return checkbox->isEnabled() && checkbox->isChecked();
}
int MyHLayout::getMin() const {
    return min->value();
}
int MyHLayout::getMax() const {
    return max->value();
}
