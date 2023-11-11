DLList.h

```
#ifndef DLLIST_DLLIST_H
#define DLLIST_DLLIST_H

template <typename Object>
class DLList{
private:
    struct Node  {
        Object data;
        Node *next;
        Node *prev;

        //Constructor de copia
        Node(const Object &d = Object{}, Node *n = nullptr)
                : data{d}, next{n}, prev{n} {}

        //Constructor de referencia
        Node(Object &&d, Node *n = nullptr)
                : data{std::move(d)}, next{n}, prev{n} {}
    };

public:
    class iterator{
    public:
        //Constructor implicito, el puntero se vuelve nulo
        iterator() : current{nullptr} {}

        //Operador * para que se comporte como puntero
        Object &operator*() {
            if(current == nullptr)
                throw std::logic_error("Trying to dereference a null pointer.");
            return current->data;
        }

        //Operador hace que pueda moverse por la lista.
        iterator &operator++() {
            if(current)
                current = current->next;
            else
                throw std::logic_error("Trying to increment past the end.");
            return *this;
        }

        iterator operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }

        iterator &operator--() {
            if(current)
                current = current->prev;
            else
                throw std::logic_error("Trying to decrease past the beginning.");
            return *this;
        }

        iterator operator--(int) {
            iterator old = *this;
            --(*this);
            return old;
        }

        //Operadores para realizar comparaciones
        bool operator==(const iterator &rhs) const {
            return current == rhs.current;
        }

        bool operator!=(const iterator &rhs) const {
            return !(*this == rhs);
        }

    private:

        //Apunta al nodo en el que se este trabajando en ese momento
        Node *current;
        iterator(Node *p) : current{p} {}
        friend class DLList<Object>;
    };

public:
    //Definir la dimension de la lista
    //Cuando se llame el constructor, ya tiene que existir una cabeza y una cola
    DLList() : head(new Node()), tail(new Node()), theSize(0) {
        head->next = tail;
    }

    //Destructor de la lista
    //Primero se borra el contenido dentro de la lista y despues la cola y la cabeza
    ~DLList() {
        clear();
        delete head;
        delete tail;
    }

    //Funciones que meten el iterador a lado de la cabeza o en la cola
    iterator begin() { return {head->next}; }
    iterator end() { return {tail}; }

    //el tamaño de la lista, o si esta estuviera vacia que la regresara como vacia.
    int size() const { return theSize; }
    bool empty() const { return size() == 0; }

    //Mientras no este vacia borra el objeto de en frente
    void clear() { while (!empty()) pop_front(); }

    //Si la lista esta vacia da un error, si no retorna el inicio
    Object &front() {
        if(empty())
            throw std::logic_error("List is empty.");
        return *begin();
    }

    //funcion de push por copia
    void push_front(const Object &x) { insert(begin(), x); }
    //funcion de push por referencia
    void push_front(Object &&x) { insert(begin(), std::move(x)); }

    void push_back(const Object &x) { insert(end(), x); }
    //funcion de push por referencia
    void push_back(Object &&x) { insert(end(), std::move(x)); }




    //Elimina el valor de en frente, si esta vacia, mencione que este vacia.
    void pop_front() {
        if(empty())
            throw std::logic_error("List is empty.");
        erase(begin());
    }

    //Recibe un iterador, lee esa posicion e inserta un código en la posicion que le demos
    iterator insert(iterator itr, const Object &x) {
        Node *p = itr.current;
        head->next = new Node{x, head->next};
        theSize++;
        return iterator(head->next);
    }

    //Este funciona por referencia
    iterator insert(iterator itr, Object &&x) {
        Node *p = itr.current;
        head->next = new Node{std::move(x), head->next};
        theSize++;
        return iterator(head->next);
    }

    void insert(int pos, const Object &x) {
        insert(get_iterator(pos), x);
    }

    iterator get_iterator(int a)
    {
        iterator it = begin();
        for(int i = 0; i != a; ++i) {
            ++it;
        }
        return it;
    }

    //recibe un iterador y borra el dato en la posicion que le digamos, si el iterador esta al final no se puede borrar de alli.
    iterator erase(iterator itr) {

        if (itr == end())
            throw std::logic_error("Cannot erase at end iterator");
        Node *p = head;
        while (p->next != itr.current) p = p->next;
        p->next = itr.current->next;
        delete itr.current;
        theSize--;
        return iterator(p->next);
    }

    void erase(int pos)
    {
        erase(get_iterator(pos));
    }

    //Getter para toda la lista
    void print() {
        iterator itr = begin();
        while (itr != end()) {
            std::cout << *itr << " ";
            ++itr;
        }
        std::cout << std::endl;
    }



private:
    Node *head;
    Node *tail;
    int theSize;
    //init necesita acceso a los datos privados para inicializar una lista vacia
    void init() {
        theSize = 0;
        head->next = tail;
    }


};
#endif //DLLIST_DLLIST_H
```

Queue.h

