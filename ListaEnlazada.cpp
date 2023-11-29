#include "ListaEnlazada.h"
#include "Nodo.cpp"
#include <QDebug>

template <class T>
ListaEnlazada<T>::ListaEnlazada() {
    root = nullptr;
}

template <class T>
ListaEnlazada<T>::~ListaEnlazada() {
    while (root) {
        Nodo<T>* temp = root;
        root = root->getNext();
        delete temp;
    }
}

template <class T>
void ListaEnlazada<T>::insert(T value) {
    Nodo<T>* nuevoNodo = new Nodo<T>(value);
    if (root == nullptr)
        this->root = nuevoNodo;
    else {
        Nodo<T>* aux = root;
        while (aux->getNext() != nullptr) {
            aux = aux->getNext();
        }
        aux->setNext(nuevoNodo);
    }
}

template <class T>
bool ListaEnlazada<T>::quit(T value) {
    bool succes = false;
    if (root == nullptr)
        return succes;

    Nodo<T>* aux = root;
    Nodo<T>* prev = nullptr;
    while (aux != nullptr && aux->getValue() != value) {
        prev = aux;
        aux = aux->getNext();
    }

    if (aux != nullptr) {
        if (prev != nullptr) {
            prev->setNext(aux->getNext());
            delete aux;
        } else {
            root = aux->getNext();
            delete aux;
        }
        return !succes;
    }
    return succes;
}

template <class T>
Nodo<T>* ListaEnlazada<T>::search(T value) {
    Nodo<T>* aux = root;
    while (aux != nullptr && aux->getValue() != value) {
        aux = aux->getNext();
    }

    if (aux)
        return aux;
    return nullptr;
}

template <class T>
void ListaEnlazada<T>::show() {
    Nodo<T>* aux = root;
    while (aux) {
        qDebug() << aux->getValue() << " ";
        aux = aux->getNext();
    }
    qDebug() << "\n";
}
