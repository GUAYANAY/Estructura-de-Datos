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
    def distribuir_datos(self, archivo_entrada, archivos_salida):
        try:
            with open(archivo_entrada, 'r') as archivo:
                cubetas = {}
                for linea in archivo:
                    cedula, nombre, apellido = linea.strip().split(',')
                    if nombre:
                        indice = nombre[0].upper()
                        if indice.isalpha():
                            if indice not in cubetas:
                                cubetas[indice] = open(f"cubeta_{indice}.txt", 'w')
                            cubetas[indice].write(linea)
                for cubeta in cubetas.values():
                    cubeta.close()
                archivos_salida.extend([f"cubeta_{indice}.txt" for indice in cubetas])
            print("Datos distribuidos correctamente en las cubetas.")
        except FileNotFoundError:
            print("Error al abrir el archivo de entrada.")

    def ordenar_archivo(self, nombre_archivo):
        try:
            with open(nombre_archivo, 'r') as archivo:
                datos = archivo.readlines()
            datos.sort(key=lambda x: (x.split(',')[1], x.split(',')[2]))
            with open(nombre_archivo, 'w') as archivo:
                archivo.writelines(datos)
        except FileNotFoundError:
            print(f"Error al abrir el archivo {nombre_archivo} para lectura.")

    def fusionar_archivos(self, archivos_cubetas, archivo_final):
        try:
            with open(archivo_final, 'w') as archivo_salida:
                for archivo_cubeta in archivos_cubetas:
                    with open(archivo_cubeta, 'r') as archivo:
                        archivo_salida.writelines(archivo.readlines())
            print(f"Archivos fusionados en {archivo_final}.")
        except FileNotFoundError:
            print("Error al abrir el archivo de salida.")

    def mostrar_archivo(self, nombre_archivo):
        try:
            with open(nombre_archivo, 'r') as archivo:
                print(archivo.read())
        except FileNotFoundError:
            print("No se pudo abrir el archivo.")
