//funciones que trabajan directamente con el archivo
#include "linker.h"

void leer_archivo(void){
    parchivo=fopen("archivos/banco.txt", "rt");

    while((fscanf(parchivo, "%s %s %ld %ld %lf %lf %s", cuentas[cuentas_leidas].pnombre, cuentas[cuentas_leidas].apellido, 
        &cuentas[cuentas_leidas].num_cuenta, &cuentas[cuentas_leidas].num_tarjeta, &cuentas[cuentas_leidas].saldo, 
        &cuentas[cuentas_leidas].interes, &cuentas[cuentas_leidas].genero)==7)){

        cuentas_leidas++;
    }

    fclose(parchivo);
}

void actualizar_archivo(void){
    parchivo=fopen("archivos/banco.txt", "wt");
    for(int i=0; i<cuentas_leidas; i++){
        fprintf(parchivo, "\n%10s %10s %10ld %10ld %12.2lf %12.2lf %10c", cuentas[i].pnombre, cuentas[i].apellido, 
            cuentas[i].num_cuenta, cuentas[i].num_tarjeta, cuentas[i].saldo, 
            cuentas[i].interes, cuentas[i].genero);
    }
    fclose(parchivo);
}