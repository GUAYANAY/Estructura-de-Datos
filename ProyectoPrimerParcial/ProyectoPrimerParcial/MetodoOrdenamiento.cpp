
#include "MetodoOrdenamiento.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

void MetodoOrdenamientoExterno::distribuirDatos(const string& archivoEntrada, vector<string>& archivosSalida) {
    ifstream archivo(archivoEntrada);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de entrada.\n";
        return;
    }

    // Crear archivos de salida para las 26 letras
    vector<ofstream> cubetas(26);
    for (int i = 0; i < 26; ++i) {
        string nombreArchivo = "cubeta_" + string(1, 'A' + i) + ".txt";
        cubetas[i].open(nombreArchivo);
        archivosSalida.push_back(nombreArchivo);
    }

    string linea;
    while (getline(archivo, linea)) {
        // Dividir la l�nea en columnas: cedula, nombre, apellido
        stringstream ss(linea);
        string cedula, nombre, apellido;

        getline(ss, cedula, ',');
        getline(ss, nombre, ',');
        getline(ss, apellido);

        // Usar la primera letra del nombre para determinar la cubeta
        if (!nombre.empty()) {
            char letra = tolower(nombre[0]);
            int indice = letra - 'a';
            if (indice >= 0 && indice < 26) {
                cubetas[indice] << linea << "\n";
            }
        }
    }

    archivo.close();

    // Cerrar todos los archivos de salida
    for (auto& cubeta : cubetas) {
        cubeta.close();
    }

    cout << "Datos distribuidos correctamente en las cubetas.\n";
}

void MetodoOrdenamientoExterno::ordenarArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo " << nombreArchivo << " para lectura.\n";
        return;
    }

    vector<string> datos;
    string linea;
    while (getline(archivo, linea)) {
        datos.push_back(linea);
    }
    archivo.close();

    // Función de comparación personalizada para ordenar por nombre del autor
    sort(datos.begin(), datos.end(), [](const string& a, const string& b) {
        stringstream ssA(a), ssB(b);
        string tituloA, nombreAutorA, isniA, fechaNacAutorA, isbnA, fechaPubA;
        string tituloB, nombreAutorB, isniB, fechaNacAutorB, isbnB, fechaPubB;

        // Extraer los datos de la línea para ambos registros
        getline(ssA, tituloA, ';');
        getline(ssA, nombreAutorA, ';');
        getline(ssA, isniA, ';');
        getline(ssA, fechaNacAutorA, ';');
        getline(ssA, isbnA, ';');
        getline(ssA, fechaPubA, ';');

        getline(ssB, tituloB, ';');
        getline(ssB, nombreAutorB, ';');
        getline(ssB, isniB, ';');
        getline(ssB, fechaNacAutorB, ';');
        getline(ssB, isbnB, ';');
        getline(ssB, fechaPubB, ';');

        // Comparar por nombre del autor
        return nombreAutorA < nombreAutorB;
    });

    ofstream archivoSalida(nombreArchivo);
    for (const auto& dato : datos) {
        archivoSalida << dato << "\n";
    }
    archivoSalida.close();
}


void MetodoOrdenamientoExterno::fusionarArchivos(const vector<string>& archivosCubetas, const string& archivoFinal) {
    ofstream archivoSalida(archivoFinal);
    if (!archivoSalida.is_open()) {
        cout << "Error al abrir el archivo de salida.\n";
        return;
    }

    for (const auto& archivoCubeta : archivosCubetas) {
        ifstream archivo(archivoCubeta);
        string linea;
        while (getline(archivo, linea)) {
            archivoSalida << linea << "\n";
        }
        archivo.close();
    }

    archivoSalida.close();
    cout << "Archivos fusionados en " << archivoFinal << ".\n";
}

void MetodoOrdenamientoExterno::mostrarArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    while (getline(archivo, linea)) {
        cout << linea << endl;
    }

    archivo.close();
}