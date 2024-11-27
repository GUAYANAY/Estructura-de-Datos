#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <ctype.h>

using namespace std;

void identificarTipoDato(const char* input) {
    bool esEntero = true, esFlotante = true;

    // Comprobar si es un entero
    for (int i = 0; i < strlen(input); i++) {
        if (!isdigit(input[i])) {
            esEntero = false;
            break;
        }
    }

    // Comprobar si es un flotante (permite un solo punto decimal)
    int puntoDecimal = 0;
    for (int i = 0; i < strlen(input); i++) {
        if (!isdigit(input[i])) {
            if (input[i] == '.' && puntoDecimal == 0) {
                puntoDecimal++;
            } else {
                esFlotante = false;
                break;
            }
        }
    }

    // Detectar y mostrar el tipo de dato
    if (esEntero) {
        printf("Valor entero ingresado: %d\n", atoi(input));
    } else if (esFlotante) {
        printf("Valor flotante ingresado: %f\n", atof(input));
    } else if (strlen(input) == 1) {
        printf("Caracter ingresado: %c\n", input[0]);
    } else {
        printf("Cadena ingresada: %s\n", input);
    }
}

int main() {
    char input[50];
    char c;
    int i = 0;

    printf("Ingrese un valor cualquiera: ");
    
    // Leer la entrada del usuario con getch
    while ((c = getch()) != 13) { // 13 es el código ASCII de Enter
        printf("%c", c); // Mostrar el carácter
        input[i++] = c;
    }
    input[i] = '\0'; // Terminar la cadena

    printf("\n");
    identificarTipoDato(input); // Llamar a la función para identificar el tipo de dato

    return 0;
}
