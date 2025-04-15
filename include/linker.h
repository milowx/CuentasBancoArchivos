//declaraciones de variables globables, librerias, estructura, funciones, etc.
#ifndef LINKER_H
#define LINKER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

extern const int TAM;

typedef struct{
    char pnombre[50];
    char apellido[50];
    unsigned long int num_cuenta;
    unsigned long int num_tarjeta;
    double saldo;
    double interes;
    char genero;
} Cuenta;

extern Cuenta cuentas[];
extern int cuentas_leidas;
extern FILE* parchivo;

extern char MENSAJE[200];

//ayuda a buscar cuentas => " bsc.c "
int buscar(int num);
void buscar_una_cuenta(void);

//manipula informacion del archivo => " man.c "
void transferir(void);
void borrar(void);
void ingresar(void);
void ordenar(int modo);

//trabaja directamente con el archivo => " mod.c "
void leer_archivo(void);
void actualizar_archivo(void);

//muestra datos del archivo => " mst.c "
void mostrar_una_cuenta(int indice_cuenta);
void mostrar_todo(void);

//validaciones de entrada => " val.c "
void validar_char(char* letra, char opc1, char opc2);
void validar_fl(double* fl, double limite);
void validar_int(unsigned long int* num,unsigned long int limite);
void validar_menu(int* dec, int li, int ls);
void validar_cuenta(int* num);

//principal loop del programa => " bac.c "
void menu(void);
void leer_menu(void);
void modificar_menu(void);
void ordenar_menu(void);

//funciones de registro => " log.c " para el archivo "log.txt"
void mensaje_log(char* msj);
void obtener_hora(char* buffer, size_t magn);

#endif
