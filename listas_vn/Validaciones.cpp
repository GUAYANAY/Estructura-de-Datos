#include "Validaciones.h"
#include <cctype>

bool validarCedula(string cedula) {
    if (cedula.size() != 10) return false;
    for (char c : cedula) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool validarSoloLetras(string texto) {
    for (char c : texto) {
        if (!isalpha(c) && c != ' ') return false;
    }
    return true;
}
