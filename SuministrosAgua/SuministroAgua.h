#ifndef SUMINISTROAGUA_H
#define SUMINISTROAGUA_H

#include <vector>

class SuministroAgua {
public:
    SuministroAgua(const std::vector<int>& casas, const std::vector<int>& fuentes);
    int calcularRadioMinimo();

private:
    std::vector<int> casas;
    std::vector<int> fuentes;
    bool todasCasasCubiertas(int radio);
};

#endif // SUMINISTROAGUA_H
