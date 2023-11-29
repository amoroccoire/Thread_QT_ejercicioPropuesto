#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include "Nodo.h"

template <class T>
class ListaEnlazada {
private:
    Nodo<T>* root;

public:
    ListaEnlazada();

    ~ListaEnlazada();

    void insert(T value);

    bool quit(T value);

    Nodo<T>* search(T value);

    void show();
};

#endif // LISTAENLAZADA_H
