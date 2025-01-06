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
    def distribuir_datos(self, archivo_origen, archivos_cubetas):
        try:
            # Crear un diccionario para almacenar las cubetas
            cubetas = {}

            # Leer el archivo de origen
            with open(archivo_origen, "r") as archivo:
                for linea in archivo:
                    nombre = linea.split(",")[1].strip()
                    letra_inicial = nombre[0].upper()

                    # Agregar la letra inicial al diccionario si no existe
                    if letra_inicial not in cubetas:
                        cubetas[letra_inicial] = []

                    # Agregar la línea a la cubeta correspondiente
                    cubetas[letra_inicial].append(linea)

            # Crear archivos de cubetas solo para las letras existentes
            for letra, lineas in cubetas.items():
                nombre_archivo = f"cubeta_{letra}.txt"
                archivos_cubetas.append(nombre_archivo)
                with open(nombre_archivo, "w") as archivo_cubeta:
                    archivo_cubeta.writelines(lineas)

        except Exception as e:
            print(f"Error al distribuir datos: {e}")

    def ordenar_archivo(self, nombre_archivo):
        try:
            if not os.path.isfile(nombre_archivo):
                print(f"Error al abrir el archivo {nombre_archivo} para lectura.")
                return

            with open(nombre_archivo, "r") as archivo:
                datos = [linea.strip() for linea in archivo]

            datos.sort(key=lambda x: (x.split(',')[1], x.split(',')[2]))

            with open(nombre_archivo, "w") as archivo:
                for dato in datos:
                    archivo.write(dato + "\n")
        except Exception as e:
            print(f"Error al ordenar archivo: {e}")

    def fusionar_archivos(self, archivos_cubetas, archivo_final):
        try:
            with open(archivo_final, "w") as archivo_salida:
                for archivo_cubeta in archivos_cubetas:
                    if os.path.isfile(archivo_cubeta):
                        with open(archivo_cubeta, "r") as archivo:
                            for linea in archivo:
                                archivo_salida.write(linea)
            print(f"Archivos fusionados en {archivo_final}.")
        except Exception as e:
            print(f"Error al fusionar archivos: {e}")

    def mostrar_archivo(self, nombre_archivo):
        try:
            if not os.path.isfile(nombre_archivo):
                print("No se pudo abrir el archivo.")
                return

            print("Lista ordenada:")
            with open(nombre_archivo, "r") as archivo:
                for linea in archivo:
                    print(linea.strip())
        except Exception as e:
            print(f"Error al mostrar archivo: {e}")
