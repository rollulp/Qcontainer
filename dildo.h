#ifndef DILDO_H
#define DILDO_H
#include "dao.h"

/*abstract*/
class Dildo {
public:
    enum Color { WHITE, BLACK, GREY, RED, PINK, ORANGE, YELLOW, PURPLE, GREEN, BLUE, SILVER, GOLD };
private:
    static char const color_names[][10];
    unsigned int price;
    unsigned int diam;
    unsigned int length;
    Color color;
public:
/*constructors & polymorphic stuff*/
    Dildo(unsigned int price, unsigned int diam, unsigned int length, Color color);
    Dildo(const Dildo& dildo);
    // Base of Hierarchy virtual destructor
    virtual ~Dildo() {}
    // Dildo d = *(new Dildo); -> NO
    // Dildo* d = f.clone(); -> YES
    // breaks Rule Of Three! :)
    virtual Dildo& operator = (const Dildo&) = delete;

/*getters and setters*/
    unsigned int getPrice() const;
    unsigned int getDiam() const;
    unsigned int getLength() const;
    const char* getColorName() const;
    Color getColor() const;
    void setPrice(unsigned int price);
    void setDiam(unsigned int diam);
    void setColor(const Color& color);
    void setLength(unsigned int length);

    virtual const char* getCategory() const = 0;
    virtual Dildo* clone() const = 0;
};

/*non abstract*/
class DoubleDildo : public Dildo {
private:
    unsigned int diam_2;
public:
/*constructors*/
    DoubleDildo(unsigned int price, unsigned int diam, unsigned int length, Color color, unsigned int diam_2);
    DoubleDildo(const DoubleDildo& dd);

/*getters and setters*/
    unsigned int getDiam2() const;
    void setDiam2(unsigned int diam_2);

/*virtual stuff*/
    static const char * const category;
    const char* getCategory() const;
    Dildo* clone() const;
};

/*abstract*/
class ElectricDildo : public Dildo {
public:
    typedef unsigned int Watt;
private:
    Watt watts;
public:
/*constructors*/
    ElectricDildo(unsigned int price, unsigned int diam, unsigned int length, Color color, Watt watts);
    ElectricDildo(const ElectricDildo& ed);

/*getters and setters*/
    Watt getWatts() const;
    void setWatts(Watt watts);
};

/*non abstract*/
class ThermoDildo : public ElectricDildo {
public:
    typedef unsigned int Temp;
private:
    Temp temp;
public:
/*constructors*/
    ThermoDildo(unsigned int price, unsigned int diam, unsigned int length, Color color, Watt watts, Temp temp);
    ThermoDildo(const ThermoDildo &td);

/*getters and setters*/
    Temp getTemp() const;
    void setTemp(Temp temp);

/*virtual stuff*/
    static const char * const category;
    const char* getCategory() const;
    Dildo* clone() const;
};

/*non abstract*/
class InternalVibrator : public ElectricDildo {

public:
    static const char * const category;
    const char* getCategory() const {
        return category;
    }
    Dildo* clone() const{
        return new InternalVibrator(*this);
    }
};


#endif // DILDO_H
