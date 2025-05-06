#include <iostream>
#include <windows.h> // Necesario para SetConsoleOutputCP y SetConsoleCP
#include "TrianguloMagico.h"
#include "Graficador.h"
#include "Validaciones.h"

int main() {
    // Establecer la configuración regional a UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    while (true) {
        std::cout << "=============================\n\tTriángulo Mágico\n=============================\nIngrese el nivel del triángulo mágico (1-14) o 'X' para salir: ";
        std::string input = Validaciones::leerSoloNumerosOX();

        if (input == "X" || input == "x") {
            std::cout << "Saliendo del programa." << std::endl;
            break;
        }

        try {
            int n = std::stoi(input);
            Validaciones::validarEntero(n);

            TrianguloMagico triangulo(n);
            triangulo.generar();

            std::cout << "Triángulo Mágico generado:\n";
            for (const auto& fila : triangulo.getMatriz()) {
                for (int num : fila) {
                    std::cout << num << " ";
                }
                std::cout << std::endl;
            }

            Graficador::dibujarCuadroLatino(triangulo.getMatriz());

            // Limpiar la consola después de cada gráfico
            system("cls");
            
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
