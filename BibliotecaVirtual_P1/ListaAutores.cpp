#include "ListaAutores.h"
#include "Validaciones.h"
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

ListaAutores::ListaAutores() : cabeza(nullptr) {}

ListaAutores::~ListaAutores() {
    if (cabeza) {
        NodoAutores* actual = cabeza;
        do {
            NodoAutores* siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        } while (actual != cabeza);
    }
}

bool ListaAutores::insertar(string cedula, string nombre, string apellido, string fechaPublicacion) {
    if (buscar(cedula)) {
        cout << "Error: Autor con cédula " << cedula << " ya existe.\n";
        return false;
    }

    NodoAutores* nuevo = new NodoAutores(cedula, nombre, apellido, fechaPublicacion);

    if (!cabeza) {
        cabeza = nuevo;
        cabeza->setSiguiente(cabeza);
        cabeza->setAnterior(cabeza);
    } else {
        NodoAutores* ultimo = cabeza->getAnterior();
        ultimo->setSiguiente(nuevo);
        nuevo->setAnterior(ultimo);
        nuevo->setSiguiente(cabeza);
        cabeza->setAnterior(nuevo);
    }
    guardarEnArchivoJSON(); // Usar JSON para guardar cambios
    cout << "Guardado Exitosamente.\n";
    return true;
}

NodoAutores* ListaAutores::buscar(string cedula) {
    if (!cabeza) return nullptr;

    NodoAutores* actual = cabeza;
    do {
        if (actual->getCedula() == cedula) {
            return actual;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    return nullptr;
}

bool ListaAutores::eliminar(string cedula) {
    NodoAutores* encontrado = buscar(cedula);
    if (!encontrado) {
        cout << "Error: Autor no encontrado.\n";
        return false;
    }

    if (encontrado->getSiguiente() == encontrado) {
        cabeza = nullptr;
    } else {
        NodoAutores* anterior = encontrado->getAnterior();
        NodoAutores* siguiente = encontrado->getSiguiente();
        anterior->setSiguiente(siguiente);
        siguiente->setAnterior(anterior);
        if (cabeza == encontrado) {
            cabeza = siguiente;
        }
    }
    delete encontrado;
    guardarEnArchivoJSON(); // Usar JSON para guardar cambios
    return true;
}

void ListaAutores::mostrar() {
    if (!cabeza) {
        cout << "Lista de autores vacía.\n";
        return;
    }

    NodoAutores* actual = cabeza;
    do {
        cout << "Cedula: " << actual->getCedula()
             << ", Nombre: " << actual->getNombre()
             << ", Apellido: " << actual->getApellido()
             << ", Fecha de Publicacion: " << actual->getFechaPublicacion() << "\n";
        actual = actual->getSiguiente();
    } while (actual != cabeza);
}

void ListaAutores::guardarEnArchivoJSON() {
    if (!cabeza) {
        cout << "La lista de autores esta vacia.\n";
        return;
    }

    json jAutores = json::array();

    NodoAutores* actual = cabeza;
    do {
        jAutores.push_back({
            {"cedula", actual->getCedula()},
            {"nombre", actual->getNombre()},
            {"apellido", actual->getApellido()},
            {"fechaPublicacion", actual->getFechaPublicacion()}
        });
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    std::ofstream archivo("autores.json");
    if (archivo.is_open()) {
        archivo << jAutores.dump(4);
        archivo.close();

    } else {
        cout << "Error: No se pudo abrir el archivo para guardar datos.\n";
    }
}

void ListaAutores::cargarDesdeArchivoJSON() {
    std::ifstream archivo("autores.json");
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo para cargar datos.\n";
        return;
    }

    json jAutores;
    archivo >> jAutores;
    archivo.close();

    for (const auto& autor : jAutores) {
        string cedula = autor["cedula"];
        string nombre = autor["nombre"];
        string apellido = autor["apellido"];
        string fechaPublicacion = autor["fechaPublicacion"];

        cout << "Cargando autor: " << cedula << ", " << nombre << ", " << apellido << "\n";
        insertar(cedula, nombre, apellido, fechaPublicacion);
    }

}
