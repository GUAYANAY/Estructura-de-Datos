#pragma once
#include "Nodo.h"
#include <string>
using namespace std;

class ListaSimple {
private:
    Nodo* cabeza;

public:
    ListaSimple();
    ~ListaSimple();

    void insertarACola(string cedula, string nombre, string apellido);
    Nodo* buscar(string cedula);
    bool eliminar(string cedula);
    void mostrar();
    void eliminarCaracter(string cedula, char caracter, ListaSimple& listaAuxiliar);
    bool validarCedulaUnica(string cedula);
};
