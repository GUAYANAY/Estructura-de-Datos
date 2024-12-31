#include "Validaciones.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <conio.h>
#include <limits>

void Validaciones::validarEntradas(int n, int m, const std::vector<int>& casas, const std::vector<int>& fuentes) {
    if (n < 1 || n > 100 || m < 1 || m > 100) {
        throw std::invalid_argument("n and m must be between 1 and 100.");
    }

    for (int casa : casas) {
        if (casa < -100 || casa > 100) {
            throw std::invalid_argument("Casa positions must be between -100 and 100.");
        }
    }

    for (int fuente : fuentes) {
        if (fuente < -100 || fuente > 100) {
            throw std::invalid_argument("Fuente positions must be between -100 and 100.");
        }
    }
}

bool Validaciones::validarRango(int n, int m) {
    return (n >= 1 && n <= 100) && (m >= 1 && m <= 100);
}

bool Validaciones::esNumero(const std::string& str) {
    if (str.empty()) return false;
    size_t start = 0;
    if (str[0] == '-') start = 1; // Handle negative numbers
    for (size_t i = start; i < str.size(); ++i) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

std::string Validaciones::capturarEntrada() {
    std::string input;
    char ch;
    while ((ch = _getch()) != '\r') { // '\r' is the Enter key
        if (isdigit(ch) || ch == '-' || ch == ' ') {
            std::cout << ch;
            input += ch;
        } else if (ch == '\b' && !input.empty()) { // '\b' is the Backspace key
            std::cout << "\b \b";
            input.pop_back();
        }
    }
    std::cout << std::endl;
    // Remove leading and trailing spaces
    input.erase(0, input.find_first_not_of(' '));
    input.erase(input.find_last_not_of(' ') + 1);
    return input;
}

void Validaciones::capturarYValidarEntradas(int& n, int& m, std::vector<int>& casas, std::vector<int>& fuentes) {
    while (true) {
        try {
            std::cout << "Ingrese la cantidad de casas y fuentes (1-100): ";
            std::string input = capturarEntrada();
            std::istringstream iss(input);

            int count = 0;
            std::string temp;
            while (iss >> temp) {
                count++;
            }

            if (count != 2) {
                throw std::invalid_argument("Debe ingresar exactamente dos numeros");
            }

            iss.clear();
            iss.str(input);
            if (!(iss >> n >> m)) {
                throw std::invalid_argument("Formato de entrada invalido");
            }

            if (!validarRango(n, m)) {
                throw std::invalid_argument("Los numeros deben estar en el rango de 1 a 100");
            }

            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error de entrada: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    casas.resize(n);
    fuentes.resize(m);

    while (true) {
        try {
            std::cout << "Ingrese las posiciones de las casas: ";
            std::string input = capturarEntrada();
            std::istringstream iss(input);

            for (int i = 0; i < n; ++i) {
                if (!(iss >> casas[i])) {
                    throw std::invalid_argument("Formato de entrada invalido para las posiciones de las casas");
                }
                if (casas[i] < -100 || casas[i] > 100) {
                    throw std::invalid_argument("Las posiciones de las casas deben estar entre -100 y 100");
                }
                if (i > 0 && casas[i] <= casas[i - 1]) {
                    throw std::invalid_argument("Las posiciones de las casas deben ser ingresadas en orden creciente");
                }
            }

            if (iss.rdbuf()->in_avail() != 0) {
                throw std::invalid_argument("El numero de posiciones de las casas ingresadas no coincide con el numero especificado");
            }

            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error de entrada: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    while (true) {
        try {
            std::cout << "Ingrese las posiciones de las fuentes: ";
            std::string input = capturarEntrada();
            std::istringstream iss(input);

            for (int i = 0; i < m; ++i) {
                if (!(iss >> fuentes[i])) {
                    throw std::invalid_argument("Formato de entrada invalido para las posiciones de las fuentes");
                }
                if (fuentes[i] < -100 || fuentes[i] > 100) {
                    throw std::invalid_argument("Las posiciones de las fuentes deben estar entre -100 y 100");
                }
                if (i > 0 && fuentes[i] <= fuentes[i - 1]) {
                    throw std::invalid_argument("Las posiciones de las fuentes deben ser ingresadas en orden creciente");
                }
            }

            if (iss.rdbuf()->in_avail() != 0) {
                throw std::invalid_argument("El numero de posiciones de las fuentes ingresadas no coincide con el numero especificado");
            }

            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error de entrada: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
