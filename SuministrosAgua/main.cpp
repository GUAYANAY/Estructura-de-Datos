#include <iostream>
#include <vector>
#include "Validaciones.h"
#include "SuministroAgua.h"

int main() {
    int n, m;
    std::vector<int> casas;
    std::vector<int> fuentes;

    Validaciones::capturarYValidarEntradas(n, m, casas, fuentes);

    SuministroAgua suministroAgua(casas, fuentes);
    int radioMinimo = suministroAgua.calcularRadioMinimo();

    std::cout << "El radio minimo necesario es: " << radioMinimo << std::endl;

    return 0;
}
