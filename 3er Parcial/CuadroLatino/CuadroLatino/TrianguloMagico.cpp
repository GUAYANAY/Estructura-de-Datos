#include "TrianguloMagico.h"
#include <stdexcept> // Necesario para std::invalid_argument
#include <cstdlib>   // Necesario para rand() y srand()
#include <ctime>     // Necesario para time()
#include <algorithm> // Necesario para std::shuffle
#include <numeric>   // Necesario para std::accumulate

TrianguloMagico::TrianguloMagico(int size) : n(size) {
    try {
        matriz.resize(n);
        for (int i = 0; i < n; ++i) {
            matriz[i].resize(i + 1, 0);
        }
        srand(time(0)); // Inicializar la semilla para números aleatorios
    } catch (const std::exception& e) {
        throw std::runtime_error("Error al inicializar la matriz: " + std::string(e.what()));
    }
}

void TrianguloMagico::generar() {
    try {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= i; ++j) {
                matriz[i][j] = rand() % 10 + 1; // Generar números aleatorios entre 1 y 10
            }
        }
        ajustarLados(); // Ajustar los lados para que la suma sea la misma
    } catch (const std::exception& e) {
        throw std::runtime_error("Error al generar el triángulo mágico: " + std::string(e.what()));
    }
}

void TrianguloMagico::ajustarLados() {
    int sumaLado = 0;
    for (int i = 0; i < n; ++i) {
        sumaLado += matriz[n-1][i]; // Sumar los números de la base del triángulo
    }

    // Ajustar los números en los lados izquierdo y derecho para que la suma sea igual a sumaLado
    int sumaActualIzquierda = 0;
    int sumaActualDerecha = 0;
    for (int i = 0; i < n; ++i) {
        sumaActualIzquierda += matriz[i][0];
        sumaActualDerecha += matriz[i][i];
    }

    int ajusteIzquierda = sumaLado - sumaActualIzquierda;
    int ajusteDerecha = sumaLado - sumaActualDerecha;

    // Distribuir el ajuste de manera uniforme
    for (int i = 0; i < n; ++i) {
        matriz[i][0] += ajusteIzquierda / n;
        matriz[i][i] += ajusteDerecha / n;
    }

    // Ajustar el último elemento si es necesario
    matriz[0][0] += ajusteIzquierda % n;
    matriz[n-1][n-1] += ajusteDerecha % n;
}

std::vector<std::vector<int>> TrianguloMagico::getMatriz() const {
    return matriz;
}
