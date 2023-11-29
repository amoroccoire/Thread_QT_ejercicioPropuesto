#include "ListaEnlazada.cpp"
#include <QCoreApplication>
#include <QRandomGenerator>
#include <QTime>
#include <QDebug>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

const int NUMEROS = 20;
const int LIMITE = 10;
const int HILOS = 4;

mutex mutexLista;

void executeThread(int, ListaEnlazada<int>*);
void llenarLista(ListaEnlazada<int>*);
int getRandom(int, int);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ListaEnlazada<int>* listaEnteros = new ListaEnlazada<int>();
    llenarLista(listaEnteros);
    listaEnteros->show();

    //crear hilos
    thread hilos[HILOS];
    for (int i = 0; i < HILOS; i++) {
        hilos[i] = thread(executeThread, i, listaEnteros);
    }

    //esperar hilos
    for (int i = 0; i < HILOS; i++) {
        hilos[i].join();
    }
    qDebug() <<"ACABO\n";

    return a.exec();
}

void executeThread(int id, ListaEnlazada<int>* lista) {
    switch (id) {
    case 0: //eliminar
    {
        int cont0 = 0;
        while (cont0 < 10) {
            this_thread::sleep_for(chrono::seconds(1));
            lock_guard<mutex> lock(mutexLista);
            int eliminarInt = getRandom(1, LIMITE + 5);
            qDebug() << "HILO " << id;
            qDebug() << "ELIMINANDO: " << eliminarInt;

            //lock_guard<mutex> lock(mutexLista);
            if(lista->quit(eliminarInt))
                qDebug() << "\tValor " << eliminarInt <<" ha sido ELIMINADO exitosamente\n";
            else
                qDebug() << "\tNo se elimino " << eliminarInt << "\n";
            cont0++;
        }
        break;
    }

    case 1: //insertar
    {
        int cont1 = 0;
        while (cont1 < 10) {
            this_thread::sleep_for(chrono::seconds(1));
            lock_guard<mutex> lock(mutexLista);
            int insertarInt = getRandom(1, LIMITE + 5);

            qDebug() << "HILO " << id;
            qDebug() << "INSERTANDO: " << insertarInt <<"\n";
            //lock_guard<mutex> lock(mutexLista);
            lista->insert(insertarInt);
            cont1++;
        }
        break;
    }

    case 2: //buscar
    {
        int cont2 = 0;
        while (cont2 < 10) {
            this_thread::sleep_for(chrono::seconds(1));
            lock_guard<mutex> lock(mutexLista);
            int consultarInt = getRandom(1, LIMITE + 5);

            qDebug() << "HILO " << id;
            qDebug() << "BUSCANDO " << consultarInt;
            //lock_guard<mutex> lock(mutexLista);
            if (lista->search(consultarInt))
                qDebug() << "\t" << consultarInt << "Encontrado\n";
            else
                qDebug() << "\t" << consultarInt << "NO encontrado\n";
            cont2++;
        }
        break;
    }

    case 3: //modificar
    {
        int cont3 = 0;
        while (cont3 < 10) {
            this_thread::sleep_for(chrono::seconds(1));
            lock_guard<mutex> lock(mutexLista);
            int randInt = getRandom(1, LIMITE + 5);
            //lock_guard<mutex> lock(mutexLista);
            Nodo<int>* nodo = lista->search(randInt);
            qDebug() << "HILO " << id;
            qDebug() << "MODIFICANDO " << randInt << " a " << (randInt + 5);
            if (nodo){
                int newValue = nodo->getValue() + 5;
                nodo->setValue(newValue);
                qDebug() << "\tHECHO\n";
            }
            else
                qDebug() << "\tNo se encontro\n";
            cont3++;
        }
        break;
    }
    default:
        break;
    }
}

void llenarLista(ListaEnlazada<int>* lista) {
    for (int i = 0; i < NUMEROS; i++) {
        int randomInt = getRandom(1, LIMITE);
        lista->insert(randomInt);
    }
}

int getRandom(int inicio, int fin) {
    QRandomGenerator* randomGenerator = new QRandomGenerator();
    randomGenerator->seed(QRandomGenerator::global()->generate());
    int randomInt = randomGenerator->bounded(inicio, fin + 1);
    return randomInt;
}
