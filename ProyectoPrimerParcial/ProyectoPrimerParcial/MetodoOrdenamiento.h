
#ifndef METODO_ORDENAMIENTO_EXTERNO_H
#define METODO_ORDENAMIENTO_EXTERNO_H

#include <string>
#include <vector>

class MetodoOrdenamientoExterno {
public:
    void distribuirDatos(const std::string& archivoEntrada, std::vector<std::string>& archivosSalida);
    void ordenarArchivo(const std::string& nombreArchivo);
    void fusionarArchivos(const std::vector<std::string>& archivosCubetas, const std::string& archivoFinal);
    void mostrarArchivo(const std::string& nombreArchivo);
};

#endif // METODO_ORDENAMIENTO_EXTERNO_H