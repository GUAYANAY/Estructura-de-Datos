#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <vector>
#include <string>

class Validaciones {
public:
    static void validarEntradas(int n, int m, const std::vector<int>& casas, const std::vector<int>& fuentes);
    static bool validarRango(int n, int m);
    static bool esNumero(const std::string& str);
    static std::string capturarEntrada();
    static void capturarYValidarEntradas(int& n, int& m, std::vector<int>& casas, std::vector<int>& fuentes);
};

#endif // VALIDACIONES_H
