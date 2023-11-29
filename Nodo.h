#ifndef NODO_H
#define NODO_H

template <class T>
class Nodo {
private:
    T value;
    Nodo<T>* next;

public:
    Nodo(T value);

    ~Nodo();

    T getValue();

    void setValue(T value);

    void setNext(Nodo<T>* nodo);

    Nodo<T>* getNext();
};

#endif // NODO_H
