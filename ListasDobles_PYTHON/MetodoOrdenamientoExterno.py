"""
***********************************************************************
* UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
* ALUMNOS:  Erika Guayanay
* FECHA ENTREGA: 06 de enero de 2025
* PROGRAMA: Listas Circulares en python.
* NRC: 1992
***********************************************************************
"""

import os

class MetodoOrdenamientoExterno:
    def distribuir_datos(self, nombre_archivo, archivos_cubetas):
        try:
            with open(nombre_archivo, "r") as archivo:
                cubetas = {}
                for linea in archivo:
                    inicial = linea.strip().split(',')[1][0].lower()
                    if inicial not in cubetas:
                        cubetas[inicial] = open(f"cubeta_{inicial}.txt", "w")
                        archivos_cubetas.append(f"cubeta_{inicial}.txt")
                    cubetas[inicial].write(linea)
                
                for archivo in cubetas.values():
                    archivo.close()
        except FileNotFoundError:
            print("Error al abrir el archivo.")

    def ordenar_archivo(self, nombre_archivo):
        try:
            with open(nombre_archivo, "r") as archivo:
                datos = [linea.strip() for linea in archivo]
            datos.sort(key=lambda x: (x.split(',')[1], x.split(',')[2]))
            with open(nombre_archivo, "w") as archivo:
                for dato in datos:
                    archivo.write(dato + "\n")
        except FileNotFoundError:
            print(f"Error al abrir el archivo {nombre_archivo} para lectura.")

    def fusionar_archivos(self, archivos_cubetas, archivo_final):
        try:
            with open(archivo_final, "w") as archivo_salida:
                for archivo_cubeta in archivos_cubetas:
                    with open(archivo_cubeta, "r") as archivo:
                        for linea in archivo:
                            archivo_salida.write(linea)
            print(f"Archivos fusionados en {archivo_final}.")
        except FileNotFoundError:
            print("Error al abrir el archivo de salida.")

    def mostrar_archivo(self, nombre_archivo):
        try:
            with open(nombre_archivo, "r") as archivo:
                for linea in archivo:
                    print(linea.strip())
        except FileNotFoundError:
            print("No se pudo abrir el archivo.")
