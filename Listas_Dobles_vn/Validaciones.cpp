/***********************************************************************
 * Module:  Validaciones.cpp
 * Author:  Erika Guayanay
 * Date: 25/11/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "Validaciones.h"
#include <iostream>
#include <regex>
#include <stdio.h>
#define dim 10

bool validarCedula(const std::string& cedula) {
    return std::regex_match(cedula, std::regex("\\d{10}"));
}

bool validarTexto(const std::string& texto) {
    return std::regex_match(texto, std::regex("[A-Za-z ]+"));
}

long int ingresarCedula() {
    long int cedula;
    printf("Ingrese su cedula: ");
    scanf("%ld", &cedula);
    return cedula;
}

bool validarCedulaReal(long int x) {
    int i, A[dim], res, sumapares = 0, sumaimpares = 0, s, mul, sumatotal = 0;
    long int coc;
    for (i = 9; i >= 0; i--) {
        coc = x / 10;
        res = x % 10;
        A[i] = res;
        x = coc;
    }

    for (i = 0; i < 9; i += 2) {
        mul = A[i] * 2;
        if (mul > 9)
            mul -= 9;
        sumapares += mul;
    }

    for (i = 1; i < 9; i += 2)
        sumaimpares += A[i];

    sumatotal = sumapares + sumaimpares;
    res = sumatotal % 10;
    s = 10 - res;
    if (s == 10)
        s = 0;

    return (s == A[9]);
}

void imprimirResultadoCedula(bool valido) {
    if (valido)
        printf("Cedula Valida\n");
    else
        printf("Cedula no Valida\n");
}
