#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <vector>
#include <string>

class Validaciones {
public:
    static bool validarEntradas(int n, int m, const std::vector<int>& usuarios, const std::vector<int>& routers);
    static bool isValidInput();
    static bool isNumber(char c);
    static bool esNumero(const std::string& str);
    static std::string capturarEntrada();
    static bool validarFormatoIntervalo(const std::string& str);
    static bool validarRango(int n, int m);
    static void capturarYValidarEntradas(int& n, int& m, std::vector<int>& usuarios, std::vector<int>& routers);
};

#endif // VALIDACIONES_H