```
#ifndef QUEUE_H
#define QUEUE_H

template<typename Data>
class Queue : private DLList<Data>{ // Se crea la clase Queue que hereda de DLList con Data
public:
    Queue(){
        DLList<Data>::init(); // Inicializa la Queue en init declarado en DLList
    }

    ~Queue(){
        clear(); // Llama a la función clear
        delete DLList<Data>::head; // Elimina la cabeza
        delete DLList<Data>::tail; // Elimina la cola
    }

    void enqueue(Data &data){
        DLList<Data>::push_back(data); // Inserta data al final de Queue por copia
    }

    void enqueue(Data &&data){
        DLList<Data>::push_back(data); // Inserta data al final de Queue por referencia
    }

    void dequeue(){
        DLList<Data>::pop_front(); // Elimina data al principio de la cola
    }

    void print(){
        DLList<Data>::print(); // Imprime Queue
    }

    void clear(){
        DLList<Data>::clear(); // Elimina Queue
    }

    Data front(){
        return DLList<Data>::head->next->data; // Imprime solo el primer valor de Queue
    }
};

#endif 
```

SLList.h

```
#ifndef SLLIST_H
#define SLLIST_H

#include <iostream>
#include <utility>

template <typename Object>
class SLList {
private:

    struct Node  {
        Object data; 
        Node *next;   

        Node(const Object &d = Object{}, Node *n = nullptr)
                : data{d}, next{n} {}

        Node(Object &&d, Node *n = nullptr)
                : data{std::move(d)}, next{n} {}
    };

public:
    class iterator {
    public:
        iterator() : current{nullptr} {}

        Object &operator*() {
            if(current == nullptr)
                throw std::logic_error("Intentando desreferenciar un puntero nulo.");
            return current->data;
        }

        iterator &operator++() {
            if(current)
                current = current->next;
            else
                throw std::logic_error("Intentando incrementar más allá del final.");
            return *this;
        }

        iterator operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }

        bool operator==(const iterator &rhs) const {
            return current == rhs.current;
        }

        bool operator!=(const iterator &rhs) const {
            return !(*this == rhs);
        }

    private:
        Node *current;
        iterator(Node *p) : current{p} {}
        friend class SLList<Object>;
    };

public:
    SLList() : head(new Node()), tail(new Node()), theSize(0) {
        head->next = tail;
    }

    ~SLList() {
        clear();
        delete head;
        delete tail;
    }

    iterator begin() { return {head->next}; }
    iterator end() { return {tail}; }

    int size() const { return theSize; }
    bool empty() const { return size() == 0; }

    void clear() { while (!empty()) pop_front(); }

    Object &front() {
        if(empty())
            throw std::logic_error("La lista está vacía.");
        return *begin();
    }

    void push_front(const Object &x) { insert(begin(), x); }
    void push_front(Object &&x) { insert(begin(), std::move(x)); }

    void pop_front() {
        if(empty())
            throw std::logic_error("La lista está vacía.");
        erase(begin());
    }

    iterator insert(iterator itr, const Object &x) {
        Node *p = itr.current;
        head->next = new Node{x, head->next};
        theSize++;
        return iterator(head->next);
    }

    iterator insert(iterator itr, Object &&x) {
        Node *p = itr.current;
        head->next = new Node{std::move(x), head->next};
        theSize++;
        return iterator(head->next);
    }

    iterator erase(iterator itr) {
        if (itr == end())
            throw std::logic_error("No se puede borrar en el iterador final");
        Node *p = head;
        while (p->next != itr.current) p = p->next;
        p->next = itr.current->next;
        delete itr.current;
        theSize--;
        return iterator(p->next);
    }

    void print() {
        iterator itr = begin();
        while (itr != end()) {
            std::cout << *itr << " ";
            ++itr;
        }
        std::cout << std::endl;
    }

private:
    Node *head;
    Node *tail;
    int theSize;
    void init() {
        theSize = 0;
        head->next = tail;
    }
};

#endif //SLLIST_H
```

Stack.h

```
#include <iostream>
#include <cstdlib>
#include <stack>
#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack : private DLList<T> { // Crea la clase Stack que hereda de DLList con tipo T
public:
    Stack() {
        DLList<T>::init(); // Inicializa Stack en init definido en DLList
    }

    ~Stack(){
        clear(); // Llama a la función clear
        delete DLList<T>::head; // Elimina la cabeza
        delete DLList<T>::tail; // Elimina la cola
    }

    void push(T &data){
        DLList<T>::push_front(data); // Inserta datos al principio de la pila por copia
    }
    void push(T &&data){
        DLList<T>::push_front(data); // Inserta datos al principio de la pila por referencia
    }

    void pop(){
        DLList<T>::pop_front(); // Elimina datos al principio de la pila
    }

    void clear(){
        DLList<T>::clear(); // Limpia la pila
    }

    void print(){
        DLList<T>::print(); // Imprime la pila
    }

    T top(){
        return DLList<T>::head->next->data; // Imprime solo el primer valor
    }
};

#endif //STACK_H
```

