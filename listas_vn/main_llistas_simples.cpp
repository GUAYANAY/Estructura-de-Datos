#include "Lista_Simple.h"
#include "Validaciones.h"
#include <iostream>
using namespace std;

int main() {
    ListaSimple listaPrincipal;
    ListaSimple listaAuxiliar;
    string cedula, nombre, apellido;
    char caracter;
    int opcion;

    do {
        cout << "\n** Men� de opciones **\n";
        cout << "1. Insertar persona\n";
        cout << "2. Buscar persona\n";
        cout << "3. Eliminar persona\n";
        cout << "4. Mostrar lista\n";
        cout << "5. Eliminar caracter\n";
        cout << "6. Mostrar lista auxiliar\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese c�dula: ";
                cin >> cedula;
                if (!validarCedula(cedula)) {
                    cout << "Error: La c�dula debe contener 10 n�meros.\n";
                    break;
                }
                cout << "Ingrese nombre: ";
                cin >> nombre;
                if (!validarSoloLetras(nombre)) {
                    cout << "Error: El nombre debe contener solo letras.\n";
                    break;
                }
                cout << "Ingrese apellido: ";
                cin >> apellido;
                if (!validarSoloLetras(apellido)) {
                    cout << "Error: El apellido debe contener solo letras.\n";
                    break;
                }
                listaPrincipal.insertarACola(cedula, nombre, apellido);
                break;

            case 2:
                cout << "Ingrese c�dula a buscar: ";
                cin >> cedula;
                if (listaPrincipal.buscar(cedula) != nullptr) {
                    cout << "Persona encontrada.\n";
                } else {
                    cout << "Persona no encontrada.\n";
                }
                break;

            case 3:
                cout << "Ingrese c�dula a eliminar: ";
                cin >> cedula;
                listaPrincipal.eliminar(cedula);
                break;

            case 4:
                listaPrincipal.mostrar();
                break;

            case 5:
                cout << "Ingrese c�dula: ";
                cin >> cedula;
                cout << "Ingrese car�cter a eliminar: ";
                cin >> caracter;
                listaPrincipal.eliminarCaracter(cedula, caracter, listaAuxiliar);
                break;

            case 6:
                listaAuxiliar.mostrar();
                break;

            case 7:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opci�n inv�lida.\n";
        }
    } while (opcion != 7);

    return 0;
}
