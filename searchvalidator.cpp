#include "searchvalidator.h"
#include "myexception.h"

#include <QDebug>

SearchValidator::SearchValidator(const AttributeBoundaries &bounds)
    : bounds(bounds)
{}

static inline SearchValidator::Category getCategory(const Dildo &dildo) {
    const char* const cat = dildo.getCategory();
    if ( cat == ::SimpleDildo::category )
        return SearchValidator::Category::SimpleDildo;
    if ( cat == ::DoubleDildo::category )
        return SearchValidator::Category::DoubleDildo;
    if ( cat == ::ThermoDildo::category )
        return SearchValidator::Category::ThermoDildo;
    if ( cat == ::InternalVibrator::category )
        return SearchValidator::Category::InternalVibrator;
    if ( cat == ::DildoDeluxe::category )
        return SearchValidator::Category::DildoDeluxe;
    throw MyException("Just what is this Dildo instance of??");
}
static inline bool is_outside_range(const bool check, int min, int val, int max) {
    return check && (val < min || val > max);
}
bool SearchValidator::operator()(const Dildo &dildo) const {

    const Category category = getCategory(dildo);
    if (!(category&bounds.categoryBitMap))
        return false;
    if ( bounds.colorCheck && (bounds.color!=dildo.getColor()) )
        return false;
    if ( is_outside_range(bounds.price, bounds.pricemin, dildo.getPrice(), bounds.pricemax) )
        return false;
    if (is_outside_range(bounds.len, bounds.lenmin, dildo.getLength(), bounds.lenmax))
        return false;
    if (is_outside_range(bounds.diam, bounds.diammin, dildo.getDiam(), bounds.diammax))
        return false;
    if ( category==DoubleDildo && is_outside_range(bounds.diam2, bounds.diam2min, static_cast<const ::DoubleDildo&>(dildo).getDiam2(), bounds.diam2max) )
        return false;
    if (  ( category==ThermoDildo || category==InternalVibrator || category==DildoDeluxe) &&
          is_outside_range(bounds.watt, bounds.wattmin, static_cast<const ::ElectricDildo&>(dildo).getWatts(), bounds.wattmax) )
        return false;
    if (  ( category==ThermoDildo || category==DildoDeluxe) &&
          is_outside_range(bounds.temp, bounds.tempmin, dynamic_cast<const ::ThermoDildo&>(dildo).getTemp(), bounds.tempmax) )
        return false;
    if (  ( category==InternalVibrator || category==DildoDeluxe) &&
          is_outside_range(bounds.freq, bounds.freqmin, dynamic_cast<const ::InternalVibrator&>(dildo).getFrequency(), bounds.freqmax) )
        return false;

    return true;
}
