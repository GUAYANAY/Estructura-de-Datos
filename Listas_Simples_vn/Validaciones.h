#pragma once
#include <string>

bool validarCedulaReal(const std::string& cedula);
bool validarCedulaUnica(const std::string& cedula);
void registrarCedula(const std::string& cedula);
void eliminarCedula(const std::string& cedula);
bool validarSoloLetras(const std::string& texto);
bool existeCedula(const std::string& cedula);
