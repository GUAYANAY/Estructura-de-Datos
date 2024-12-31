#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <vector>
#include <string>

class Validaciones {
public:
    bool validarEntradas(int n, int m, const std::vector<int>& locations, const std::vector<int>& cameras);
    bool isValidInput();
    bool isNumber(char c); // Method to check if a character is a valid number input
    bool esNumero(const std::string& str); // Method to check if a string is a valid number
    std::string capturarEntrada(); // Method to capture input
    bool validarFormatoIntervalo(const std::string& str); // Method to validate interval format
    bool validarRango(int n, int m); // Method to validate range of n and m
    void capturarYValidarEntradas(int& n, int& m, std::vector<int>& locations, std::vector<int>& cameras); // Method to capture and validate entries
};

#endif // VALIDACIONES_H
