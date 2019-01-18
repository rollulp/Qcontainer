#include "dildo.h"
#include "myexception.h"

const char Dildo::color_names[12][7] = {"white", "black", "grey", "red", "pink", "orange", "yellow", "purple", "green", "blue", "silver", "gold"};

Dildo::Dildo(int weight, int length, Color color, string img64, string title)
    : diam(weight), length(length), color(color), img64(img64), title(title)
{
    if (title.length() > 24)
        title = title.substr(0, 25);
    if (diam < 0 || length < 0 || color < 0 || color > GOLD)
        throw MyException("invalid dildo contruction");
}
Dildo::Dildo(const Dildo &dildo)
    : Dildo(dildo.diam, dildo.length, dildo.color, dildo.img64, dildo.title)
{}
Dildo::~Dildo() { }

Dildo::string Dildo::getTitle() const {
    return title;
}
int Dildo::getDiam() const {
    return diam;
}
int Dildo::getLength() const {
    return length;
}
const char* Dildo::getColorName() const {
    return Dildo::color_names[color];
}
Dildo::Color Dildo::getColor() const {
    return color;
}
Dildo::string Dildo::getImg() const {
    return img64;
}

void Dildo::setTitle(Dildo::string title) {
    this->title = title;
}
void Dildo::setDiam(int weight) {
    this->diam = weight;
}
void Dildo::setLength(int length) {
    this->length = length;
}
void Dildo::setColor(const Color& color) {
    this->color = color;
}
void Dildo::setImg(const string& img64) {
    this->img64 = img64;
}


/// Aggiungo la definzione dei metodo virtuali puri e do Class::category il suo valore
/// per le classi non astratte

#define VIRTUAL_CHECK(CLASS, NAME) \
    const char * const CLASS::category = #NAME; \
    const char* CLASS::getCategory() const { return category; } \
    Dildo* CLASS::clone() const { return new CLASS(*this); }

VIRTUAL_CHECK(SimpleDildo, Simple Dildo)
VIRTUAL_CHECK(DoubleDildo, Double Dildo)
VIRTUAL_CHECK(ThermoDildo, Thermo Dildo)
VIRTUAL_CHECK(InternalVibrator, Internal Vibrator)
VIRTUAL_CHECK(DildoDeluxe, Dildo Deluxe)

#undef VIRTUAL_CHECK



int SimpleDildo::getPrice() const {
    return 12 + getDiam()*getDiam()/4*getLength()/16;
}

DoubleDildo::DoubleDildo(int diam, int length, Dildo::Color color, string img64, string title, int diam_2)
    : Dildo(diam, length, color, img64, title), diam_2(diam_2)
{}
DoubleDildo::DoubleDildo(const DoubleDildo &dd)
    : DoubleDildo(dd.getDiam(), dd.getLength(), dd.getColor(), dd.getImg(), dd.getTitle(), dd.diam_2)
{}
int DoubleDildo::getPrice() const {
    return 12+((getDiam()+getDiam2())/4*(getDiam()+getDiam2())/4*getLength()/16);
}
int DoubleDildo::getDiam2() const {
    return diam_2;
}
void DoubleDildo::setDiam2(int diam_2) {
    this->diam_2 = diam_2;
}


ElectricDildo::ElectricDildo(int diam, int length, Dildo::Color color, string img64, string title, Watt watts)
    : Dildo(diam, length, color, img64, title), watts(watts)
{}
ElectricDildo::ElectricDildo(const ElectricDildo &ed)
    : ElectricDildo(ed.getDiam(), ed.getLength(), ed.getColor(), ed.getImg(), ed.getTitle(), ed.watts)
{}
ElectricDildo::Watt ElectricDildo::getWatts() const {
    return watts;
}
void ElectricDildo::setWatts(Watt watts) {
    this->watts = watts;
}


ThermoDildo::ThermoDildo(int diam, int length, Color color, string img64, string title, Watt watts, Temp temp)
    :  ElectricDildo(diam, length, color, img64, title, watts), temp(temp)
{}
ThermoDildo::ThermoDildo(const ThermoDildo &td) :
    ThermoDildo(td.getDiam(), td.getLength(), td.getColor(), td.getImg(), td.getTitle(), td.getWatts(), td.temp)
{}
int ThermoDildo::getPrice() const {
    return (15 + getDiam()*getDiam()/4*getLength()/3 + getWatts()/4);
}
ThermoDildo::Temp ThermoDildo::getTemp() const {
    return temp;
}
void ThermoDildo::setTemp(Temp temp) {
    this->temp = temp;
}


InternalVibrator::InternalVibrator(int diam, int length, Color color, string img64, string title, Watt watts, Hertz frequency)
    : ElectricDildo(diam, length, color, img64, title, watts), frequency(frequency)
{}
InternalVibrator::InternalVibrator(const InternalVibrator &iv)
    : InternalVibrator(iv.getDiam(), iv.getLength(), iv.getColor(), iv.getImg(), iv.getTitle(), iv.getWatts(), iv.frequency)
{}
int InternalVibrator::getPrice() const {
    return (18 + getDiam()*getDiam()/4*getLength()/2 + getWatts()/4);
}
InternalVibrator::Hertz InternalVibrator::getFrequency() const {
    return frequency;
}
void InternalVibrator::setFrequency(Hertz frequency) {
    this->frequency = frequency;
}

DildoDeluxe::DildoDeluxe(int diam, int length, Dildo::Color color, Dildo::string img64, string title, ElectricDildo::Watt watts, InternalVibrator::Hertz frequency, Temp temp)
    : ElectricDildo(diam, length, color, img64, title, watts),
      ThermoDildo(diam, length, color, img64, title, watts, temp),
      InternalVibrator(diam, length, color, img64, title, watts, frequency)
{}
DildoDeluxe::DildoDeluxe(const DildoDeluxe &ud)
    : ElectricDildo(ud.getDiam(), ud.getLength(), ud.getColor(), ud.getImg(), ud.getTitle(), ud.getWatts()),
      ThermoDildo(ud.getDiam(), ud.getLength(), ud.getColor(), ud.getImg(), ud.getTitle(), ud.getWatts(), ud.getTemp()),
      InternalVibrator(ud.getDiam(), ud.getLength(), ud.getColor(), ud.getImg(), ud.getTitle(), ud.getWatts(), ud.getFrequency())
{}
int DildoDeluxe::getPrice() const {
    return (21 + getDiam()*getDiam()/4*getLength()/2 + getWatts()/2);
}
