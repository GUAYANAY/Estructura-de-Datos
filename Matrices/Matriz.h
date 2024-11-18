#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#define MAX 3 // Tamaño de las matrices

using namespace std;

template <typename T>
class Matriz {
public:
    Matriz(); // Constructor para inicializar la matriz
    void inicializarAleatorio(); // Inicializar la matriz con valores aleatorios
    void imprimir() const; // Imprimir la matriz
    static T sumarRecursivo(const T mat1[MAX][MAX], const T mat2[MAX][MAX], int f, int c); // Suma recursiva

    T datos[MAX][MAX]; // Arreglo estático para almacenar los datos
};

#endif
