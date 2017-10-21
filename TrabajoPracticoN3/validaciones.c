#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "validaciones.h"

#define MAX_INPUT_BUFFER 4096

/** \brief Recibe un buffer y en la ultima posicion coloca un \0
 *
 * \param buffer donde se guarda el string
 * \param tama�o del string
 *
 */

void myFgets(char* buffer, int limite,FILE* archivo)
{
    int i=0;
    fflush(archivo);
    fgets(buffer, limite,archivo);
    buffer[limite-1] = '\0';
    while(buffer[i] != '\0')
    {
        if(buffer[i] == 10)//10 -> LF
        {
            buffer[i] = '\0';
            break;
        }
        i++;
    }
}
/** \brief Valida ingreso de numeros enteros
 *
 * \param destino donde se guarda el string
 * \param mensaje, mensaje para el usuario
 * \param mensajeError mensaje a mostrar en caso de error
 * \param intentos, cantidad de veces antes de mostrar error
 * \param limite, tama�o del string
 * \return 0 OK -1 en caso de error
 *
 */

int val_getUnsignedInt(char* destino, char* mensaje,char* mensajeError,int intentos,int limite)
{
    int retorno = -1;
    char buffer[MAX_INPUT_BUFFER];

    if(destino != NULL && limite > 0 && limite < MAX_INPUT_BUFFER)
    {
        printf(mensaje);
        for( ; intentos>0; intentos--)
        {

            myFgets(buffer, limite,stdin);

            if(val_validarUnsignedInt(buffer) == -1)
            {
                printf(mensajeError);
                continue;
            }
            else
            {
                strncpy(destino,buffer,limite);
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}


/** \brief Valida que solo se ingresen numeros
 *
 * \param buffer donde se guarda el string
 * \return 0 OK -1 en caso de error
 *
 */
int val_validarUnsignedInt(char* buffer)
{
    int i=0;
    int retorno = 0;
    int flagPunto = 0;

    if(buffer[i]=='\0')
        retorno=-1;

    while(buffer[i] != '\0')
    {
        if(buffer[i] < '0' || buffer[i] > '9' )
        {
            retorno = -1;
            break;
        }
        else
        {
            if(buffer[i] == '-' && i != 0)
            {
                retorno = -1;
                break;
            }
            else if(buffer[i] == '.')
            {
                flagPunto++;
                if(flagPunto > 1)
                {
                    retorno = -1;
                    break;
                }
            }
        }
        i++;
    }
    return retorno;
}

/** \brief Valida que solo se ingresen letras
 *
 * \param destino donde se guarda el string
 * \param mensaje, mensaje para el usuario
 * \param mensajeError mensaje a mostrar en caso de error
 * \param intentos, cantidad de veces antes de mostrar error
 * \param limite,tama�o del string
 * \return 0 OK -1 en caso de error
 *
 */

int val_getString(char* destino, char* mensaje,char* mensajeError,int intentos,int limite)
{
    int retorno = -1;
    char buffer[MAX_INPUT_BUFFER];

    if(destino != NULL && limite > 0 && limite < MAX_INPUT_BUFFER)
    {
        printf(mensaje);
        for( ; intentos>0; intentos--)
        {

            myFgets(buffer, limite,stdin);

            if(val_validarString(buffer) == -1)
            {
                printf(mensajeError);
                continue;
            }
            else
            {
                strncpy(destino,buffer,limite);
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}

/** \brief Valida lo ingresado sean solo letras
 * \param buffer donde se guarda el string
 * \return 0 OK -1 en caso de error
 *
 */

int val_validarString(char* buffer)
{
    int i=0;
    int retorno = 0;

    while(buffer[i] != '\0')
    {
        if((buffer[i] < 'a' || buffer[i] > 'z') && (buffer[i] < 'A' || buffer[i] > 'Z') && buffer[i] != ' ')
        {
            retorno = -1;
            break;
        }
        i++;
    }
    return retorno;
}
//*******************************************************************************************************************

/** \brief Toma un string y lo guarda permitiendo letras y numeros
 *
 * \param destino donde se guarda el string
 * \param mensaje, mensaje para el usuario
 * \param mensajeError mensaje a mostrar en caso de error
 * \param intentos, cantidad de veces antes de mostrar error
 * \param limite, tama�o del string
 * \return 0 OK -1 en caso de error
 *
 */

int val_getAlfanumerico(char* destino, char* mensaje, char* mensajeError,int intentos,int limite)
{
    int retorno = -1;
    char buffer[MAX_INPUT_BUFFER];

    if(destino != NULL && limite > 0 && limite < MAX_INPUT_BUFFER)
    {
        printf(mensaje);
        for( ; intentos>0; intentos--)
        {

            myFgets(buffer, limite,stdin);

            if(val_validarAlfanumerico(buffer) == -1)
            {
                printf(mensajeError);
                continue;
            }
            else
            {
                strncpy(destino,buffer,limite);
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}

//*******************************************************************************************************************
/** \brief Valida que solo se ingresen numeros y letras
 *
 * \param buffer donde se guarda el string
 * \return 0 OK -1 en caso de error
 *
 */

int val_validarAlfanumerico(char* buffer)
{
    int i=0;
    int retorno = 0;
    while(buffer[i] != '\0')
    {
        if((buffer[i] < 'a' || buffer[i] > 'z') &&
                (buffer[i] < 'A' || buffer[i] > 'Z') && (buffer[i] < '0' || buffer[i] > '9')&& buffer[i] != ' ')
        {
            retorno = -1;
            break;
        }
        i++;
    }
    return retorno;
}

