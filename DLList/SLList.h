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
