#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <list>
using namespace std;

const int filas = 20;
const int columnas = 10;

void cambiarColor(int color);
bool hayEspacioVacioEnFila(char **tablero, int fila);
void aplicarGravedadInvertida(char **tablero);
void colapsarFila(int fila, char **tablero);
void dfsEliminar(int r, int c, char numero, char **tablero, bool **visitado, list<pair<int,int>> &grupo);
void eliminarGrupos(char **tablero, bool **visitado);

#endif // FUNCIONES_H
