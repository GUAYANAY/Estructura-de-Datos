#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <vector>
#include <utility>
#include <string>
#include <conio.h>

class Validaciones {
public:
    void leerDatos(int& N, int& M, std::vector<std::pair<long long, long long>>& intervalos);
private:
    bool esNumero(const std::string& str);
    std::string capturarEntrada();
    std::string capturarEntradaConValidacion();
    bool validarFormatoIntervalo(const std::string& str);
};

#endif // VALIDACIONES_H
