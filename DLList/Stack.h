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
