#include "Lista_Simple.h"
#include <iostream>
#include <algorithm> // Asegúrate de incluir este encabezado

using namespace std;

ListaSimple::ListaSimple() : cabeza(nullptr) {}

ListaSimple::~ListaSimple() {
    Nodo* temp;
    while (cabeza != nullptr) {
        temp = cabeza;
        cabeza = cabeza->getSiguiente();
        delete temp;
    }
}

bool ListaSimple::validarCedulaUnica(string cedula) {
    Nodo* temp = cabeza;
    while (temp != nullptr) {
        if (temp->getCedula() == cedula) {
            return false;
        }
        temp = temp->getSiguiente();
    }
    return true;
}

void ListaSimple::insertarACola(string cedula, string nombre, string apellido) {
    if (!validarCedulaUnica(cedula)) {
        cout << "Error: La cedula ya existe en la lista.\n";
        return;
    }

    Nodo* nuevo = new Nodo(cedula, nombre, apellido);
    if (cabeza == nullptr) {
        cabeza = nuevo;
    } else {
        Nodo* temp = cabeza;
        while (temp->getSiguiente() != nullptr) {
            temp = temp->getSiguiente();
        }
        temp->setSiguiente(nuevo);
    }
    //cout << "Persona ingresada correctamente.\n";
}

Nodo* ListaSimple::buscar(string cedula) {
    Nodo* temp = cabeza;
    while (temp != nullptr) {
        if (temp->getCedula() == cedula) {
            return temp;
        }
        temp = temp->getSiguiente();
    }
    return nullptr;
}

bool ListaSimple::eliminar(string cedula) {
    Nodo* temp = cabeza;
    Nodo* anterior = nullptr;

    while (temp != nullptr) {
        if (temp->getCedula() == cedula) {
            if (anterior == nullptr) {
                cabeza = temp->getSiguiente();
            } else {
                anterior->setSiguiente(temp->getSiguiente());
            }
            delete temp;
            //cout << "Persona eliminada correctamente.\n";
            return true;
        }
        anterior = temp;
        temp = temp->getSiguiente();
    }
    cout << "Persona con cédula " << cedula << " no encontrada.\n";
    return false;
}

void ListaSimple::mostrar() {
    Nodo* temp = cabeza;
    if (temp == nullptr) {
        cout << "NULL\n";
        return;
    }
    while (temp != nullptr) {
        cout << "Cédula: " << temp->getCedula()
             << "\nNombre: " << temp->getNombre()
             << "\nApellido: " << temp->getApellido() << " -> ";
        temp = temp->getSiguiente();
    }
    cout << "NULL\n";
}



void ListaSimple::eliminarCaracter(string cedula, char caracter, ListaSimple& listaAuxiliar) {
    Nodo* temp = buscar(cedula);
    if (temp == nullptr) {
        cout << "Cedula no encontrada.\n";
        return;
    }

    string nuevoNombre = temp->getNombre();
    string nuevoApellido = temp->getApellido();

    // Eliminar el carácter del nombre
    nuevoNombre.erase(remove(nuevoNombre.begin(), nuevoNombre.end(), caracter), nuevoNombre.end());
    nuevoApellido.erase(remove(nuevoApellido.begin(), nuevoApellido.end(), caracter), nuevoApellido.end());

    // Actualizar los valores en el nodo original
    temp->setNombre(nuevoNombre);
    temp->setApellido(nuevoApellido);

    // Insertar en la lista auxiliar
    listaAuxiliar.insertarACola(temp->getCedula(), nuevoNombre, nuevoApellido);

    cout << "Caracter eliminado correctamente. Lista auxiliar actualizada.\n";
}
