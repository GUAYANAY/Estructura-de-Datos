/***********************************************************************
 * Module:  Validaciones.h
 * Author:  Erika Guayanay
 * Date: 25/11/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#pragma once
#include <string>

bool validarCedula(const std::string& cedula); // Valida que sea un numero de 10 digitos.
bool validarTexto(const std::string& texto);  // Valida que solo contenga letras.
long int ingresarCedula();                    // Ingresa y valida formato de cedula.
bool validarCedulaReal(long int cedula);      // Valida si la cedula es real.
void imprimirResultadoCedula(bool valido);    // Imprime resultado de validacion.
