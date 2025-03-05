#include <iostream>
#include <conio.h>
#include <windows.h>
#include <list>
#include <cstdlib>
#include <ctime>
#include "Juego.h"
#include "Funciones.h"

using namespace std;

int main() {
    // Inicializar tablero con espacios
    char **tablero = new char*[filas];
    for (int i = 0; i < filas; i++) {
        tablero[i] = new char[columnas];
        for (int j = 0; j < columnas; j++) {
            tablero[i][j] = ' ';
        }
    }

    // Matriz de celdas visitadas
    bool **visitado = new bool*[filas];
    for (int i = 0; i < filas; i++) {
        visitado[i] = new bool[columnas];
        for (int j = 0; j < columnas; j++) {
            visitado[i][j] = false;
        }
    }

    // Lista para números en caída
    list<NumeroCaida> numerosCaidos;
    srand(static_cast<unsigned int>(time(0)));

    // Lambda para imprimir el tablero
    auto imprimirTablero = [&]() {
        char **temp = new char*[filas];
        for (int i = 0; i < filas; i++) {
            temp[i] = new char[columnas];
            for (int j = 0; j < columnas; j++)
                temp[i][j] = tablero[i][j];
        }
        // Superponer números en caída
        for (auto &nc : numerosCaidos) {
            if (nc.fila >= 0 && nc.fila < filas && nc.columna >= 0 && nc.columna < columnas)
                temp[nc.fila][nc.columna] = nc.numero;
        }
        system("cls");
        // Borde superior
        cout << ".";
        for (int j = 0; j < columnas; j++)
            cout << ".";
        cout << "." << endl;
        // Filas del tablero con bordes laterales
        for (int i = 0; i < filas; i++) {
            cout << ".";
            for (int j = 0; j < columnas; j++) {
                if (temp[i][j] != ' ') {
                    cambiarColor(11); // Color azul
                    cout << temp[i][j];
                    cambiarColor(7); // Color blanco
                } else {
                    cout << temp[i][j];
                }
            }
            cout << "." << endl;
        }
        // Borde inferior
        cout << ".";
        for (int j = 0; j < columnas; j++)
            cout << ".";
        cout << "." << endl;

        // Liberar memoria temporal
        for (int i = 0; i < filas; i++) {
            delete[] temp[i];
        }
        delete[] temp;
    };

    // Bucle principal del juego
    while (true) {
        // Generar nuevo número en caída si no hay ninguno
        if (numerosCaidos.empty()) {
            NumeroCaida nuevo;
            nuevo.fila = 0;  // Parte superior
            nuevo.columna = rand() % columnas;
            // Verificar que la posición esté libre
            if (tablero[nuevo.fila][nuevo.columna] == ' ') {
                nuevo.numero = '0' + rand() % 10;
                numerosCaidos.push_back(nuevo);
            }
        }
        
        // Procesar entrada de usuario para mover el número en caída
        if (_kbhit()) {
            int ch = _getch();
            // Las flechas en Windows inician con 224
            if (ch == 224) {
                int flecha = _getch();
                if (!numerosCaidos.empty()) {
                    NumeroCaida &nc = numerosCaidos.front();
                    // Movimiento lateral sin fusión
                    if (flecha == 75 && nc.columna > 0 && tablero[nc.fila][nc.columna - 1] == ' ')
                        nc.columna--;
                    else if (flecha == 77 && nc.columna < columnas - 1 && tablero[nc.fila][nc.columna + 1] == ' ')
                        nc.columna++;
                }
            }
        }

        // Actualizar posición del número en caída
        if (!numerosCaidos.empty()) {
            NumeroCaida nc = numerosCaidos.front();
            if (nc.fila < filas - 1) {
                // Fusión si la celda inferior contiene el mismo número
                if (tablero[nc.fila + 1][nc.columna] == nc.numero) {
                    tablero[nc.fila + 1][nc.columna] = ' ';
                    numerosCaidos.pop_front();
                } else if (tablero[nc.fila + 1][nc.columna] == ' ') {
                    nc.fila++;
                    numerosCaidos.front() = nc;
                } else {
                    // Fijar número si la celda inferior está ocupada
                    tablero[nc.fila][nc.columna] = nc.numero;
                    numerosCaidos.pop_front();
                }
            } else {
                // Fijar número si ya está en la última fila
                tablero[nc.fila][nc.columna] = nc.numero;
                numerosCaidos.pop_front();
            }
        }

        // Desplazar números fijos en la última fila hacia la izquierda
        for (int j = 1; j < columnas; j++) {
            if (tablero[filas - 1][j] != ' ' && tablero[filas - 1][j - 1] == ' ') {
                for (int i = filas - 1; i >= 0; i--) {
                    if (tablero[i][j] != ' ') {
                        tablero[i][j - 1] = tablero[i][j];
                        tablero[i][j] = ' ';
                    }
                }
            }
        }

        // Desplazar todos los números en la primera fila hacia la izquierda
        for (int j = 1; j < columnas; j++) {
            if (tablero[0][j] != ' ' && tablero[0][j - 1] == ' ') {
                tablero[0][j - 1] = tablero[0][j];
                tablero[0][j] = ' ';
            }
        }

        // Aplicar gravedad invertida para las filas
        aplicarGravedadInvertida(tablero);

        eliminarGrupos(tablero, visitado);
        imprimirTablero();
        Sleep(200); // Pausa para visualizar el proceso
    }

    // Liberar memoria del tablero y visitado
    for (int i = 0; i < filas; i++) {
        delete[] tablero[i];
        delete[] visitado[i];
    }
    delete[] tablero;
    delete[] visitado;

    return 0;
}

