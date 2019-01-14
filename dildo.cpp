#include "dildo.h"
#include "myexception.h"

const char Dildo::color_names[12][7] = {"white", "black", "grey", "red", "pink", "orange", "yellow", "purple", "green", "blue", "silver", "gold"};

Dildo::Dildo(int price, int weight, int length, Color color, string img64, string title)
    : price(price), diam(weight), length(length), color(color), img64(img64), title(title)
{
    if (title.length() > 24)
        title = title.substr(0, 25);
    if (price < 0 || diam < 0 || length < 0 || color < 0 || color > GOLD)
        throw MyException("invalid dildo contruction");
}
Dildo::Dildo(const Dildo &dildo)
    : Dildo(dildo.price, dildo.diam, dildo.length, dildo.color, dildo.img64, dildo.title)
{}
Dildo::~Dildo() { }

Dildo::string Dildo::getTitle() const {
    return title;
}
int Dildo::getPrice() const {
    return price;
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
void Dildo::setPrice(int price) {
    this->price = price;
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

DoubleDildo::DoubleDildo(int price, int diam, int length, Dildo::Color color, string img64, string title, int diam_2)
    : Dildo(price, diam, length, color, img64, title), diam_2(diam_2)
{}
DoubleDildo::DoubleDildo(const DoubleDildo &dd)
    : DoubleDildo(dd.getPrice(), dd.getDiam(), dd.getLength(), dd.getColor(), dd.getImg(), dd.getTitle(), dd.diam_2)
{}
int DoubleDildo::getDiam2() const {
    return diam_2;
}
void DoubleDildo::setDiam2(int diam_2) {
    this->diam_2 = diam_2;
}


ElectricDildo::ElectricDildo(int price, int diam, int length, Dildo::Color color, string img64, string title, Watt watts)
    : Dildo(price, diam, length, color, img64, title), watts(watts)
{}
ElectricDildo::ElectricDildo(const ElectricDildo &ed)
    : ElectricDildo(ed.getPrice(), ed.getDiam(), ed.getLength(), ed.getColor(), ed.getImg(), ed.getTitle(), ed.watts)
{}
ElectricDildo::Watt ElectricDildo::getWatts() const {
    return watts;
}
void ElectricDildo::setWatts(Watt watts) {
    this->watts = watts;
}


ThermoDildo::ThermoDildo(int price, int diam, int length, Color color, string img64, string title, Watt watts, Temp temp)
    :  ElectricDildo(price, diam, length, color, img64, title, watts), temp(temp)
{}
ThermoDildo::ThermoDildo(const ThermoDildo &td) :
    ThermoDildo(td.getPrice(), td.getDiam(), td.getLength(), td.getColor(), td.getImg(), td.getTitle(), td.getWatts(), td.temp)
{}
ThermoDildo::Temp ThermoDildo::getTemp() const {
    return temp;
}
void ThermoDildo::setTemp(Temp temp) {
    this->temp = temp;
}


InternalVibrator::InternalVibrator(int price, int diam, int length, Color color, string img64, string title, Watt watts, Hertz frequency)
    : ElectricDildo(price, diam, length, color, img64, title, watts), frequency(frequency)
{}
InternalVibrator::InternalVibrator(const InternalVibrator &iv)
    : InternalVibrator(iv.getPrice(), iv.getDiam(), iv.getLength(), iv.getColor(), iv.getImg(), iv.getTitle(), iv.getWatts(), iv.frequency)
{}
InternalVibrator::Hertz InternalVibrator::getFrequency() const {
    return frequency;
}
void InternalVibrator::setFrequency(Hertz frequency) {
    this->frequency = frequency;
}

DildoDeluxe::DildoDeluxe(int price, int diam, int length, Dildo::Color color, Dildo::string img64, string title, ElectricDildo::Watt watts, InternalVibrator::Hertz frequency, Temp temp)
    : ElectricDildo(price, diam, length, color, img64, title, watts),
      ThermoDildo(price, diam, length, color, img64, title, watts, temp),
      InternalVibrator(price, diam, length, color, img64, title, watts, frequency)
{}
DildoDeluxe::DildoDeluxe(const DildoDeluxe &ud)
    : ElectricDildo(ud.getPrice(), ud.getDiam(), ud.getLength(), ud.getColor(), ud.getImg(), ud.getTitle(), ud.getWatts()),
      ThermoDildo(ud.getPrice(), ud.getDiam(), ud.getLength(), ud.getColor(), ud.getImg(), ud.getTitle(), ud.getWatts(), ud.getTemp()),
      InternalVibrator(ud.getPrice(), ud.getDiam(), ud.getLength(), ud.getColor(), ud.getImg(), ud.getTitle(), ud.getWatts(), ud.getFrequency())
{}
