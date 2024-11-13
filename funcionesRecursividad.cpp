/*
Programa: Funciones de Recursividad
Autor: Erika Vannesa Guayanay Lema
Fecha:13/11/2024
***************UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"****************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

// Recursividad simple
void recursividadSimple(int n) {
    if (n <= 0) return;
    cout << "Recursividad Simple: " << n << endl;
    recursividadSimple(n - 1); // Llamada a sí misma
}

// Recursividad de cola (tail recursion)
void recursividadDeCola(int n) {
    if (n <= 0) return;
    cout << "Recursividad de Cola: " << n << endl;
    recursividadDeCola(n - 1); // Llamada recursiva al final de la función
}

// Recursividad de no cola (non-tail recursion)
int recursividadNoDeCola(int n) {
    if (n <= 0) return 0;
    int result = n + recursividadNoDeCola(n - 1); // Operación después de la llamada recursiva
    cout << "Recursividad No de Cola: " << result << endl;
    return result;
}

// Recursividad mutua (mutual recursion)
void funcionX(int n); // Declaración adelantada para funcionX
void funcionY(int n); // Declaración adelantada para funcionY

void funcionX(int n) {
    if (n <= 0) return;
    cout << "Funcion X: " << n << endl;
    funcionY(n - 1); // Llama a funcionY
}

void funcionY(int n) {
    if (n <= 0) return;
    cout << "Funcion Y: " << n << endl;
    funcionX(n - 1); // Llama a funcionX, generando recursión mutua
}

// Recursividad anidada (nested recursion)
int recursividadAnidada(int n) {
    if (n > 100) return n - 10;
    return recursividadAnidada(recursividadAnidada(n + 11)); // Llamada anidada
}

// Recursividad múltiple (multiple recursion)
int recursividadMultiple(int n) {
    if (n <= 1) return n;
    int result = recursividadMultiple(n - 1) + recursividadMultiple(n - 2); // Llamada múltiple
    cout << "Recursividad Múltiple: " << result << endl;
    return result;
}

// Recursividad indirecta (indirect recursion)
void recursividadIndirectaA(int n); // Declaración adelantada para B
void recursividadIndirectaB(int n);

void recursividadIndirectaA(int n) {
    if (n <= 0) return;
    cout << "Recursividad Indirecta A: " << n << endl;
    recursividadIndirectaB(n - 1); // Llama a B
}

void recursividadIndirectaB(int n) {
    if (n <= 0) return;
    cout << "Recursividad Indirecta B: " << n << endl;
    recursividadIndirectaA(n - 1); // Llama a A
}

int main() {
    int n = 5;

    // Llamadas a las funciones de cada tipo de recursividad
    recursividadSimple(n);
    cout << endl;

    recursividadDeCola(n);
    cout << endl;

    recursividadNoDeCola(n);
    cout << endl;

    funcionX(n); // Llamada inicial de la recursión mutua
    cout << endl;

    cout << "Recursividad Anidada: " << recursividadAnidada(95) << endl;
    cout << endl;

    recursividadMultiple(n);
    cout << endl;

    recursividadIndirectaA(n); // Llamada inicial de la recursión indirecta
    cout << endl;

    return 0;
}
