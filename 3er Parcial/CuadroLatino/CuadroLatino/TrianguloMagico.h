#ifndef TRIANGULOMAGICO_H
#define TRIANGULOMAGICO_H

#include <vector>

class TrianguloMagico {
private:
    int n;
    std::vector<std::vector<int>> matriz;
    void ajustarLados();

public:
    TrianguloMagico(int size);
    void generar();
    std::vector<std::vector<int>> getMatriz() const;
};

#endif
