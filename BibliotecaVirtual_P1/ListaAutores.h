#pragma once
#include "NodoAutores.h"
#include <string>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class ListaAutores {
private:
    NodoAutores* cabeza;

public:
    ListaAutores();
    ~ListaAutores();

    bool validarCedulaUnica(string cedula);

    bool insertar(string cedula, string nombre, string apellido, string fechaPublicacion);
    NodoAutores* buscar(string cedula);
    bool eliminar(string cedula);
    void mostrar();

    // Nuevas funciones para JSON
    void cargarDesdeArchivoJSON(); // Cargar datos desde un archivo JSON
    void guardarEnArchivoJSON();   // Guardar datos en un archivo JSON
};
