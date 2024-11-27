/***********************************************************************
 * Module:  ListasDoble.cpp
 * Author:  Erika Guayanay.
 * Date: 25/11/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "ListasDoble.h"
#include <iostream>
#include <algorithm>
using namespace std;

ListaDoble::ListaDoble() : primero(nullptr), ultimo(nullptr) {}

ListaDoble::~ListaDoble() {
    Nodo* temp;
    while (primero != nullptr) {
        temp = primero;
        primero = primero->getSiguiente();
        delete temp;
    }
}

bool ListaDoble::validarCedulaUnica(string cedula) {
    Nodo* temp = primero;
    while (temp != nullptr) {
        if (temp->getCedula() == cedula) {
            return false;
        }
        temp = temp->getSiguiente();
    }
    return true;
}

void ListaDoble::insertar(string cedula, string nombre, string apellido) {
    if (!validarCedulaUnica(cedula)) {
        cout << "Error: La c�dula ya existe en la lista.\n";
        return;
    }

    Nodo* nuevo = new Nodo(cedula, nombre, apellido);
    if (primero == nullptr) {
        primero = nuevo;
        ultimo = nuevo;
    } else {
        ultimo->setSiguiente(nuevo);
        nuevo->setAnterior(ultimo);
        ultimo = nuevo;
    }
    cout << "Persona ingresada correctamente.\n";
}

Nodo* ListaDoble::buscar(string cedula) {
    Nodo* temp = primero;
    while (temp != nullptr) {
        if (temp->getCedula() == cedula) {
            return temp;
        }
        temp = temp->getSiguiente();
    }
    return nullptr;
}

bool ListaDoble::eliminar(string cedula) {
    Nodo* temp = buscar(cedula);
    if (temp == nullptr) {
        cout << "Persona con cedula " << cedula << " no encontrada.\n";
        return false;
    }

    if (temp == primero) {
        primero = primero->getSiguiente();
        if (primero != nullptr) {
            primero->setAnterior(nullptr);
        } else {
            ultimo = nullptr;
        }
    } else if (temp == ultimo) {
        ultimo = ultimo->getAnterior();
        if (ultimo != nullptr) {
            ultimo->setSiguiente(nullptr);
        } else {
            primero = nullptr;
        }
    } else {
        temp->getAnterior()->setSiguiente(temp->getSiguiente());
        temp->getSiguiente()->setAnterior(temp->getAnterior());
    }

    delete temp;
    cout << "Persona eliminada correctamente.\n";
    return true;
}

void ListaDoble::mostrar() {
    Nodo* temp = primero;
    if (temp == nullptr) {
        cout << "NULL\n";
        return;
    }
    while (temp != nullptr) {
        cout << "<Cedula: " << temp->getCedula() << ", Nombre: " << temp->getNombre() << ", Apellido: " << temp->getApellido() << "> -> ";
        temp = temp->getSiguiente();
    }
    cout << "NULL\n";
}

void ListaDoble::eliminarCaracter(string cedula, char caracter) {
    Nodo* temp = buscar(cedula);
    if (temp == nullptr) {
        cout << "Cedula no encontrada.\n";
        return;
    }

    string nuevoNombre = temp->getNombre();
    string nuevoApellido = temp->getApellido();

    nuevoNombre.erase(remove(nuevoNombre.begin(), nuevoNombre.end(), caracter), nuevoNombre.end());
    nuevoApellido.erase(remove(nuevoApellido.begin(), nuevoApellido.end(), caracter), nuevoApellido.end());

    temp->setNombre(nuevoNombre);
    temp->setApellido(nuevoApellido);

    cout << "Caracter eliminado correctamente.\n";
}
