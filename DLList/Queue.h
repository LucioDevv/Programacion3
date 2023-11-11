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
