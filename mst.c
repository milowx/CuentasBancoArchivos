//funciones que muestran informacion del archivo
#include "linker.h"

void mostrar_una_cuenta(int indice_cuenta){
    printf("\n\t%s      %s        %c          %ld         %ld        %.2lf         %.2lf\n",
    cuentas[indice_cuenta].pnombre, cuentas[indice_cuenta].apellido, cuentas[indice_cuenta].genero,
    cuentas[indice_cuenta].num_cuenta, cuentas[indice_cuenta].num_tarjeta, cuentas[indice_cuenta].saldo, cuentas[indice_cuenta].interes);
}

void mostrar_todo(void){
    printf("\n\tNOMBRE    APELLIDO     GENERO       NUMERO DE CUENTA      NUMERO DE TARJETA         SALDO       INTERES");
    for(int i=0; i<cuentas_leidas; i++){
        printf("\n\t%s      %s        %c          %ld         %ld        %.2lf         %.2lf",
        cuentas[i].pnombre, cuentas[i].apellido, cuentas[i].genero,
        cuentas[i].num_cuenta, cuentas[i].num_tarjeta, cuentas[i].saldo, cuentas[i].interes);
    }
}