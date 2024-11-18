#include "Matriz.h"
#include <stdlib.h>
#include <time.h>

// Constructor
template <typename T>
Matriz<T>::Matriz() {
    // Inicializar la matriz con ceros (opcional)
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            datos[i][j] = 0;
        }
    }
}

// Inicializar con valores aleatorios
template <typename T>
void Matriz<T>::inicializarAleatorio() {
    srand(time(NULL));
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            datos[i][j] = (T)((rand() % 1000) + 1); // Valores entre 1 y 1000
        }
    }
}

// Imprimir matriz
template <typename T>
void Matriz<T>::imprimir() const {
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            cout << datos[i][j] << "\t";
        }
        cout << endl;
    }
}

// Suma recursiva de matrices
template <typename T>
T Matriz<T>::sumarRecursivo(const T mat1[MAX][MAX], const T mat2[MAX][MAX], int f, int c) {
    if (f == 0 && c == 0)
        return mat1[f][c] + mat2[f][c];
    if (c == 0)
        return mat1[f][c] + mat2[f][c] + sumarRecursivo(mat1, mat2, f - 1, MAX - 1);
    return mat1[f][c] + mat2[f][c] + sumarRecursivo(mat1, mat2, f, c - 1);
}

// Necesario para evitar errores de linking con plantillas
template class Matriz<int>;
template class Matriz<float>;
template class Matriz<double>;
