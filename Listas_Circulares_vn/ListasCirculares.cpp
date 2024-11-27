/***********************************************************************
 * Module:  ListasCirculares.cpp
 * Author:  Erika Guayanay
 * Date: 25/11/2024
 * Purpose: Lista de Personas con Listas Circulares
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "ListasCirculares.h"
#include <iostream>
#include <algorithm>

ListaCircular::ListaCircular() : primero(nullptr), ultimo(nullptr) {}

bool ListaCircular::validarCedulaUnica(string cedula) {
    Nodo* actual = primero;
    if (actual == nullptr) return true;

    do {
        if (actual->getCedula() == cedula) {
            return false;
        }
        actual = actual->getSiguiente();
    } while (actual != primero);

    return true;
}

void ListaCircular::insertar(string cedula, string nombre, string apellido) {
    if (!validarCedulaUnica(cedula)) {
        cout << "Error: La cédula ya existe en la lista.\n";
        return;
    }

    Nodo* nuevo = new Nodo(cedula, nombre, apellido);
    if (primero == nullptr) {
        primero = nuevo;
        ultimo = nuevo;
        nuevo->setSiguiente(nuevo);
    } else {
        ultimo->setSiguiente(nuevo);
        nuevo->setSiguiente(primero);
        ultimo = nuevo;
    }
    cout << "Persona ingresada correctamente.\n";
}

Nodo* ListaCircular::buscar(string cedula) {
    Nodo* actual = primero;
    if (actual == nullptr) return nullptr;

    do {
        if (actual->getCedula() == cedula) {
            return actual;
        }
        actual = actual->getSiguiente();
    } while (actual != primero);

    return nullptr;
}

bool ListaCircular::eliminar(string cedula) {
    if (primero == nullptr) {
        cout << "La lista está vacía.\n";
        return false;
    }

    Nodo* actual = primero;
    Nodo* anterior = nullptr;
    bool encontrado = false;

    do {
        if (actual->getCedula() == cedula) {
            encontrado = true;
            break;
        }
        anterior = actual;
        actual = actual->getSiguiente();
    } while (actual != primero);

    if (!encontrado) {
        cout << "Cédula no encontrada.\n";
        return false;
    }

    if (actual == primero) {
        if (primero == ultimo) {
            primero = nullptr;
            ultimo = nullptr;
        } else {
            primero = primero->getSiguiente();
            ultimo->setSiguiente(primero);
        }
    } else if (actual == ultimo) {
        anterior->setSiguiente(primero);
        ultimo = anterior;
    } else {
        anterior->setSiguiente(actual->getSiguiente());
    }

    delete actual;
    cout << "Persona eliminada correctamente.\n";
    return true;
}

void ListaCircular::mostrar() {
    Nodo* actual = primero;
    if (actual == nullptr) {
        cout << "NULL\n";
        return;
    }

    do {
        cout << "<Cédula: " << actual->getCedula() << ", Nombre: " << actual->getNombre()
             << ", Apellido: " << actual->getApellido() << "> -> ";
        actual = actual->getSiguiente();
    } while (actual != primero);

    cout << "(Regresa al inicio)\n";
}

void ListaCircular::eliminarCaracter(string cedula, char caracter) {
    Nodo* actual = buscar(cedula);
    if (actual == nullptr) {
        cout << "Cédula no encontrada.\n";
        return;
    }

    string nuevoNombre = actual->getNombre();
    string nuevoApellido = actual->getApellido();

    nuevoNombre.erase(remove(nuevoNombre.begin(), nuevoNombre.end(), caracter), nuevoNombre.end());
    nuevoApellido.erase(remove(nuevoApellido.begin(), nuevoApellido.end(), caracter), nuevoApellido.end());

    actual->setNombre(nuevoNombre);
    actual->setApellido(nuevoApellido);

    cout << "Carácter eliminado correctamente.\n";
}
