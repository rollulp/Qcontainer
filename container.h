#ifndef CONTAINER_H
#define CONTAINER_H
#include "myexception.h"
#include "validator.h"

template <typename T>
class Container {
public:
    class iterator; // foward declare

private:
    /*!
      \class node
      \brief Nodo della linked list, con T* e due node*
    */
    class node {
        /*!
         * tutto è private e ci sono due classi friend
         * per vincolare node a essere usato solo in Container<T>
        */

        T *info;
        node *previous, *next;

        /*!
         * \brief costruttore per collocare il nodo in posizione
         * \param info puntatore all' oggetto da inserire
         * \param previous nodo precedente
         * \param next nodo successivo
         */
        node(T *info, node *previous = nullptr, node *next = nullptr)
            : info(info), previous(previous), next(next) {
				if (previous)
					previous->next = this;
				if (next)
					next->previous = this;
		}

        /// non permetto la costruzione di copia
        node(const node&) = delete;

        /// non permetto l' assegnamento
        node& operator = (const node&) = delete;

        /// delete dell' oggetto
        ~node() {
            if (info)
                delete info;
        }

        friend class Container;
        friend class iterator;
    };

    /*!
     * \brief first inizio coda
     * \brief last fine coda
     */
    node *first, *last;

public:
    /*!
      \class iterator
     * \brief iterator per iterare nel Container
     */
    class iterator {
        /*!
         * \class accept_all
         * \brief Validator che convalida tutti gli oggetti
         */
        class accept_all : public Validator<T> {
            // qui implemento i metodi virtuali puri di Validator<T>
            bool operator () (const T&) const { return true; }
            accept_all* clone() const { return new accept_all; }
        };
        Validator<T> *validate;
        node *current;

        /*!
         * \brief costruttore per iterare su Container solo sugli oggetti validabili
         * \param first inizio della sequenza
         * \param validate Validator per validare la sequenza, come default valida tutto
         */
        iterator(node *first, Validator<T> *validate = nullptr) : validate(validate), current(first) {
            if (!validate)
                this->validate = new accept_all;
            // vai avanti fino al primo elemento validato
            if ( current && ! (*(this->validate))(*(current->info)) )
                operator ++();
        }

        /// cancella l'oggetto, privata e utilizzabile solo da Container<T>
        void trash() const {
            if (! current)
                return;
            if (current->previous)
                current->previous->next = current->next;
            if (current->next)
                current->next->previous = current->previous;
            delete current;
        }

        /// Container ha potere assoluto su iterator come su node
        friend class Container;

    public:
        /// Copy constructor chiama Validator<T>::clone
        iterator(const iterator& it)
            : validate(it.validate->clone()), current(it.current) {}

        /// Assignment operator per finire la rule of three
        iterator& operator = (const iterator &it) {
            if (validate)
                delete validate;
            validate = it.validate->clone();
            current = it.current;
        }

        /// delete dell' oggetto
        virtual ~iterator() {
            delete validate;
        }

        /// per verificare se l'iteratore ha finito il container, cast a bool
        operator bool() const {
            return current;
        }

        /// per passare al nodo seguente nella sequenza
        // (ho scelto di non fare anche l'operatore postfisso it++, ma tenere solo ++it )
        T* operator ++() {
            if ( current )
            do { current = current->next; }
            while ( current && !(*validate)(*(current->info)) );
            return current ? current->info : nullptr;
        }

        ///per accedere all elemento come referenza
        T& operator * () const { return *(current->info); }

        ///per accedere all elemento come puntatore
        T* operator ->() const { return current->info; }
    };

    /// container vuoto
    Container() : first(nullptr), last(nullptr) {}

    /// non permetto la costruzione di copia
    Container(const Container<T> & rhs) = delete;
    virtual ~Container() {
        while (first)
            remove( begin() );
    }

    /// per inserire un elemento all' inizio della lista
    void push_front(T* info) {
        first = new node(info, nullptr, first);
        if (!last)
			last = first;
    }

    /// per inserire un elemento all' inizio della lista
    void push_front(const T &info) {
        push_front(new T(info));
    }

    /// per inserire un elemento alla fine della lista
    void push_back(T *info) {
		last = new node(info, last, nullptr);
		if (!first)
			first = last;
	}

    /// per inserire un elemento alla fine della lista
	void push_back(const T &info) {
		push_back(new T(info));
	}

    /*!
     * \brief per iterare su Container
     * \param validate criterio di selezione elementi della lista
     * \return Iteratore alla sottolista che soddisfa il criterio
     */
    iterator select(Validator<T> *validate) const {
        return iterator(first, validate);
    }

    /// iteratore all inizio di una lista
    iterator begin() const {
        return iterator(first);
    }

    /// iteratore all ultimo oggetto della lista
    iterator end() const {
        return iterator(last);
    }

    /// per rimuovere un oggetto dalla lista;
    /// serve controllare se sia all inizio o alla fine
    /// per far si che fist e last puntino a valori validi
    void remove(iterator it) {
        if (it.current == first)
            first = first->next;
        else if (it.current == last)
            last = last->previous;
        it.trash();
    }

};

#endif // CONTAINER_H











