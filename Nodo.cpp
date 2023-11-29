#include "Nodo.h"

template <class T>
Nodo<T>::Nodo(T value) {
    next = nullptr;
    this->value = value;
}

template <class T>
Nodo<T>::~Nodo() {}

template <class T>
T Nodo<T>::getValue() {
    return this->value;
}

template <class T>
void Nodo<T>::setValue(T value) {
    this->value = value;
}

template <class T>
void Nodo<T>::setNext(Nodo<T>* nodo) {
    next = nodo;
}

template <typename T>
Nodo<T>* Nodo<T>::getNext() {
    return this->next;
}
