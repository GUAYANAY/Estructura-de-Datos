#include "Validaciones.h"
#include <conio.h> // Para usar _getch()
#include <iostream>
#include <stdexcept>

bool Validations::validateInput(int n, int m) {
    return (n > 0 && m > 0 && n <= 105 && m <= 105);
}

std::string Validations::getValidatedInput() {
    try {
        std::string input;
        char ch;
        bool lastCharWasDigit = false;
        while (true) {
            input.clear();
            lastCharWasDigit = false;
            while ((ch = _getch()) != 13) { // 13 es el código ASCII para Enter
                if (ch >= '0' && ch <= '9' || ch == ' ' || ch == 8 || (ch == '-' && !lastCharWasDigit && (input.empty() || input.back() == ' '))) { // 8 es el código ASCII para Backspace
                    if (ch == 8) { // Si es Backspace
                        if (!input.empty()) {
                            if (isdigit(input.back())) {
                                lastCharWasDigit = false;
                            }
                            std::cout << "\b \b"; // Borra el último carácter en la consola
                            input.pop_back();
                        }
                    } else {
                        std::cout << ch; // Muestra el carácter en la consola
                        input.push_back(ch);
                        lastCharWasDigit = isdigit(ch);
                    }
                }
            }
            if (!input.empty()) {
                std::cout << std::endl; // Nueva línea después de Enter
                return input;
            } else {
                std::cout << "\nEntrada vacia, por favor ingrese un valor: ";
            }
        }
    } catch (const std::exception& e) {
        throw std::runtime_error("Error al validar la entrada: " + std::string(e.what()));
    }
}
