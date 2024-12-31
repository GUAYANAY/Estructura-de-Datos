#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <sstream>
#include "Validaciones.h"
#include "CamarasSeguridad.h"
#include <conio.h>

using namespace std;

int main() {
    Validaciones validaciones;
    int n, m;
    vector<int> locations;
    vector<int> cameras;

    validaciones.capturarYValidarEntradas(n, m, locations, cameras);

    if (!validaciones.validarEntradas(n, m, locations, cameras)) {
        cerr << "Entradas no validas" << endl;
        return 1;
    }

    CamarasSeguridad camarasSeguridad;
    int r = camarasSeguridad.calcularRangoMinimo(locations, cameras);

    cout << "El rango minimo necesario es: " << r << endl;
    return 0;
}
