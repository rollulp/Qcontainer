#ifndef VALIDATOR_H
#define VALIDATOR_H

template <typename T>
class Validator {
public:
    virtual ~Validator() {};
    virtual bool operator () (const T &) const = 0;
};

#endif // VALIDATOR_H
