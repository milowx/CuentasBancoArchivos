#include "linker.h"

void obtener_hora(char* buffer, size_t magn){
    time_t ahora = time(NULL);//regresa momento actual
    struct tm *tmpo = localtime(&ahora);
    /*
    time(NULL) regresa hora exacta en tipo time_t
    localtime(&ahora) agarra el time_t y lo convierte en una estructura de tiempo[year, month, day, hour, minute, second]
    */
   strftime(buffer, magn, "%Y-%m-%d %H:%M:%S", tmpo);//2025-04-08 16:25:40, formato es guardado en el string buffer.
}

void mensaje_log(char* msj){
    FILE* plog = fopen("archivos/log.txt", "at");
    char tiempo_exacto[30];

    if(!plog){
        printf("\n\t\aERROR: No se pudo abrir el archivo de registro.");
    }else{
        obtener_hora(tiempo_exacto, sizeof(tiempo_exacto));//se pasa el string donde se almacena la hora exacta y el tamaño del string
        fprintf(plog, "[%s] --- %s\n", tiempo_exacto, msj);//se imprime el formato yyyy-mm-dd hh:mm:ss y el mensaje proveido a la funcion.
    }
    fclose(plog);
}