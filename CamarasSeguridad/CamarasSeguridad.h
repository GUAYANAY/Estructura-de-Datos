#ifndef CAMARAS_SEGURIDAD_H
#define CAMARAS_SEGURIDAD_H

#include <vector>

class CamarasSeguridad {
public:
    int calcularRangoMinimo(const std::vector<int>& locations, const std::vector<int>& cameras);
};

#endif // CAMARAS_SEGURIDAD_H
