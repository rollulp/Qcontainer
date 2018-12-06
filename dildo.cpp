#include "dildo.h"

const char Dildo::color_names[][10] = {"white", "black", "grey", "red", "pink", "orange", "yellow", "purple", "green", "blue", "silver", "gold"};

Dildo::Dildo(unsigned int price, unsigned int weight, unsigned int length, Color color)
    : price(price), diam(weight), length(length), color(color)
{}
Dildo::Dildo(const Dildo &dildo)
    : Dildo(dildo.price, dildo.diam, dildo.length, dildo.color)
{}
unsigned int Dildo::getPrice() const {
    return price;
}
unsigned int Dildo::getDiam() const {
    return diam;
}
unsigned int Dildo::getLength() const {
    return length;
}
const char* Dildo::getColorName() const {
    return Dildo::color_names[color];
}
Dildo::Color Dildo::getColor() const {
    return color;
}
void Dildo::setPrice(unsigned int price) {
    this->price = price;
}
void Dildo::setDiam(unsigned int weight) {
    this->diam = weight;
}
void Dildo::setLength(unsigned int length) {
    this->length = length;
}
void Dildo::setColor(const Color& color) {
    this->color = color;
}

#define VIRTUAL_CHECK(CLASS, NAME) \
    const char * const CLASS::category = #NAME; \
    const char* CLASS::getCategory() const { return category; } \
    Dildo* CLASS::clone() const { return new CLASS(*this); }

VIRTUAL_CHECK(DoubleDildo, Double Dildo)
VIRTUAL_CHECK(ThermoDildo, Thermo Dildo)

#undef VIRTUAL_CHECK

DoubleDildo::DoubleDildo(unsigned int price, unsigned int diam, unsigned int length, Dildo::Color color, unsigned int diam_2)
    : Dildo(price, diam, length, color), diam_2(diam_2)
{}
DoubleDildo::DoubleDildo(const DoubleDildo &dd)
    : DoubleDildo(dd.getPrice(), dd.getDiam(), dd.getLength(), dd.getColor(), dd.diam_2)
{}
unsigned int DoubleDildo::getDiam2() const {
    return diam_2;
}
void DoubleDildo::setDiam2(unsigned int diam_2) {
    this->diam_2 = diam_2;
}


ElectricDildo::ElectricDildo(unsigned int price, unsigned int diam, unsigned int length, Dildo::Color color, ElectricDildo::Watt watts)
    : Dildo(price, diam, length, color), watts(watts)
{}
ElectricDildo::ElectricDildo(const ElectricDildo &ed)
    : ElectricDildo(ed.getPrice(), ed.getDiam(), ed.getLength(), ed.getColor(), ed.watts)
{}
ElectricDildo::Watt ElectricDildo::getWatts() const {
    return watts;
}
void ElectricDildo::setWatts(Watt watts) {
    this->watts = watts;
}

ThermoDildo::ThermoDildo(unsigned int price, unsigned int diam, unsigned int length, Color color, Watt watts, Temp temp)
    : ElectricDildo(price, diam, length, color, watts), temp(temp)
{}
ThermoDildo::ThermoDildo(const ThermoDildo &td) :
    ThermoDildo(td.getPrice(), td.getDiam(), td.getLength(), td.getColor(), td.getWatts(), td.temp)
{}
ThermoDildo::Temp ThermoDildo::getTemp() const {
    return temp;
}
void ThermoDildo::setTemp(Temp temp) {
    this->temp = temp;
}
