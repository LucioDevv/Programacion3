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