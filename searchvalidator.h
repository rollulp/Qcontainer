#ifndef SEARCHVALIDATOR_H
#define SEARCHVALIDATOR_H
#include "dildo.h"
#include "validator.h"

/*!
 * \class SearchValidator
 * implementazione di Validator per la classe Dildo.
 * Possiede un campo AttributeBoundaries per ricordarsi
 * lo stato della ricerca.
 * L' operatore parentesi tonde definisce il funtore
 * di validazione che ritorna il booleano di validità
 */
class SearchValidator : public Validator<Dildo> {
public:
    /*!
     * \enum Category
     * \brief Dildo types needed for AttributeBoundaries to work
     */
    enum Category {
        SimpleDildo = 1 << 0,
        DoubleDildo = 1 << 1,
        ThermoDildo = 1 << 2,
        InternalVibrator = 1 << 3,
        DildoDeluxe = 1 << 4
    };
    /*!
     * \struct AttributeBoundaries
     * Non ho ritenuto necessario incapsulare;
     * AttributeBoundaries la visualizzo molto di più
     * come una struct del C che come una classe.
     * Dopotutto è solo una collezione di bool e int,
     * voglio evitare masse di codice assurde.
     */
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
        bool diam2;
        int diam2min, diam2max;
        bool watt;
        int wattmin, wattmax;
        bool freq;
        int freqmin, freqmax;
        bool temp;
        int tempmin, tempmax;
    } bounds;
    SearchValidator(const SearchValidator &searchValidator);
    SearchValidator(const AttributeBoundaries &boundaries);
    bool operator() (const Dildo &dildo) const override;
    Validator<Dildo>* clone() const override;
};
#endif // SEARCHVALIDATOR_H
