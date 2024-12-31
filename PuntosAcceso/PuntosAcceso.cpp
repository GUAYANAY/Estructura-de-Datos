#include "PuntosAcceso.h"
#include <algorithm>
#include <cmath>

bool esValido(int r, const std::vector<int>& usuarios, const std::vector<int>& routers) {
    int j = 0;
    for (int i = 0; i < usuarios.size(); ++i) {
        while (j < routers.size() && std::abs(routers[j] - usuarios[i]) > r) {
            ++j;
        }
        if (j == routers.size()) {
            return false;
        }
    }
    return true;
}

int encontrarRMinimo(const std::vector<int>& usuarios, const std::vector<int>& routers) {
    int izquierda = 0, derecha = 2000;
    while (izquierda < derecha) {
        int medio = (izquierda + derecha) / 2;
        if (esValido(medio, usuarios, routers)) {
            derecha = medio;
        } else {
            izquierda = medio + 1;
        }
    }
    return izquierda;
}
