from lista_simple import ListaSimple
from metodo_ordenamiento_externo import MetodoOrdenamientoExterno
from validaciones import *
import os

def clear_console():
    os.system('cls' if os.name == 'nt' else 'clear')

def main():
    lista_principal = ListaSimple()
    lista_auxiliar = ListaSimple()
    metodo_ordenamiento = MetodoOrdenamientoExterno()
    lista_principal.cargar_desde_archivo("personas.txt")

    while True:
        
        print("** Menu de opciones **")
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
        opcion = capturar_solo_numeros()

        if opcion == 1:
            while True:
                cedula = capturar_cedula()
                if not validar_cedula_real(cedula):
                    print("Cedula invalida. Intente de nuevo.")
                elif not validar_cedula_unica(cedula):
                    print("La cedula ya esta registrada. Intente de nuevo.")
                else:
                    break
            while True:
                nombre = capturar_solo_letras("Ingrese nombre: ")
                nombre = normalizar_nombre(nombre)
                if not validar_solo_letras(nombre):
                    print("Error: El nombre debe contener solo letras. Intente nuevamente.")
                else:
                    break
            while True:
                apellido = capturar_solo_letras("Ingrese apellido: ")
                apellido = normalizar_nombre(apellido)
                if not validar_solo_letras(apellido):
                    print("Error: El apellido debe contener solo letras. Intente nuevamente.")
                else:
                    break
            lista_principal.insertar_a_cola(cedula, nombre, apellido)
            lista_principal.guardar_en_archivo(cedula, nombre, apellido, "personas.txt")
            registrar_cedula(cedula)
            print("Persona registrada exitosamente.")
        

        elif opcion == 2:
            while True:
                cedula = capturar_cedula()
                if not validar_cedula_real(cedula):
                    print("Cedula invalida. Intente de nuevo.")
                else:
                    break
            persona = lista_principal.buscar(cedula)
            if not persona:
                print("Error: Persona no encontrada.")
           

        elif opcion == 3:
            while True:
                cedula = capturar_cedula()
                if not validar_cedula_real(cedula):
                    print("Cedula invalida. Intente de nuevo.")
                else:
                    break
            if lista_principal.eliminar(cedula):
                print("Persona eliminada exitosamente.")
            else:
                print("Error: Persona no encontrada o no pudo ser eliminada.")
            

        elif opcion == 4:
            lista_principal.mostrar()
            

        elif opcion == 5:
            cedula = capturar_cedula()
            if not validar_cedula_real(cedula):
                print("Cedula invalida. Intente de nuevo.")
                continue
            if not lista_principal.buscar(cedula):
                print("Error: Persona no encontrada.")
                continue
            caracter = capturar_una_letra()
            lista_principal.eliminar_caracter(cedula, caracter, lista_auxiliar)
            continue  # Volver al menú principal después de eliminar el carácter
            

        elif opcion == 6:
            cedula = capturar_cedula()
            if not validar_cedula_real(cedula):
                print("Cedula invalida. Intente de nuevo.")
                continue
            if not lista_principal.buscar(cedula):
                print("Error: Persona no encontrada.")
                continue
            caracter = capturar_una_letra()
            desplazamiento = validar_numero_1a25()
            lista_principal.cifrar_caracter(cedula, caracter, desplazamiento, lista_auxiliar)
            continue  # Volver al menú principal después de cifrar el carácter
            

        elif opcion == 7:
            lista_auxiliar.mostrar()
            

        elif opcion == 8:
            archivos_cubetas = []
            metodo_ordenamiento.distribuir_datos("personas.txt", archivos_cubetas)
            for archivo in archivos_cubetas:
                metodo_ordenamiento.ordenar_archivo(archivo)
            metodo_ordenamiento.fusionar_archivos(archivos_cubetas, "personas_ordenadas.txt")
            print("La lista ha sido ordenada y guardada en 'personas_ordenadas.txt'.")
            

        elif opcion == 9:
            metodo_ordenamiento.mostrar_archivo("personas_ordenadas.txt")
            

        elif opcion == 10:
            print("Saliendo...")
            break

        else:
            print("Opcion invalida. Intente de nuevo.")
            

if __name__ == "__main__":
    main()
