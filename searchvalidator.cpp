#include "searchvalidator.h"
#include "myexception.h"

using Category = SearchValidator::Category;

SearchValidator::SearchValidator(const AttributeBoundaries &bounds)
    : bounds(bounds)
{}

static inline Category getCategory(const Dildo &dildo) {
    const char* const cat = dildo.getCategory();
    if ( cat == SimpleDildo::category )
        return Category::SimpleDildo;
    if ( cat == SimpleDildo::category )
        return Category::SimpleDildo;
    if ( cat == ThermoDildo::category )
        return Category::ThermoDildo;
    if ( cat == InternalVibrator::category )
        return Category::InternalVibrator;
    if ( cat == DildoDeluxe::category )
        return Category::DildoDeluxe;
    throw MyException("Just what is this Dildo instance of??");
}
static inline bool is_outside_range(const bool check, int min, int val, int max) {
    return check && (val < min || val > max);
}
bool SearchValidator::operator()(const Dildo &dildo) const {
    const Category category = getCategory(dildo);
    if (category^bounds.categoryBitMap)
        return false;
    // TODO only checks for category so far!
    return true;
}
