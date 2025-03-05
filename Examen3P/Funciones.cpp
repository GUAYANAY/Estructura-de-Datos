#include <iostream>
#include <windows.h>
#include "Funciones.h"

using namespace std;

void cambiarColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

bool hayEspacioVacioEnFila(char **tablero, int fila) {
    for (int j = 0; j < columnas; j++) {
        if (tablero[fila][j] == ' ') {
            return true;
        }
    }
    return false;
}

void aplicarGravedadInvertida(char **tablero) {
    for (int j = 0; j < columnas; j++) {
        for (int i = filas - 1; i > 0; i--) {
            if (tablero[i][j] == ' ' && tablero[i - 1][j] != ' ') {
                tablero[i][j] = tablero[i - 1][j];
                tablero[i - 1][j] = ' ';
            }
        }
    }
}

void colapsarFila(int fila, char **tablero) {
    if (fila != filas - 1)
        return;
    char *temporal = new char[columnas];
    int indice = 0;
    for (int j = 0; j < columnas; j++) {
        if (tablero[fila][j] != ' ') {
            temporal[indice++] = tablero[fila][j];
        }
    }
    for (int j = 0; j < indice; j++) {
        tablero[fila][j] = temporal[j];
    }
    for (int j = indice; j < columnas; j++) {
        tablero[fila][j] = ' ';
    }
    delete[] temporal;
}

void dfsEliminar(int r, int c, char numero, char **tablero, bool **visitado, list<pair<int,int>> &grupo) {
    if (r < 0 || r >= filas || c < 0 || c >= columnas) return;
    if (visitado[r][c] || tablero[r][c] != numero) return;
    visitado[r][c] = true;
    grupo.push_back({r, c});
    // Vecinos: arriba, abajo, izquierda y derecha
    dfsEliminar(r - 1, c, numero, tablero, visitado, grupo);
    dfsEliminar(r + 1, c, numero, tablero, visitado, grupo);
    dfsEliminar(r, c - 1, numero, tablero, visitado, grupo);
    dfsEliminar(r, c + 1, numero, tablero, visitado, grupo);
}

void eliminarGrupos(char **tablero, bool **visitado) {
    // Reiniciar matriz de visitados
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            visitado[i][j] = false;
    // Recorrer cada celda
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (tablero[i][j] != ' ' && !visitado[i][j]) {
                list<pair<int,int>> grupo;
                dfsEliminar(i, j, tablero[i][j], tablero, visitado, grupo);
                // Si hay grupo (2 o más números conectados)
                if (grupo.size() >= 2) {
                    for (auto &p : grupo) {
                        tablero[p.first][p.second] = ' ';
                    }
                    if (i == filas - 1)
                        colapsarFila(i, tablero);
                }
            }
        }
    }
}
