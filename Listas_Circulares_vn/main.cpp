/***********************************************************************
 * Module:  main.cpp
 * Author:  Erika Guayanay
 * Date: 25/11/2024
 * Purpose: Lista de Personas con Listas Circulares
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "ListasCirculares.h"
#include "Validaciones.h"
#include <iostream>
#include <string>
using namespace std;

void limpiarConsola() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    ListaCircular lista;
    string nombre, apellido;
    long int cedulaNumerica;
    char caracter;
    int opcion;

    do {
        limpiarConsola();
        cout << "\n*** Menu de opciones ***\n";
        cout << "1. Insertar persona\n";
        cout << "2. Buscar persona\n";
        cout << "3. Eliminar persona\n";
        cout << "4. Mostrar lista\n";
        cout << "5. Eliminar caracter\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                // Validación de cédula en bucle
                bool cedulaValida = false;
                do {
                    cout << "Ingrese su cedula: ";
                    string cedulaInput;
                    cin >> cedulaInput;

                    // Validar que sea numérica y tenga 10 dígitos
                    if (cedulaInput.length() == 10 && validarCedula(cedulaInput)) {
                        cedulaNumerica = stol(cedulaInput); // Convertir a número
                        if (validarCedulaReal(cedulaNumerica)) {
                            imprimirResultadoCedula(true);
                            cedulaValida = true;
                        } else {
                            imprimirResultadoCedula(false);
                        }
                    } else {
                        cout << "Cedula invalida. Asegurese de que tenga 10 digitos numericos.\n";
                    }
                } while (!cedulaValida);

                // Validación de nombre en bucle
                bool nombreValido = false;
                do {
                    cout << "Ingrese nombre: ";
                    cin >> nombre;
                    if (validarSoloLetras(nombre)) {
                        nombreValido = true;
                    } else {
                        cout << "Error: El nombre debe contener solo letras. Intente nuevamente.\n";
                    }
                } while (!nombreValido);

                // Validación de apellido en bucle
                bool apellidoValido = false;
                do {
                    cout << "Ingrese apellido: ";
                    cin >> apellido;
                    if (validarSoloLetras(apellido)) {
                        apellidoValido = true;
                    } else {
                        cout << "Error: El apellido debe contener solo letras. Intente nuevamente.\n";
                    }
                } while (!apellidoValido);

                // Inserción en la lista
                lista.insertar(to_string(cedulaNumerica), nombre, apellido);
                cout << "Persona insertada exitosamente.\n";
                break;
            }

            case 2:
                cout << "Ingrese cédula a buscar: ";
                cin >> cedulaNumerica;
                if (lista.buscar(to_string(cedulaNumerica)) != nullptr) {
                    Nodo* encontrado = lista.buscar(to_string(cedulaNumerica));
                    cout << "Persona encontrada: <Cédula: " << encontrado->getCedula()
                         << ", Nombre: " << encontrado->getNombre()
                         << ", Apellido: " << encontrado->getApellido() << ">\n";
                } else {
                    cout << "Persona no encontrada.\n";
                }
                break;

            case 3:
                cout << "Ingrese cedula a eliminar: ";
                cin >> cedulaNumerica;
                if (lista.eliminar(to_string(cedulaNumerica))) {
                    cout << "Persona eliminada correctamente.\n";
                } else {
                    cout << "Error: Persona no encontrada.\n";
                }
                break;

            case 4:
                cout << "\nLista de personas:\n";
                lista.mostrar();
                break;

            case 5:
                cout << "Ingrese cedula de la persona: ";
                cin >> cedulaNumerica;
                cout << "Ingrese caracter a eliminar: ";
                cin >> caracter;
                lista.eliminarCaracter(to_string(cedulaNumerica), caracter);
                break;

            case 6:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opción no válida. Por favor, seleccione una opción del menú.\n";
        }

        if (opcion != 6) {
            cout << "\nPresione cualquier tecla para regresar al menu...\n";
            system("pause");
        }
    } while (opcion != 6);

    return 0;
}

