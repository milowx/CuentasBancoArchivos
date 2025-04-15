//funciones que manipulan informacion del archivo
#include "linker.h"

void transferir(void){
    int ncuenta_origen, ncuenta_destino, icuenta_origen, icuenta_destino, num_tranx;
    char respuesta;
    double cantidad;

    do{
        printf("\n\tCUENTA ORIGEN:");
        validar_cuenta(&ncuenta_origen);
        printf("\n\tCUENTA DESTINO:");
        validar_cuenta(&ncuenta_destino);

        icuenta_origen = buscar(ncuenta_origen);
        icuenta_destino = buscar(ncuenta_destino);
        if((icuenta_destino==-1) || (icuenta_origen==-1)){
            printf("\n\tCuentas no encontradas!");    
        }else{
            if(cuentas[icuenta_origen].saldo<=0){
                printf("\n\tSaldo No Disponible!");
                mostrar_una_cuenta(icuenta_origen);
            }else{
                printf("\n\tCUENTA ORIGEN");
                mostrar_una_cuenta(icuenta_origen);
                printf("\n\tCUENTA DESTINO");
                mostrar_una_cuenta(icuenta_destino);
                do{
                    printf("\n\tIngrese la cantidad a transferir a la cuenta destino: ");
                    scanf("%lf", &cantidad);
                    if(cantidad<=0){
                        printf("\n\t\aERROR: Ingrese un numero positivo.\n\t");
                    }else if(cantidad>cuentas[icuenta_origen].saldo){
                        printf("\n\t\aERROR: La cantidad excede el saldo disponible.\n\t");
                    }
                }while(cantidad<=0 || cantidad>cuentas[icuenta_origen].saldo);

                cuentas[icuenta_origen].saldo-=cantidad;
                cuentas[icuenta_destino].saldo+=cantidad;
                printf("\n\tTransferencia exitosa de: L.%.2lf", cantidad);
                printf("\n\tCUENTA ORIGEN");
                mostrar_una_cuenta(icuenta_origen);
                printf("\n\tCUENTA DESTINO");
                mostrar_una_cuenta(icuenta_destino);
            }
        }

        num_tranx=10000000+rand()%99999999;
        printf("\n\tNUMERO DE TRANSACCION: %d", num_tranx);

        snprintf(MENSAJE, sizeof(MENSAJE), "[WRITE|TRANSF] TRANSFERENCIA DE: %.2lf [O]%d => [D]%d. NUMERO DE TRANSACCION:[%d]", cantidad, cuentas[icuenta_origen].num_cuenta, cuentas[icuenta_destino].num_cuenta, num_tranx);
        mensaje_log(MENSAJE);

        printf("\n\tDesea realilzar otra transaccion?[S/N]: ");
        validar_char(&respuesta, 'S', 'N');
    }while(respuesta=='S');
    actualizar_archivo();
}

void borrar(void){
    char respuesta;
    int indice_cuenta, num;

    do{
        printf("\n\tBORRAR CUENTAS");
        validar_cuenta(&num);
        indice_cuenta=buscar(num);

        if(indice_cuenta==-1){
            printf("\n\tCuenta No Encontrada");
        }else{
            printf("\n\n\tCuenta Eliminada!");
            mostrar_una_cuenta(indice_cuenta);
            snprintf(MENSAJE, sizeof(MENSAJE), "[WRITE|DELETE]Cuenta eliminida |%lu|", cuentas[indice_cuenta].num_cuenta);
            mensaje_log(MENSAJE);
            for(int j=indice_cuenta; j<cuentas_leidas-1;j++){
                cuentas[j]=cuentas[j+1];
            }
            cuentas_leidas--;
        }

        printf("\n\tDesea borrar otra cuenta?[S/N]: ");
        validar_char(&respuesta, 'S', 'N');
    }while(respuesta=='S');

    actualizar_archivo();
}

