//definiciones de variables globales declaradas en linker.h
#include "linker.h"

const int TAM = 2000;

Cuenta cuentas[TAM];
int cuentas_leidas = 0;
FILE* parchivo = NULL;

char MENSAJE[200];