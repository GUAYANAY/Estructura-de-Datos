"""
***********************************************************************
* UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
* ALUMNOS:  Erika Guayanay
* FECHA ENTREGA: 06 de enero de 2025
* PROGRAMA: Listas Circulares en python.
* NRC: 1992
***********************************************************************
"""

import re
import msvcrt
import os

class NodoCedula:
    def __init__(self, cedula):
        self.cedula = cedula
        self.siguiente = None

class ListaCedulas:
    def __init__(self):
        self.primero = None

    def agregar(self, cedula):
        nuevo = NodoCedula(cedula)
        if self.primero is None:
            self.primero = nuevo
        else:
            temp = self.primero
            while temp.siguiente is not None:
                temp = temp.siguiente
            temp.siguiente = nuevo

    def eliminar(self, cedula):
        temp = self.primero
        anterior = None
        while temp is not None and temp.cedula != cedula:
            anterior = temp
            temp = temp.siguiente
        if temp is not None:
            if anterior is None:
                self.primero = temp.siguiente
            else:
                anterior.siguiente = temp.siguiente

    def existe(self, cedula):
        temp = self.primero
        while temp is not None:
            if temp.cedula == cedula:
                return True
            temp = temp.siguiente
        return False

# Lista para almacenar las cedulas unicas
lista_cedulas = ListaCedulas()

def registrar_cedula(cedula):
    lista_cedulas.agregar(cedula)

def eliminar_cedula(cedula):
    lista_cedulas.eliminar(cedula)

def validar_cedula_real(cedula):
    try:
        if len(cedula) != 10 or not cedula.isdigit():
            print("Error: La cedula debe contener exactamente 10 digitos y solo numeros.")
            return False

        provincia = int(cedula[:2])
        if provincia < 1 or provincia > 24:
            print("Error: La cedula tiene un codigo de provincia invalido.")
            return False

        digito_verificador = int(cedula[9])
        suma = 0

        for i in range(9):
            digito = int(cedula[i])
            if i % 2 == 0:
                digito *= 2
                if digito > 9:
                    digito -= 9
            suma += digito

        decena_superior = (suma + 9) // 10 * 10
        calculado = decena_superior - suma

        if calculado != digito_verificador:
            print("Error: La cedula no es valida.")
            return False

        return True
    except Exception as e:
        print(f"Error al validar cedula real: {e}")
        return False

def validar_cedula_unica(cedula):
    try:
        if os.path.isfile("personas.txt"):
            with open("personas.txt", "r") as archivo:
                for linea in archivo:
                    if linea.startswith(cedula + ","):
                        print("Error: La cedula ya esta registrada.")
                        return False
        return True
    except Exception as e:
        print(f"Error al validar cedula unica: {e}")
        return False

def validar_solo_letras(texto):
    try:
        if not bool(re.match("^[a-zA-Z ]+$", texto)):
            print("Error: Debe ingresar solo letras.")
            return False
        if len(texto) < 3:
            print("Error: Debe ingresar al menos 3 letras.")
            return False
        return True
    except Exception as e:
        print(f"Error al validar solo letras: {e}")
        return False

def capturar_solo_numeros():
    try:
        entrada = ""
        while True:
            tecla = msvcrt.getch()
            if tecla.isdigit():
                entrada += tecla.decode()
                print(tecla.decode(), end="", flush=True)
            elif tecla == b'\r':  # Enter key
                if entrada:
                    print()
                    return int(entrada)
                else:
                    print("\nError: Debe ingresar al menos un numero.")
            elif tecla == b'\b' and entrada:  # Backspace key
                entrada = entrada[:-1]
                print("\b \b", end="", flush=True)
    except Exception as e:
        print(f"Error al capturar solo numeros: {e}")
        return None

def capturar_solo_letras():
    try:
        while True:
            entrada = ""
            while True:
                tecla = msvcrt.getch()
                if tecla.isalpha() or tecla == b' ':
                    entrada += tecla.decode()
                    print(tecla.decode(), end="", flush=True)
                elif tecla == b'\r':  # Enter key
                    if len(entrada) >= 3:
                        print()
                        return entrada
                    else:
                        print("\nError: Debe ingresar al menos 3 letras.")
                        break
                elif tecla == b'\b' and entrada:  # Backspace key
                    entrada = entrada[:-1]
                    print("\b \b", end="", flush=True)
    except Exception as e:
        print(f"Error al capturar solo letras: {e}")
        return None

def normalizar_nombre(nombre):
    try:
        return nombre.capitalize()
    except Exception as e:
        print(f"Error al normalizar nombre: {e}")
        return nombre

def capturar_cedula():
    try:
        while True:
            entrada = ""
            print("Ingrese cedula (10 digitos): ", end="", flush=True)
            while True:
                tecla = msvcrt.getch()
                if tecla.isdigit():
                    entrada += tecla.decode()
                    print(tecla.decode(), end="", flush=True)
                elif tecla == b'\r':  # Enter key
                    if len(entrada) == 10:
                        print()
                        return entrada
                    else:
                        print("\nError: La cedula debe contener exactamente 10 digitos.")
                        break
                elif tecla == b'\b' and entrada:  # Backspace key
                    entrada = entrada[:-1]
                    print("\b \b", end="", flush=True)
    except Exception as e:
        print(f"Error al capturar cedula: {e}")
        return None

def capturar_una_letra():
    try:
        while True:
            tecla = msvcrt.getch()
            if tecla.isalpha() and len(tecla) == 1:
                print(tecla.decode())
                return tecla.decode()
            elif tecla == b'\r':  # Enter key
                print("\nError: Debe ingresar una sola letra.")
    except Exception as e:
        print(f"Error al capturar una letra: {e}")
        return None

def validar_numero_1_a_25():
    try:
        while True:
            entrada = ""
            while True:
                tecla = msvcrt.getch()
                if tecla.isdigit():
                    entrada += tecla.decode()
                    print(tecla.decode(), end="", flush=True)
                elif tecla == b'\r':  # Enter key
                    if entrada and 1 <= int(entrada) <= 25:
                        print()
                        return int(entrada)
                    else:
                        print("\nError: Debe ingresar un numero entre 1 y 25.")
                        entrada = ""  # Reset the variable to allow re-entry
                        break
                elif tecla == b'\b' and entrada:  # Backspace key
                    entrada = entrada[:-1]
                    print("\b \b", end="", flush=True)
    except Exception as e:
        print(f"Error al validar numero entre 1 y 25: {e}")
        return None
