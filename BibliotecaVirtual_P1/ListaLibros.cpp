#include "ListaLibros.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "json.hpp"
#include "BackupManager.h"
using json = nlohmann::json;

ListaLibros::ListaLibros() : cabeza(nullptr) {}

ListaLibros::~ListaLibros() {
    if (cabeza) {
        NodoLibros* actual = cabeza;
        do {
            NodoLibros* siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        } while (actual != cabeza);
    }
}

bool ListaLibros::insertar(string titulo, string autor, string isbn, string anioLanzamiento, string genero, float precio, float calificacion) {
    if (buscar(isbn)) {
        cout << "Error: Libro con ISBN " << isbn << " ya existe.\n";
        return false;
    }

    NodoLibros* nuevo = new NodoLibros(titulo, autor, isbn, genero, anioLanzamiento, precio, calificacion);

    if (!cabeza) {
        cabeza = nuevo;
        cabeza->setSiguiente(cabeza);
        cabeza->setAnterior(cabeza);
    } else {
        NodoLibros* ultimo = cabeza->getAnterior();
        ultimo->setSiguiente(nuevo);
        nuevo->setAnterior(ultimo);
        nuevo->setSiguiente(cabeza);
        cabeza->setAnterior(nuevo);
    }
    guardarEnArchivoJSON(); // Usar JSON para guardar cambios
    return true;
}

