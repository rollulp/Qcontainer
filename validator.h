#ifndef VALIDATOR_H
#define VALIDATOR_H

/*!
 * \class Validator
 * classe funtore base astratta dove l'operatore parentesi
 * ritorna un booleano che va a rappresentare se l'oggetto
 * argomento sottostà al criterio.
 */
template <typename T>
class Validator {
public:
    /// solo perchè è alla base della gerarchia, distruttore virtuale
    virtual ~Validator() {}

    /// per replicare l' istanza della classe
    virtual Validator<T>* clone() const = 0;

    /// operatore di validazione
    virtual bool operator () (const T &) const = 0;
};

#endif // VALIDATOR_H
