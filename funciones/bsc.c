//funciones que ayudan a buscar informacion en el archivo
#include "linker.h"

int buscar(int num){//regresa el indice de la cuenta
    int indice;
    bool encontrado=false;
    for(int i=0;i<cuentas_leidas;i++){
        if((cuentas[i].num_cuenta==num)||(cuentas[i].num_tarjeta==num)){
            indice = i;
            encontrado=true;
            break;
        }
    }

    snprintf(MENSAJE, sizeof(MENSAJE), "[READ|CUENTA] CUENTA BUSCADA: |%d|, ENCONTRADO: |%d|", num, encontrado);
    mensaje_log(MENSAJE);

    if(encontrado){
        return indice;
    }else{
        return -1;
    }
}

void buscar_una_cuenta(void){
    char respuesta;
    int num, indice_cuenta;

    do{
        validar_cuenta(&num);
        indice_cuenta=buscar(num);

        if(indice_cuenta==-1){
            printf("\n\tCuentra no encontrada");
        }else{
            printf("\n\n\tCuenta Encontrada!");
            mostrar_una_cuenta(indice_cuenta);
        }

        printf("\n\tDesea buscar otra cuenta?[S/N]: ");
        validar_char(&respuesta, 'S', 'N');

    }while(respuesta=='S');
}