#ifndef CONTAINER_H
#define CONTAINER_H
#include "myexception.h"
#include "validator.h"

template <typename T>
class Container {
public:
    class iterator;

public://change
    class node {
        T *info;
        node *previous, *next;
        node(T *info, node *previous = nullptr, node *next = nullptr)
            : info(info), previous(previous), next(next) {
				if (previous)
					previous->next = this;
				if (next)
					next->previous = this;
		}
        node(const node&) = delete;
        node& operator = (const node&) = delete;
        ~node() { if (info) delete info; }
        friend class Container;
        friend class iterator;
    } *first, *last;

public:
    class iterator {
        class accept_all : public Validator<T> {
            bool operator () (const T&) const { return true; }
            accept_all* clone() const { return new accept_all; }
        };
        Validator<T> *validate;
        node *current;

        iterator(node *first, Validator<T> *validate = nullptr) : validate(validate), current(first) {
            if (!validate)
                this->validate = new accept_all;
            if ( current && ! (*(this->validate))(*(current->info)) )
                operator ++();
        }
        friend class Container;

    public:
        void *cur() const { return current; }
        void null() { current = nullptr; }
        iterator(const iterator& it)
            : validate(it.validate->clone()), current(it.current) {}
        iterator& operator = (const iterator &it) {
            if (validate)
                delete validate;
            validate = it.validate->clone();
            current = it.current;
        }
        virtual ~iterator() { delete validate; }
        operator bool() const { return current; }
        T* operator ++() {
            if ( current )
            do { current = current->next; }
            while ( current && !(*validate)(*(current->info)) );
            return current ? current->info : nullptr;
        }
        T& operator * () const { return *(current->info); }
        T* operator ->() const { return current->info; }
        void delete_and_advance() {
            if (! current)
                return;
            if (current->previous)
                current->previous->next = current->next;
            if (current->next)
                current->next->previous = current->previous;
            node *tmp = current;
            operator ++();
            delete tmp;
        }
    };

    Container() : first(nullptr), last(nullptr) {}
    Container(const Container<T> & rhs) = delete;
    virtual ~Container() {
        iterator it(first);
        while (it)
            it.delete_and_advance();
    }
    void push_front(T* info) {
        first = new node(info, nullptr, first);
        if (!last)
			last = first;
    }
    void push_front(const T &info) {
        push_front(new T(info));
    }
    void push_back(T *info) {
		last = new node(info, last, nullptr);
		if (!first)
			first = last;
	}
	void push_back(const T &info) {
		push_back(new T(info));
	}

    iterator select(Validator<T> *validate) const {
        return iterator(first, validate);
    }
    iterator begin() const {
        return iterator(first);
    }

};

#endif // CONTAINER_H











