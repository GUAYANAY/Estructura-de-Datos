"""
***********************************************************************
* UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
* ALUMNOS:  Erika Guayanay
* FECHA ENTREGA: 06 de enero de 2025
* PROGRAMA: Listas Circulares en python.
* NRC: 1992
***********************************************************************
"""

from ListaCircular import ListaCircular
from Validaciones import *
from MetodoOrdenamientoExterno import MetodoOrdenamientoExterno
import os

def clear_screen():
    os.system('cls' if os.name == 'nt' else 'clear')

def pause_screen():
    input("Press Enter to continue...")

def main():
    lista_circular = ListaCircular()
    lista_auxiliar = ListaCircular()
    metodo_ordenamiento = MetodoOrdenamientoExterno()

    try:
        if os.path.isfile("personas.txt"):
            lista_circular.cargar_desde_archivo("personas.txt")
    except Exception as e:
        print(f"Error al cargar datos iniciales: {e}")

    while True:
        clear_screen()
        print("\n----------------------------------------------------")
        print("\t\t MENU DE OPCIONES\t\t")
        print("----------------------------------------------------")
        print("1. Insertar persona")
        print("2. Buscar persona")
        print("3. Eliminar persona")
        print("4. Mostrar lista")
        print("5. Eliminar caracter de nombre")
        print("6. Cifrar un caracter")
        print("7. Mostrar lista auxiliar")
        print("8. Ordenar lista por nombre (Distribution Sort)")
        print("9. Mostrar archivo de distribucion ordenado")
        print("10. Salir")
        print("Seleccione una opcion: ", end="")
        opcion = capturar_solo_numeros()

        try:
            if opcion == 1:
                while True:
                    cedula = capturar_cedula()
                    if not validar_cedula_real(cedula):
                        pause_screen()
                        continue
                    if not validar_cedula_unica(cedula):
                        pause_screen()
                        continue
                    break

                while True:
                    print("Ingrese nombre: ", end="")
                    nombre = capturar_solo_letras()
                    if len(nombre) >= 3:
                        nombre = normalizar_nombre(nombre)
                        break
                    else:
                        print("Error: El nombre debe tener al menos 3 letras.")
                        pause_screen()

                while True:
                    print("Ingrese apellido: ", end="")
                    apellido = capturar_solo_letras()
                    if len(apellido) >= 3:
                        apellido = normalizar_nombre(apellido)
                        break
                    else:
                        print("Error: El apellido debe tener al menos 3 letras.")
                        pause_screen()

                lista_circular.insertar(cedula, nombre, apellido)
                lista_circular.guardar_en_archivo(cedula, nombre, apellido, "personas.txt")
                registrar_cedula(cedula)
                print("Persona registrada exitosamente.")
                pause_screen()

            elif opcion == 2:
                if not os.path.isfile("personas.txt"):
                    print("El archivo 'personas.txt' no existe. No hay datos para buscar.")
                    pause_screen()
                    continue

                cedula = capturar_cedula()
                if not validar_cedula_real(cedula):
                    pause_screen()
                    continue

                persona = lista_circular.buscar(cedula)
                if persona:
                    print(f"Persona encontrada: Cedula: {persona.get_cedula()}, Nombre: {persona.get_nombre()}, Apellido: {persona.get_apellido()}")
                else:
                    print("Persona no encontrada.")
                pause_screen()

            elif opcion == 3:
                if not os.path.isfile("personas.txt"):
                    print("El archivo 'personas.txt' no existe. No hay datos para eliminar.")
                    pause_screen()
                    continue

                cedula = capturar_cedula()
                if not validar_cedula_real(cedula):
                    pause_screen()
                    continue

                if lista_circular.eliminar(cedula):
                    eliminar_cedula(cedula)
                    lista_circular.eliminar_de_archivo(cedula, "personas.txt")
                    lista_circular.eliminar_de_cubetas(cedula)
                    print("Persona eliminada exitosamente.")
                else:
                    print("Error: Persona no encontrada o no pudo ser eliminada.")
                pause_screen()

            elif opcion == 4:
                lista_circular.mostrar()
                pause_screen()

            elif opcion == 5:
                if not os.path.isfile("personas.txt"):
                    print("El archivo 'personas.txt' no existe. No hay datos para eliminar.")
                    pause_screen()
                    continue

                cedula = capturar_cedula()
                if not validar_cedula_real(cedula):
                    pause_screen()
                    continue

                persona_encontrada = lista_circular.buscar(cedula)
                if persona_encontrada is None:
                    print("La cedula no existe en el archivo.")
                    pause_screen()
                    continue

                print("Ingrese caracter a eliminar: ", end="")
                caracter = capturar_una_letra()
                
                nombre = persona_encontrada.get_nombre()
                apellido = persona_encontrada.get_apellido()
                
                if caracter not in nombre and caracter not in apellido:
                    print("Error: Caracter no encontrado en nombre o apellido.")
                else:
                    lista_circular.eliminar_caracter(cedula, caracter, lista_auxiliar)
                
                pause_screen()

            elif opcion == 6:
                if not os.path.isfile("personas.txt"):
                    print("El archivo 'personas.txt' no existe. No hay datos para cifrar.")
                    pause_screen()
                    continue

                cedula = capturar_cedula()
                if not validar_cedula_real(cedula):
                    pause_screen()
                    continue

                persona_encontrada = lista_circular.buscar(cedula)
                if persona_encontrada is None:
                    pause_screen()
                    continue

                print("Ingrese caracter a cifrar: ", end="")
                caracter = capturar_una_letra()
                
                nombre = persona_encontrada.get_nombre()
                apellido = persona_encontrada.get_apellido()
                
                if caracter not in nombre and caracter not in apellido:
                    print("Error: Caracter no encontrado en nombre o apellido.")
                else:
                    print("Ingrese desplazamiento: ", end="")
                    desplazamiento = validar_numero_1_a_25()
                    lista_circular.cifrar_caracter(cedula, caracter, desplazamiento, lista_auxiliar)
                
                pause_screen()

            elif opcion == 7:
                lista_auxiliar.mostrar()
                pause_screen()

            elif opcion == 8:
                if not os.path.isfile("personas.txt"):
                    print("El archivo 'personas.txt' no existe. No hay datos para ordenar.")
                    pause_screen()
                    continue

                if not os.path.isfile("personas.txt") or os.path.getsize("personas.txt") == 0:
                    print("El archivo 'personas.txt' está vacío. No hay datos para procesar.")
                    pause_screen()
                    continue

                archivos_cubetas = []
                metodo_ordenamiento.distribuir_datos("personas.txt", archivos_cubetas)

                for archivo in archivos_cubetas:
                    metodo_ordenamiento.ordenar_archivo(archivo)

                metodo_ordenamiento.fusionar_archivos(archivos_cubetas, "personas_ordenadas.txt")
                print("La lista ha sido ordenada y guardada en 'personas_ordenadas.txt'.")
                pause_screen()

            elif opcion == 9:
                if not os.path.isfile("personas_ordenadas.txt"):
                    print("El archivo 'personas_ordenadas.txt' no existe. No hay datos para mostrar.")
                    pause_screen()
                    continue

                if not os.path.isfile("personas_ordenadas.txt") or os.path.getsize("personas_ordenadas.txt") == 0:
                    print("El archivo 'personas_ordenadas.txt' no existe o está vacío. No hay datos para mostrar.")
                    pause_screen()
                    continue

                metodo_ordenamiento.mostrar_archivo("personas_ordenadas.txt")
                pause_screen()

            elif opcion == 10:
                print("Saliendo...")
                break

            else:
                print("Opcion invalida. Intente de nuevo.")
                pause_screen()
        except Exception as e:
            print(f"Error en la opcion seleccionada: {e}")
            pause_screen()

if __name__ == "__main__":
    main()
