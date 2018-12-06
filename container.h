#ifndef CONTAINER_H
#define CONTAINER_H
#include <cstddef>
#include <type_traits>
#include "deepptr.h"

template <typename T>
class Container {
    DeepPtr<T>* data;
    size_t len;
    size_t reserved;
protected:
    DeepPtr<T>& getDeepPtr(size_t i) const {
        if(i < len)
            return data[i];
        return data[0]; //TODO array index out of bounds ERR
    }
public:
    Container() : data(new DeepPtr<T>[2*0]), len(0), reserved(2*0) {
        /*se voglio generare un Container<T> dove
        * (is_default_constructible<T>::value == false)
        * non posso generare un metodo con (data[i] = new T)
        * nemmeno se (new T) non esegue mai.
        * In questo modo Container<T> si comporta con std::vector<T> per la costruzione,
        * mantenendo gli standard STL.
        */
    }

    Container(size_t n) : data(new DeepPtr<T>[2*n]), len(n), reserved(2*n) {
            for (size_t i = 0; i < len; i++)
                data[i] = new T;
    }
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
    template < typename U = T, typename std::enable_if< std::is_default_constructible<U>::value >::type >
    void resize(size_t newsize) {
        if (newsize > reserved)
            reserve(newsize*2);
        for(size_t i = len; i < newsize; i++)
            data[i] = new T;
        len = newsize;

    }
    /* if is default constructible pass reference
     * to insert element
    */
    template < typename U = T>
    typename std::enable_if< std::is_default_constructible<U>::value >::type
    insert_into(const U& t, size_t n) {
        if (n > len)
            return; // TODO ERR
        if(len == reserved)
            reserve((len+1)*2);
        for(size_t i = len; i > n; i--)
            data[i].eat(data[i-1]);
        data[n] = new U(t);
        len++;
    }
    /* if is not default constructible pass pointer
     * to insert element
    */
    template < typename U = T>
    typename std::enable_if< ! std::is_default_constructible<U>::value, void>::type
    insert_into(const T* t, size_t n) {
        if (n > len)
            return; // TODO ERR
        if(len == reserved)
            reserve((len+1)*2);
        for(size_t i = len; i > n; i--)
            data[i].eat(data[i-1]);
        data[n] = t;
        len++;
    }
    void delete_at(size_t n) {
        if (n >= len)
            return; // TODO ERR
        len--;
        for(size_t i = n; i < len; i++) {
            data[i].eat(data[i+1]);
        }
    }
    /* if is default constructible pass reference
     * to insert element
    */
    template < typename U = T>
    typename std::enable_if< ! std::is_default_constructible<U>::value, void>::type
    push_back(const T& t) {
        insert_into(t, len);
    }
    /* if is not default constructible pass pointer
     * to insert element
    */
    template < typename U = T>
    typename std::enable_if< ! std::is_default_constructible<U>::value, void>::type
    push_back(const T* t) {
        insert_into(t, len);
    }
    T& operator [] (size_t i) const {
        if(i < len)
            return data[i].get();
        return data[0].get(); //TODO array index out of bounds ERR
    }
};

#endif // CONTAINER_H