NodoLibros* ListaLibros::buscar(string isbn) {
    if (!cabeza) {
        cout << "La lista de libros esta vacía.\n";
        return nullptr;
    }

    NodoLibros* actual = cabeza;
    do {
        // Depuración: Mostrar qué ISBN se compara
        //cout << "Comparando ISBN en nodo: " << actual->getIsbn() << " con " << isbn << "\n";
        if (actual->getIsbn() == isbn) {
            cout << "Libro encontrado: " << actual->getTitulo() << "\n";
            return actual;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    cout << "ISBN no encontrado: " << isbn << "\n";
    return nullptr;
}

bool ListaLibros::eliminar(string isbn) {
    // Verificar si la lista está vacía
    if (!cabeza) {
        cout << "Error: La lista de libros esta vacia.\n";
        return false;
    }

    NodoLibros* encontrado = buscar(isbn); // Buscar el nodo a eliminar
    if (!encontrado) {
        cout << "Error: Libro con ISBN " << isbn << " no encontrado.\n";
        return false;
    }

    // Caso: Único nodo en la lista
    if (encontrado->getSiguiente() == encontrado) {
        cabeza = nullptr;
    } else {
        // Caso: Múltiples nodos en la lista
        NodoLibros* anterior = encontrado->getAnterior();
        NodoLibros* siguiente = encontrado->getSiguiente();

        anterior->setSiguiente(siguiente);
        siguiente->setAnterior(anterior);

        // Actualizar la cabeza si es necesario
        if (cabeza == encontrado) {
            cabeza = siguiente;
        }
    }

    // Eliminar el nodo
    cout << "Eliminando libro: " << encontrado->getTitulo() << ", ISBN: " << encontrado->getIsbn() << "\n";
    delete encontrado;

    guardarEnArchivoJSON(); // Actualizar el archivo JSON
    return true;
}

void ListaLibros::mostrar() {
    if (!cabeza) {
        cout << "Lista de libros vacia.\n";
        return;
    }

    NodoLibros* actual = cabeza;
    cout << "Mostrando libros:\n";
    do {
        cout << "Titulo: " << actual->getTitulo()
             << ", Autor: " << actual->getAutor()
             << ", ISBN: " << actual->getIsbn()
             << ", Genero: " << actual->getGenero()
             << ", Fecha de Lanzamiento: " << actual->getAnioLanzamiento()
             << ", Precio: " << actual->getPrecio()
             << ", Calificacion: " << actual->getCalificacion() << "\n";
        actual = actual->getSiguiente();
    } while (actual != cabeza);
}

void ListaLibros::guardarEnArchivoJSON() {
    if (!cabeza) {
        cout << "La lista de libros esta vacia. Nada que guardar.\n";
        return;
    }

    json jLibros = json::array();

    NodoLibros* actual = cabeza;
    do {
        jLibros.push_back({
            {"titulo", actual->getTitulo()},
            {"autor", actual->getAutor()},
            {"isbn", actual->getIsbn()},
            {"genero", actual->getGenero()},
            {"anioLanzamiento", actual->getAnioLanzamiento()},
            {"precio", actual->getPrecio()},
            {"calificacion", actual->getCalificacion()}
        });
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    std::ofstream archivo("libros.json");
    if (archivo.is_open()) {
        archivo << jLibros.dump(4);
        archivo.close();
        //cout << "Datos guardados correctamente en 'libros.json'.\n";
    } else {
        cout << "Error: No se pudo abrir el archivo para guardar datos.\n";
    }
}

void ListaLibros::cargarDesdeArchivoJSON() {
    std::ifstream archivo("libros.json");
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo para cargar datos.\n";
        return;
    }

    json jLibros;
    archivo >> jLibros; // Leer el contenido del archivo JSON
    archivo.close();

    for (const auto& libro : jLibros) {
        // Asegurarse de que los campos coincidan con el JSON
        string titulo = libro["titulo"];
        string autor = libro["autor"];
        string isbn = libro["isbn"];
        string genero = libro["genero"];
        string anioLanzamiento = libro["anioLanzamiento"];
        float precio = libro["precio"];
        float calificacion = libro["calificacion"];

        // Depuración: Confirmar que los datos se están leyendo
        cout << "Cargando libro: Titulo: " << titulo << ", Autor: " << autor
             << ", ISBN: " << isbn << ", Género: " << genero
             << ", Fecha de Lanzamiento: " << anioLanzamiento
             << ", Precio: " << precio
             << ", Calificacion: " << calificacion << "\n";

        insertar(titulo, autor, isbn, genero, anioLanzamiento, precio, calificacion);
    }

    //cout << "Datos cargados correctamente desde 'libros.json'.\n";
}


string ListaLibros::seleccionarAutor(ListaAutores& listaAutores) {
    cout << "Seleccione un autor de la lista:\n";
    listaAutores.mostrar();

    string cedula;
    cout << "Ingrese la cedula del autor: ";
    cin >> cedula;

    NodoAutores* autor = listaAutores.buscar(cedula);
    if (autor) {
        return autor->getNombre() + " " + autor->getApellido();
    } else {
        cout << "Error: Autor no encontrado.\n";
        return "";
    }
}
void ListaLibros::crearBackup() {
    // Generar nombre con fecha y hora
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    tm localTime;
    localtime_s(&localTime, &now); // Convertir a hora local

    char buffer[64];
    strftime(buffer, sizeof(buffer), "BackupLibros/libros-%Y-%m-%d-%H-%M-%S.json", &localTime);

    // Guardar backup
    ofstream archivo(buffer);
    if (!archivo.is_open()) {
        cout << "Error: No se pudo crear el backup en la carpeta BackupLibros.\n";
        return;
    }

    json jLibros = json::array();
    NodoLibros* actual = cabeza;
    do {
        jLibros.push_back({
            {"titulo", actual->getTitulo()},
            {"autor", actual->getAutor()},
            {"isbn", actual->getIsbn()},
            {"genero", actual->getGenero()},
            {"anioLanzamiento", actual->getAnioLanzamiento()},
            {"precio", actual->getPrecio()},
            {"calificacion", actual->getCalificacion()}
        });
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    archivo << jLibros.dump(4);
    archivo.close();
    cout << "Backup creado exitosamente: " << buffer << "\n";
}

void ListaLibros::restaurarBackup(const string& nombreArchivo) {
    ifstream archivo("BackupLibros/" + nombreArchivo); // Leer desde la carpeta BackupLibros
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo de backup " << nombreArchivo << ".\n";
        return;
    }

    json jLibros;
    archivo >> jLibros;
    archivo.close();

    // Liberar memoria de la lista actual (si existe)
    if (cabeza) {
        NodoLibros* actual = cabeza;
        do {
            NodoLibros* siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        } while (actual != cabeza);
        cabeza = nullptr; // Reiniciar la cabeza
    }

    // Reconstruir la lista desde el backup
    for (const auto& libro : jLibros) {
        string titulo = libro["titulo"];
        string autor = libro["autor"];
        string isbn = libro["isbn"];
        string genero = libro["genero"];
        string anioLanzamiento = to_string(libro["anioLanzamiento"]); // Convertir int a string
        float precio = libro["precio"];
        float calificacion = libro["calificacion"];

        // Insertar nodos directamente sin mensajes
        NodoLibros* nuevo = new NodoLibros(titulo, autor, isbn, genero, anioLanzamiento, precio, calificacion);
        if (!cabeza) {
            cabeza = nuevo;
            cabeza->setSiguiente(cabeza);
            cabeza->setAnterior(cabeza);
        } else {
            NodoLibros* ultimo = cabeza->getAnterior();
            ultimo->setSiguiente(nuevo);
            nuevo->setAnterior(ultimo);
            nuevo->setSiguiente(cabeza);
            cabeza->setAnterior(nuevo);
        }
    }

    cout << "Backup restaurado correctamente desde " << nombreArchivo << ".\n";
}
