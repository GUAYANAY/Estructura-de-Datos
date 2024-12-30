#include "BusquedaBinaria.h"
#include <algorithm>

using namespace std;

bool BusquedaBinaria::puedeColocarVacas(const vector<pair<long long, long long>>& intervalos, int N, long long D) {
    int vacasColocadas = 0;
    long long ultimaPosicion = -D;

    for (const auto& intervalo : intervalos) {
        long long inicio = max(intervalo.first, ultimaPosicion + D);
        while (inicio <= intervalo.second) {
            vacasColocadas++;
            if (vacasColocadas == N) return true;
            inicio += D;
        }
        ultimaPosicion = inicio - D;
    }
    return false;
}

long long BusquedaBinaria::encontrarMaximaDistancia(const vector<pair<long long, long long>>& intervalos, int N) {
    long long izquierda = 1, derecha = 1e18, respuesta = 1;
    while (izquierda <= derecha) {
        long long medio = izquierda + (derecha - izquierda) / 2;
        if (puedeColocarVacas(intervalos, N, medio)) {
            respuesta = medio;
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }
    return respuesta;
}