void ingresar(void){
    char respuesta;

    parchivo=fopen("archivos/banco.txt", "at");
    do{
        printf("\n\tINGRESANDO CUENTA #%d", cuentas_leidas+1);
        printf("\n\tIngrese el primer nombre del titular de la cuenta: ");
        scanf("%s", cuentas[cuentas_leidas].pnombre);

        printf("\n\tIngrese el apellido del titular de la cuenta: ");
        scanf("%s", cuentas[cuentas_leidas].apellido);

        printf("\n\tIngrese el genero del titular de la cuenta[M/F]: ");
        validar_char(&cuentas[cuentas_leidas].genero, 'M', 'F');

        printf("\n\tIngrese el numero de cuenta: ");
        validar_int(&cuentas[cuentas_leidas].num_cuenta, 10000000);

        printf("\n\tIngrese el numero de tarjeta: ");
        validar_int(&cuentas[cuentas_leidas].num_tarjeta, 10000000);

        printf("\n\tIngrese el saldo de la cuenta: ");
        scanf("%lf", &cuentas[cuentas_leidas].saldo);

        printf("\n\tIngrese el interes de la cuenta: ");
        validar_fl(&cuentas[cuentas_leidas].interes, 0);

        fprintf(parchivo, "\n%10s %10s %10ld %10ld %12.2lf %12.2lf %10c", cuentas[cuentas_leidas].pnombre, cuentas[cuentas_leidas].apellido, 
            cuentas[cuentas_leidas].num_cuenta, cuentas[cuentas_leidas].num_tarjeta, cuentas[cuentas_leidas].saldo, 
            cuentas[cuentas_leidas].interes, cuentas[cuentas_leidas].genero);
        snprintf(MENSAJE, sizeof(MENSAJE), "[WRITE|NEW]Nueva cuenta #%d ingresada |acc:%lu|", cuentas_leidas, cuentas[cuentas_leidas].num_cuenta);
        mensaje_log(MENSAJE);
        cuentas_leidas++;


        printf("\n\tDesea Ingresar Una Nueva Cuenta?[S/N]: ");
        validar_char(&respuesta, 'S', 'N');
    }while(respuesta=='S');

    fclose(parchivo);
}

void ordenar(int modo){
    Cuenta cuenta_actual;
    bool swap;

    switch(modo){
        case 1:
            for(int i=0; i<cuentas_leidas; i++){
                swap=false;
                for(int j=0; j<cuentas_leidas-1-i; j++){
                    if(cuentas[j].num_tarjeta>cuentas[j+1].num_tarjeta){
                        cuenta_actual=cuentas[j];
                        cuentas[j]=cuentas[j+1];
                        cuentas[j+1]=cuenta_actual;
                        swap=true;
                    }
                }
                if(!swap){
                    break;
                }
            }
            mensaje_log("[WRITE|SORT] Archivo ordenado por NUMERO de TARJETA.");
            break;
        case 2:
            for(int i=0; i<cuentas_leidas; i++){
                swap=false;
                for(int j=0; j<cuentas_leidas-1-i; j++){
                    if(cuentas[j].num_cuenta>cuentas[j+1].num_cuenta){
                        cuenta_actual=cuentas[j];
                        cuentas[j]=cuentas[j+1];
                        cuentas[j+1]=cuenta_actual;
                        swap=true;
                    }
                }
                if(!swap){
                    break;
                }
            }
            mensaje_log("[WRITE|SORT] Archivo ordenado por NUMERO de CUENTA.");
            break;
        case 3:
            for(int i=0; i<cuentas_leidas; i++){
                swap=false;
                for(int j=0; j<cuentas_leidas-1-i; j++){
                    if(cuentas[j].saldo>cuentas[j+1].saldo){
                        cuenta_actual=cuentas[j];
                        cuentas[j]=cuentas[j+1];
                        cuentas[j+1]=cuenta_actual;
                        swap=true;
                    }
                }
                if(!swap){
                    break;
                }
            }
            mensaje_log("[WRITE|SORT] Archivo ordenado por SALDO.");
            break;
        default:
            break;
    }
    actualizar_archivo();
}