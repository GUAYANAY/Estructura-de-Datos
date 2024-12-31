#include "Validaciones.h"
#include <algorithm>
#include <limits>
#include <iostream>
#include <conio.h>
#include <sstream>

bool Validaciones::validarEntradas(int n, int m, const std::vector<int>& locations, const std::vector<int>& cameras) {
    if (n < 1 || m < 1 || n > 100000 || m > 100000) {
        return false;
    }
    if (!std::is_sorted(locations.begin(), locations.end()) || !std::is_sorted(cameras.begin(), cameras.end())) {
        return false;
    }
    return true;
}

bool Validaciones::isValidInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
}

bool Validaciones::isNumber(char c) {
    return (c >= '0' && c <= '9') || c == ' ' || c == '-' || c == '\b' || c == '\n';
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

bool Validaciones::validarFormatoIntervalo(const std::string& str) {
    std::stringstream ss(str);
    std::string a_str, b_str;
    ss >> a_str >> b_str;
    if (ss.rdbuf()->in_avail() != 0 || a_str.empty() || b_str.empty()) { // Check if there are more than two numbers or if any number is missing
        return false;
    }
    if (!esNumero(a_str) || !esNumero(b_str)) {
        return false;
    }
    long long a = std::stoll(a_str);
    long long b = std::stoll(b_str);
    if (a < 0 || a > 100 || b < 0 || b > 100) {
        return false;
    }
    return true;
}

bool Validaciones::validarRango(int n, int m) {
    return (n >= 1 && n <= 100) && (m >= 1 && m <= 100);
}

void Validaciones::capturarYValidarEntradas(int& n, int& m, std::vector<int>& locations, std::vector<int>& cameras) {
    while (true) {
        try {
            std::cout << "Ingrese el numero de ubicaciones y camaras (1-100): ";
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

    locations.resize(n);
    cameras.resize(m);

    while (true) {
        try {
            std::cout << "Ingrese las ubicaciones: ";
            std::string input = capturarEntrada();
            std::istringstream iss(input);

            for (int i = 0; i < n; ++i) {
                if (!(iss >> locations[i])) {
                    throw std::invalid_argument("Formato de entrada invalido para las ubicaciones");
                }
                if (i > 0 && locations[i] <= locations[i - 1]) {
                    throw std::invalid_argument("Las ubicaciones deben ser ingresadas en orden creciente");
                }
            }

            if (iss.rdbuf()->in_avail() != 0) {
                throw std::invalid_argument("El numero de ubicaciones ingresadas no coincide con el numero especificado");
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
            std::cout << "Ingrese las posiciones de las camaras: ";
            std::string input = capturarEntrada();
            std::istringstream iss(input);

            for (int i = 0; i < m; ++i) {
                if (!(iss >> cameras[i])) {
                    throw std::invalid_argument("Formato de entrada invalido para las posiciones de las camaras");
                }
                if (i > 0 && cameras[i] <= cameras[i - 1]) {
                    throw std::invalid_argument("Las posiciones de las camaras deben ser ingresadas en orden creciente");
                }
            }

            if (iss.rdbuf()->in_avail() != 0) {
                throw std::invalid_argument("El numero de posiciones de las camaras ingresadas no coincide con el numero especificado");
            }

            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error de entrada: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
