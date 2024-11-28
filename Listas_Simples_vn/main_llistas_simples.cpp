#include "Lista_Simple.h"
#include "Validaciones.h"
#include <iostream>
#include <cstdlib> // Para system("cls") o system("clear")
using namespace std;

// Función para limpiar la consola
void limpiarConsola() {
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Linux/Mac
#endif
}

// Función para pausar la consola
void pausa() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

int main() {
    ListaSimple listaPrincipal;
    ListaSimple listaAuxiliar;
    string cedula, nombre, apellido;
    int desplazar;
    char caracter;
    int opcion;

    do {
        limpiarConsola();
        cout << "** Menu de opciones **\n";
        cout << "1. Insertar persona\n";
        cout << "2. Buscar persona\n";
        cout << "3. Eliminar persona\n";
        cout << "4. Mostrar lista\n";
        cout << "5. Eliminar caracter de nombre\n";
        cout << "6. Cifrar un caracter\n";
        cout << "7. Mostrar lista auxiliar\n";
        cout << "8. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        limpiarConsola();
        switch (opcion) {
            case 1: { // Insertar persona
                do {
                    cout << "Ingrese cedula: ";
                    cin >> cedula;
                    if (!validarCedulaReal(cedula)) {
                        cout << "Cedula invalida. Intente de nuevo.\n";
                    } else if (!validarCedulaUnica(cedula)) {
                        cout << "La cedula ya esta registrada. Intente de nuevo.\n";
                    } else {
                        break;
                    }
                } while (true);

                do {
                    cout << "Ingrese nombre: ";
                    cin >> nombre;
                    if (!validarSoloLetras(nombre)) {
                        cout << "Error: El nombre debe contener solo letras. Intente nuevamente.\n";
                    }
                } while (!validarSoloLetras(nombre));

                do {
                    cout << "Ingrese apellido: ";
                    cin >> apellido;
                    if (!validarSoloLetras(apellido)) {
                        cout << "Error: El apellido debe contener solo letras. Intente nuevamente.\n";
                    }
                } while (!validarSoloLetras(apellido));

                listaPrincipal.insertarACola(cedula, nombre, apellido);
                registrarCedula(cedula); // Registrar cédula en el conjunto
                cout << "Persona registrada exitosamente.\n";
                pausa();
                break;
            }

            case 2: { // Buscar persona
                do {
                    cout << "Ingrese cedula a buscar: ";
                    cin >> cedula;
                    if (!validarCedulaReal(cedula)) {
                        cout << "Cedula invalida. Intente de nuevo.\n";
                    } else {
                        break;
                    }
                } while (true);

                if (!existeCedula(cedula)) {
                    cout << "Error: La cedula no existe.\n";
                } else if (listaPrincipal.buscar(cedula) != nullptr) {
                    cout << "Persona encontrada.\n";
                } else {
                    cout << "Error: Persona no encontrada.\n";
                }
                pausa();
                break;
            }

            case 3: { // Eliminar persona
                do {
                    cout << "Ingrese cedula a eliminar: ";
                    cin >> cedula;
                    if (!validarCedulaReal(cedula)) {
                        cout << "Cedula invalida. Intente de nuevo.\n";
                    } else {
                        break;
                    }
                } while (true);

                if (!existeCedula(cedula)) {
                    cout << "Error: La cedula no existe.\n";
                } else {
                    listaPrincipal.eliminar(cedula);
                    eliminarCedula(cedula); // Eliminar cédula del conjunto
                    cout << "Persona eliminada exitosamente.\n";
                }
                pausa();
                break;
            }

            case 4: { // Mostrar lista principal
                listaPrincipal.mostrar();
                pausa();
                break;
            }

            case 5: { // Eliminar carácter de nombre
                do {
                    cout << "Ingrese cedula: ";
                    cin >> cedula;
                    if (!validarCedulaReal(cedula)) {
                        cout << "Cedula inválida. Intente de nuevo.\n";
                    } else {
                        break;
                    }
                } while (true);

                if (!existeCedula(cedula)) {
                    cout << "Error: La cedula no existe.\n";
                } else {
                    cout << "Ingrese caracter a eliminar: ";
                    cin >> caracter;
                    listaPrincipal.eliminarCaracter(cedula, caracter, listaAuxiliar);
                }
                pausa();
                break;
            }
            case 6:{//cifrar caracter
                do {
                    cout << "Ingrese cedula: ";
                    cin >> cedula;
                    if (!validarCedulaReal(cedula)) {
                        cout << "Cedula inválida. Intente de nuevo.\n";
                    } else {
                        break;
                    }
                } while (true);

                if (!existeCedula(cedula)) {
                    cout << "Error: La cedula no existe.\n";
                } else {
                    cout << "Ingrese caracter a crifrar: ";
                    cin >> caracter;

                    cout<< "Ingrese el desplazamieno: ";
                    cin>>desplazar;
                    listaPrincipal.cifrarCaracter(cedula,caracter,desplazar, listaAuxiliar);
                }
                pausa();
                break;

            }

            case 7: { // Mostrar lista auxiliar
                listaAuxiliar.mostrar();
                pausa();
                break;
            }

            case 8: { // Salir
                cout << "Saliendo...\n";
                pausa();
                break;
            }

            default: {
                cout << "Opción invalida. Intente de nuevo.\n";
                pausa();
                break;
            }
        }
    } while (opcion != 7);

    return 0;
}
