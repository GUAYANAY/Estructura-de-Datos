#include "SuministroAgua.h"
#include <algorithm>
#include <cmath>

SuministroAgua::SuministroAgua(const std::vector<int>& casas, const std::vector<int>& fuentes)
    : casas(casas), fuentes(fuentes) {}

int SuministroAgua::calcularRadioMinimo() {
    int izquierda = 0;
    int derecha = 200; // Max distance between -100 and 100
    while (izquierda < derecha) {
        int medio = (izquierda + derecha) / 2;
        if (todasCasasCubiertas(medio)) {
            derecha = medio;
        } else {
            izquierda = medio + 1;
        }
    }
    return izquierda;
}

bool SuministroAgua::todasCasasCubiertas(int radio) {
    int j = 0;
    for (int casa : casas) {
        while (j < fuentes.size() && std::abs(fuentes[j] - casa) > radio) {
            ++j;
        }
        if (j == fuentes.size()) {
            return false;
        }
    }
    return true;
}
