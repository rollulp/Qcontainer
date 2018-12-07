#ifndef DILDO_H
#define DILDO_H

// std::string rather than QString
#include <string>
using mystring = std::string;

/*abstract*/
class Dildo {
public:
    using string = mystring;
    enum Color { WHITE, BLACK, GREY, RED, PINK, ORANGE, YELLOW, PURPLE, GREEN, BLUE, SILVER, GOLD };
private:
    static char const color_names[][10];
    int price;
    int diam;
    int length;
    Color color;
    string img64;
public:
/*constructors & polymorphic stuff*/
    Dildo(int price, int diam, int length, Color color, string img64);
    Dildo(const Dildo& dildo);
    // Base of Hierarchy virtual destructor
    virtual ~Dildo() {}

    // Dildo d = *(new Dildo); -> NO
    // Dildo* d = f.clone(); -> YES
    // breaks Rule Of Three! :)
    virtual Dildo& operator = (const Dildo&) = delete;

/*getters and setters*/
    int getPrice() const;
    int getDiam() const;
    int getLength() const;
    const char* getColorName() const;
    Color getColor() const;
    string getImg() const;
    void setPrice(int price);
    void setDiam(int diam);
    void setColor(const Color& color);
    void setLength(int length);
    void setImg(const string& img64);

    virtual const char* getCategory() const = 0;
    virtual Dildo* clone() const = 0;
};

/*non abstract*/
class SimpleDildo : public Dildo {
public:
/*constructors*/
    using Dildo::Dildo;

/*virtual stuff*/
        static const char * const category;
        const char* getCategory() const;
        Dildo* clone() const;
};
/*non abstract*/
class DoubleDildo : public Dildo {
private:
    int diam_2;
public:
/*constructors*/
    DoubleDildo(int price, int diam, int length, Color color, string img64, int diam_2);
    DoubleDildo(const DoubleDildo& dd);

/*getters and setters*/
    int getDiam2() const;
    void setDiam2(int diam_2);

/*virtual stuff*/
    static const char * const category;
    const char* getCategory() const;
    Dildo* clone() const;
};

/*abstract*/
class ElectricDildo : virtual public Dildo {
public:
    using Watt = int;
private:
    Watt watts;
public:
/*constructors*/
    ElectricDildo(int price, int diam, int length, Color color, string img64, Watt watts);
    ElectricDildo(const ElectricDildo& ed);

/*getters and setters*/
    Watt getWatts() const;
    void setWatts(Watt watts);
};

/*non abstract*/
class ThermoDildo : virtual public ElectricDildo {
public:
    using Temp = int;
private:
    Temp temp;
public:
/*constructors*/
    ThermoDildo(int price, int diam, int length, Color color, string img64, Watt watts, Temp temp);
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
class InternalVibrator : virtual public ElectricDildo {
public:
    using Hertz = int;
private:
    Hertz frequency;
public:
/*constructors*/
        InternalVibrator(int price, int diam, int length, Color color, string img64, Watt watts, Hertz frequency);
        InternalVibrator(const InternalVibrator &iv);

/*getters and setters*/
        Hertz getFrequency() const;
        void setFrequency(Hertz frequency);

/*virtual stuff*/
        static const char * const category;
        const char* getCategory() const;
        Dildo* clone() const;

};


#endif // DILDO_H
