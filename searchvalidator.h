#ifndef SEARCHVALIDATOR_H
#define SEARCHVALIDATOR_H
#include "dildo.h"

class SearchValidator {
public:
    enum Category {
        SimpleDildo = 1 << 0,
        DoubleDildo = 1 << 1,
        ThermoDildo = 1 << 2,
        InternalVibrator = 1 << 3,
        DildoDeluxe = 1 << 4
    };
    struct AttributeBoundaries {
        unsigned int categoryBitMap;
        bool colorCheck;
        Dildo::Color color;
        bool len;
        int lenmin, lenmax;
        bool price;
        int pricemin, pricemax;
        bool diam;
        int diammin, diammax;
        union {
            struct {
                bool diam2;
                int diam2min, diam2max;
            };
            struct {
                bool watt;
                int wattmin, wattmax;
            };
        };
        bool freq;
        int freqmin, freqmax;
        bool temp;
        int tempmin, tempmax;

    } bounds;
    SearchValidator(const AttributeBoundaries &boundaries);
    bool operator() (const Dildo &dildo) const;
};

#endif // SEARCHVALIDATOR_H
