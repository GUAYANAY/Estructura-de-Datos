import os

class MetodoOrdenamientoExterno:
    def distribuir_datos(self, archivo_entrada, archivos_salida):
        try:
            with open(archivo_entrada, 'r') as archivo:
                cubetas = [open(f"cubeta_{chr(65 + i)}.txt", 'w') for i in range(26)]
                for linea in archivo:
                    cedula, nombre, apellido = linea.strip().split(',')
                    if nombre:
                        indice = ord(nombre[0].lower()) - ord('a')
                        if 0 <= indice < 26:
                            cubetas[indice].write(linea)
                for cubeta in cubetas:
                    cubeta.close()
                archivos_salida.extend([f"cubeta_{chr(65 + i)}.txt" for i in range(26)])
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
