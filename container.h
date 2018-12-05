#ifndef CONTAINER_H
#define CONTAINER_H
#include <cstddef>
#include "deepptr.h"

/*
Siccome è una template class
implemento i metodi nell' header
(altrimenti il linker si arrabbia ovviamente)
*/
template <typename T>
class Container {
    DeepPtr<T>* data;
    size_t len;
    size_t reserved;
public:

    Container(size_t n = 0) : data(new DeepPtr<T>[2*n]), len(n), reserved(2*n) {}
    Container(const Container<T> & rhs) : data(new DeepPtr<T>[2*rhs.len]), len(rhs.len), reserved(2*rhs.len) {
        for(size_t i = 0; i < len; i++)
            data[i] = rhs.data[i];
    }
    virtual ~Container() {
        delete [] data;
    }

    size_t size() const {
        return len;
    }
    void reserve(size_t newsize) {
        reserved = newsize;
        len = ((newsize<len) ? (newsize) : (len));
        DeepPtr<T>* tmp = new DeepPtr<T>[reserved];
        for(size_t i = 0; i < len; i++)
           tmp[i].eat(data[i]);
        delete [] data;
        data = tmp;
    }
    void resize(size_t newsize) {
        if (newsize <= reserved)
            return;
        reserve(newsize*2);
        for(size_t i = len; i < newsize; i++)
            data[i].eat(DeepPtr<int>(new T));
        len = newsize;

    }
    void insert_into(const T& t, size_t n) {
        if (n > len)
            return; // ERR
        if(len == reserved)
            reserve((len+1)*2);
        for(size_t i = len; i > n; i--)
            data[i].eat(data[i-1]);
        data[n].eat(DeepPtr<int>(new T(t)));
        len++;
    }
    void delete_at(size_t n) {
        if (n >= len)
            return; // ERR
        len--;
        for(size_t i = n; i < len; i++) {
            data[i].eat(data[i+1]);
        }
    }
    void push_back(const T& t) {
        insert_into(t, len);
    }
    T& operator [] (size_t i) const {
        if(i < len)
            return *data[i];
        return *data[0]; // array index out of bounds ERR
    }
};

#endif // CONTAINER_H
