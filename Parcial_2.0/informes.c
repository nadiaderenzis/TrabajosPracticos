#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pantallas.h"
#include "contrataciones.h"
#include "validar.h"
#include "informes.h"

/** \brief recorre el array y lista las contrataciones de cada cliente y el cliente con mayor facturacion
 *
 * \param arrayPantallas array pasado por referencia
 * \param arrayContrataciones array pasado por referencia
 * \param longitudPantalla, longitud del 1er array
 * \param longitudContrataciones, longitud del 2do array
 * \return 0 OK  o -1 error
 *
 */

int informes_clienteContratacionesEimporte(sPantallas* arrayPantallas,sContrataciones* arrayContrataciones,int longitudPantalla,
        int longitudContrataciones)
{
    int i,j;
    int retorno=-1;
    char buffer[5];
    int contadorIntentos;
    float maximo;
    float resultado;
    int clienteMax;


    if((arrayPantallas != NULL && arrayContrataciones != NULL) && (longitudPantalla > 0 && longitudContrataciones  > 0))
    {
        do
        {
            val_getUnsignedInt(buffer,"\n1- Contrataciones en curso.\n2- Contrataciones finalizadas.\nIngrese una opcion: ","\nSolo ingrese 1 o 2. ",3,5);
            switch(atoi(buffer))
            {
            case 1:
                printf("\nContrataciones en curso: \n");
                contrataciones_listarContratacionesEnCurso(arrayPantallas,arrayContrataciones,longitudPantalla,longitudContrataciones);
                break;
            case 2:
                printf("\nContrataciones finalizadas: \n");
                contrataciones_listarContratacionesFinalizadas(arrayPantallas,arrayContrataciones,longitudPantalla,longitudContrataciones);
                break;
            }
            contadorIntentos++;
        }
        while(contadorIntentos<3);

        for(i=0; i<longitudContrataciones; i++)
        {
            for(j=0; j<longitudPantalla; j++)
            {
                if(arrayContrataciones[i].idPantalla==arrayPantallas[j].idPantalla)
                   {
                       resultado=(arrayContrataciones[i].diasPublicacion*arrayPantallas[j].precioPorDia);
                       if(resultado>maximo)
                       {
                           maximo=resultado;
                           clienteMax=i;
                       }
                   }
                }
        }
        printf("\nEl cliente con mas alto importe a facturar es: %s con %.2f",arrayContrataciones[clienteMax].cuit,maximo);
    }
    return retorno;
}

