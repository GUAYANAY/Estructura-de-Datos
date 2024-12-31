#include <iostream>
#include <vector>
#include "validaciones.h"
#include "PuntosAcceso.h"

int main() {
    int n, m;
    std::vector<int> usuarios;
    std::vector<int> routers;
    
    Validaciones::capturarYValidarEntradas(n, m, usuarios, routers);
    
    if (!Validaciones::validarEntradas(n, m, usuarios, routers)) {
        std::cerr << "Entradas no validas" << std::endl;
        return 1;
    }
    
    int r_minimo = encontrarRMinimo(usuarios, routers);
    std::cout << "El valor minimo de r necesario es: " << r_minimo << std::endl;
    
    return 0;
}
