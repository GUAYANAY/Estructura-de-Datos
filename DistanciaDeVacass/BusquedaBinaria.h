#ifndef BUSQUEDABINARIA_H
#define BUSQUEDABINARIA_H

#include <vector>
#include <utility>

class BusquedaBinaria {
public:
    long long encontrarMaximaDistancia(const std::vector<std::pair<long long, long long>>& intervalos, int N);
private:
    bool puedeColocarVacas(const std::vector<std::pair<long long, long long>>& intervalos, int N, long long D);
};

#endif // BUSQUEDABINARIA_H
