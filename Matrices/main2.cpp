#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 3
/*
Suma de matrices recursiva usando plantillas
*/

using namespace std;

// Declaración de la plantilla para la función de suma recursiva
template <typename T>
T sumaRecursivaMatrices(T[MAX][MAX], T[MAX][MAX], int, int);

// Implementación de la función de suma recursiva
template <typename T>
T sumaRecursivaMatrices(T mat1[MAX][MAX], T mat2[MAX][MAX], int f, int c) {
    if ((f == 0) && (c == 0))
        return mat1[f][c] + mat2[f][c];
    else {
        if (f > -1) {
            c--;
            if (c >= -1)
                return mat1[f][c + 1] + mat2[f][c + 1] + sumaRecursivaMatrices(mat1, mat2, f, c);
            else
                return sumaRecursivaMatrices(mat1, mat2, f - 1, MAX - 1);
        }
    }
    return 0; // Valor de retorno por defecto
}

int main(int argc, char** argv) {
    int mat1[MAX][MAX], mat2[MAX][MAX];
    srand(time(NULL));
    
    // Inicialización de matrices con valores aleatorios
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            mat1[i][j] = (int)((rand() / 32768.1) * 1000);
            mat2[i][j] = (int)((rand() / 32768.1) * 1000);
        }
    }
    
    // Impresión de la primera matriz
    cout << "Matriz 1:" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cout << mat1[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    
    // Impresión de la segunda matriz
    cout << "Matriz 2:" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cout << mat2[i][j] << "\t";
        }
        cout << endl;
    }
    
    // Llamada a la función de suma recursiva y salida del resultado
    cout << "Suma de Matrices es: " << sumaRecursivaMatrices(mat1, mat2, MAX - 1, MAX - 1) << endl;
    return 0;
}

