import os
from Nodo import Nodo

class ListaDoble:
    def __init__(self):
        self.primero = None
        self.ultimo = None

    def __del__(self):
        while self.primero:
            temp = self.primero
            self.primero = self.primero.get_siguiente()
            del temp

    def validar_cedula_unica(self, cedula):
        temp = self.primero
        while temp:
            if temp.get_cedula() == cedula:
                return False
            temp = temp.get_siguiente()
        return True

    def insertar(self, cedula, nombre, apellido):
        if not self.validar_cedula_unica(cedula):
            print("Error: La cedula ya existe en la lista.")
            return

        nuevo = Nodo(cedula, nombre, apellido)
        if not self.primero:
            self.primero = nuevo
            self.ultimo = nuevo
        else:
            self.ultimo.set_siguiente(nuevo)
            nuevo.set_anterior(self.ultimo)
            self.ultimo = nuevo

    def buscar(self, cedula):
        try:
            with open("personas.txt", "r") as archivo:
                for linea in archivo:
                    archivo_cedula, nombre, apellido = linea.strip().split(',')
                    if archivo_cedula == cedula:
                        print("Persona encontrada")
                        print(f"Cedula: {archivo_cedula}")
                        print(f"Nombre: {nombre}")
                        print(f"Apellido: {apellido}")
                        return Nodo(archivo_cedula, nombre, apellido)
        except FileNotFoundError:
            print("Error al abrir el archivo personas.txt.")
        print(f"La cedula {cedula} no existe en el archivo personas.txt.")
        return None

    def eliminar(self, cedula):
        temp = self.primero
        while temp and temp.get_cedula() != cedula:
            temp = temp.get_siguiente()

        if not temp:
            print(f"Persona con cedula {cedula} no encontrada.")
            return False

        if temp == self.primero:
            self.primero = temp.get_siguiente()
            if self.primero:
                self.primero.set_anterior(None)
            else:
                self.ultimo = None
        elif temp == self.ultimo:
            self.ultimo = temp.get_anterior()
            if self.ultimo:
                self.ultimo.set_siguiente(None)
            else:
                self.primero = None
        else:
            temp.get_anterior().set_siguiente(temp.get_siguiente())
            temp.get_siguiente().set_anterior(temp.get_anterior())

        del temp

        try:
            with open("personas.txt", "r") as archivo_entrada, open("personas_temp.txt", "w") as archivo_temporal:
                for linea in archivo_entrada:
                    archivo_cedula, nombre, apellido = linea.strip().split(',')
                    if archivo_cedula != cedula:
                        archivo_temporal.write(f"{archivo_cedula},{nombre},{apellido}\n")
        except FileNotFoundError:
            print("Error al abrir los archivos.")
            return False

        os.remove("personas.txt")
        os.rename("personas_temp.txt", "personas.txt")
        return True

    def actualizar_archivo(self, cedula, nuevo_nombre=None, nuevo_apellido=None):
        try:
            with open("personas.txt", "r") as archivo_entrada, open("personas_temp.txt", "w") as archivo_temporal:
                for linea in archivo_entrada:
                    archivo_cedula, nombre, apellido = linea.strip().split(',')
                    if archivo_cedula == cedula:
                        if nuevo_nombre and nuevo_apellido:
                            archivo_temporal.write(f"{archivo_cedula},{nuevo_nombre},{nuevo_apellido}\n")
                    else:
                        archivo_temporal.write(linea)
            os.remove("personas.txt")
            os.rename("personas_temp.txt", "personas.txt")
        except FileNotFoundError:
            print("Error al abrir los archivos.")

    def eliminar_caracter(self, cedula, caracter, lista_auxiliar):
        temp = self.buscar(cedula)
        if not temp:
            return False
        nuevo_nombre = temp.get_nombre().replace(caracter, '')
        nuevo_apellido = temp.get_apellido().replace(caracter, '')
        temp.set_nombre(nuevo_nombre)
        temp.set_apellido(nuevo_apellido)
        lista_auxiliar.insertar(temp.get_cedula(), nuevo_nombre, nuevo_apellido)
        self.actualizar_archivo(cedula, nuevo_nombre, nuevo_apellido)
        print("Caracter eliminado correctamente del archivo y lista auxiliar actualizada.")
        return True

    def cifrar_caracter(self, cedula, caracter, desplazamiento, lista_auxiliar):
        temp = self.buscar(cedula)
        if not temp:
            return
        cifrar = lambda c: chr((ord(c) - ord('a') + desplazamiento) % 26 + ord('a')) if c == caracter and c.isalpha() else c
        nuevo_nombre = ''.join(cifrar(c) for c in temp.get_nombre())
        nuevo_apellido = ''.join(cifrar(c) for c in temp.get_apellido())
        temp.set_nombre(nuevo_nombre)
        temp.set_apellido(nuevo_apellido)
        lista_auxiliar.insertar(temp.get_cedula(), nuevo_nombre, nuevo_apellido)
        self.actualizar_archivo(cedula, nuevo_nombre, nuevo_apellido)
        print(f"Caracter cifrado correctamente con desplazamiento {desplazamiento}. Archivo actualizado y lista auxiliar actualizada.")

    def guardar_en_archivo(self, cedula, nombre, apellido, nombre_archivo):
        with open(nombre_archivo, "a") as archivo:
            archivo.write(f"{cedula},{nombre},{apellido}\n")

    def mostrar(self):
        temp = self.primero
        if not temp:
            print("NULL")
            return
        while temp:
            print(f"\nCedula: {temp.get_cedula()}\nNombre: {temp.get_nombre()}\nApellido: {temp.get_apellido()} ->\n")
            temp = temp.get_siguiente()

    def cargar_desde_archivo(self, nombre_archivo):
        try:
            with open(nombre_archivo, "r") as archivo:
                for linea in archivo:
                    cedula, nombre, apellido = linea.strip().split(',')
                    self.insertar(cedula, nombre, apellido)
        except FileNotFoundError:
            print("No se pudo abrir el archivo.")
