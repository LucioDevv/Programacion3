```

#ifndef SLLLIST_H
#define SLLLIST_H


#include <iostream>
#include <utility>

template <typename Object> // Declara una plantilla donde todo lo llamado Object se reemplazará por un valor/clase
class SLList {
private:
    struct Node  {
        Object data;
        Node *next;

        Node(const Object &d = Object{}, Node *n = nullptr) // Declara un constructor de copia, así como un constructor predeterminado ya que es igual a 0
            : data{d}, next{n} {} // Apunta a n, con datos de d

        Node(Object &&d, Node *n = nullptr) // Declara un constructor de referencia
            : data{std::move(d)}, next{n} {} // Apunta a n, con datos de d
    };

public:
    class iterator { // Declara la clase iterator
    public:
        iterator() : current{nullptr} {} // Constructor predeterminado

        Object &operator*() { // Declara el puntero
            if(current == nullptr) // Si el puntero es 0, imprime un mensaje de error lógico
                throw std::logic_error("Intentando desreferenciar un puntero nulo.");
            return current->data; // Devuelve los datos actuales
        }

        iterator &operator++() { // Declara la adición a la siguiente posición
            if(current) // Si el puntero está en la posición actual, avanza a la siguiente posición
                current = current->next;
            else // Si el puntero no tiene un siguiente, imprime un mensaje de error lógico
                throw std::logic_error("Intentando incrementar más allá del final.");
            return *this;
        }

        iterator operator++(int) { // Usa ++ para determinar la posición
            iterator old = *this;
            ++(*this); // Añade 1 a la posición
            return old;
        }

        bool operator==(const iterator &rhs) const { // Declara ==, si ambas declaraciones son iguales, devuelve true, si no, devuelve false
            return current == rhs.current;
        }

        bool operator!=(const iterator &rhs) const { // Declara !=, si ambas declaraciones son iguales, devuelve false, si no, devuelve true
            return !(*this == rhs);
        }

    private:
        Node *current; // Puntero
        iterator(Node *p) : current{p} {} // Constructor
        friend class SLList<Object>; // Declara como amigo a la clase SLList
    };

public:
    SLList() : head(new Node()), tail(new Node()), theSize(0) { // Constructor predeterminado para listas
        head->next = tail;
    }

    ~SLList() { // Destructor
        clear();
        delete head;
        delete tail;
    }

    iterator begin() { return {head->next}; } // Obtiene el inicio de la lista
    iterator end() { return {tail}; } // Obtiene el final de la lista

    int size() const { return theSize; } // Obtiene el tamaño de la lista
    bool empty() const { return size() == 0; } // Comprueba si la lista está vacía, si lo está, devuelve true y false en caso contrario

    void clear() { while (!empty()) pop_front(); } // Mientras la lista no esté vacía, la limpia

    Object &front() { // Inicio de la Lista
        if(empty()) // Si el primer elemento está vacío, indica que está vacío, si no, da un valor
            throw std::logic_error("La Lista está vacía.");
        return *begin();
    }

    void push_front(const Object &x) { insert(begin(), x); } // Añade un nuevo elemento a la lista por copia
    void push_front(Object &&x) { insert(begin(), std::move(x)); } // Añade un nuevo elemento a la lista por referencia

    void pop_front() { // Borra el primer elemento a menos que la Lista esté vacía
        if(empty())
            throw std::logic_error("La Lista está vacía.");
        erase(begin());
    }

    iterator insert(iterator itr, const Object &x) { // Inserta un elemento donde está el puntero por copia
        Node *p = itr.current;
        head->next = new Node{x, head->next};
        theSize++;
        return iterator(head->next);
    }

    iterator insert(iterator itr, Object &&x) { // Inserta un elemento donde está el puntero por referencia
        Node *p = itr.current;
        head->next = new Node{std::move(x), head->next};
        theSize++;
        return iterator(head->next);
    }

    iterator erase(iterator itr) { // Borra el elemento donde está el puntero
        if (itr == end())
            throw std::logic_error("No se puede borrar en el iterador final");
        Node *p = head;
        while (p->next != itr.current) p = p->next;
        p->next = itr.current->next;
        delete itr.current;
        theSize--;
        return iterator(p->next);
    }

    void printList() { 
    // Imprime la lista, obtiene la posición actual del iterador, agrega a la posición del iterador y repite hasta que la lista termine
    
        iterator itr = begin();
        while (itr != end()) {
            std::cout << *itr << " ";
            ++itr;
        }
        std::cout << std::endl;
    }

private:
    Node *head; // Cabeza de la Lista
    Node *tail; // Cola de la Lista
    int theSize;
    void init() { // Inicializa las variables
        theSize = 0;
        head->next = tail;
    }
};

#endif


```