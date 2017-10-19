#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pantallas.h"
#include "validar.h"


/** \brief initArray inicializa los campos de la esctructura
 * \param array recibido por referencia
 * \param longitud del array
 * \return 0 OK  o -1 error
 *
 */

int pantallas_initArray (sPantallas* arrayPantallas, int longitud)
{
    int retorno = -1;
    int i;
    if(arrayPantallas != NULL && longitud > 0)
    {
        for(i=0; i<longitud ; i++)
        {
            arrayPantallas[i].estado = PANTALLAS_SINCARGAR;
            retorno=0;
        }

    }
    return retorno;
}

//************************************************************************************************************************

/** \brief genera un id autoincrementable
 * \return retorna idAutoincrementable
 */

static int idAutoincrementable = -1;

int pantallas_generarProximoId (void)
{
    idAutoincrementable++;
    return idAutoincrementable;
}

//************************************************************************************************************************

/** \brief cargaPantalla realiza la carga de datos
 * \param arrayPantalla array recibido por parametro
 * \param longitud del array
 * \return 0 si se realizo la carga correctamente o -1 si no se pudo
 *
 */
int pantallas_cargarPantallas (sPantallas* arrayPantallas,int longitud)
{
    int retorno = -1;
    int i;
    int index;
    char bNombre[51];
    char bDireccion[100];
    char bPrecio[10];
    char auxTipo[5];
    int flagTipoPantalla=0;
    int contadorIntentos=0;


    if(arrayPantallas != NULL && longitud >= 0)
    {
        for(i=0; i<longitud; i++)
        {
            if(arrayPantallas[i].estado == PANTALLAS_SINCARGAR)
            {
                index = i;
                break;
            }
        }

        if(val_getAlfanumericoConSignos(bNombre,"\nIngrese el nombre de la pantalla: ","\nError, solo puede ingresar letras: ",3,51)==0)
        {
            if(val_getAlfanumericoConSignos(bDireccion, "\nIngrese la direccion: ",
                                            "\nError, solo puede ingresar letras, numeros y algunos signos: ",3,100)== 0)
            {
                if(val_getFloat(bPrecio,"\nIngrese el precio  por dia: ","\nError, formato valido numeros y 1 punto. ",3,10)==0)
                {
                    do
                    {
                        val_getUnsignedInt(auxTipo,"\n1- Led.\n2- LCD.\nIngrese el tipo de pantalla: ","\nTipo de pantalla invalido. ",3,5);
                        switch(atoi(auxTipo))
                        {
                        case 1:
                            arrayPantallas[index].tipo=PANTALLAS_LCD;
                            flagTipoPantalla=1;
                            break;
                        case 2:
                            arrayPantallas[index].tipo=PANTALLAS_LED;
                            flagTipoPantalla=1;
                            break;
                        }
                        contadorIntentos++;
                    }
                    while(flagTipoPantalla==0 && contadorIntentos<3);
                }
                if(flagTipoPantalla==1)
                {
                    arrayPantallas[index].estado = PANTALLAS_LIBRE;
                    strncpy(arrayPantallas[index].nombre,bNombre,51);
                    strncpy(arrayPantallas[index].direccion,bDireccion,100);
                    arrayPantallas[index].precioPorDia=atof(bPrecio);
                    arrayPantallas[index].idPantalla = pantallas_generarProximoId();

                    retorno = 0;
                }


            }
        }
    }
    return retorno;
}

//************************************************************************************************************************

/** \brief recorre array e imprime por pantalla todas las cargas realizas y con estado LIBRE
 *
 * \param array recibido por referencia
 * \param longitud del array
 * \param mensaje de error, si no hay pantallas cargadas
 * \return 0 si se realizo la carga correctamente o -1 si no se pudo
 *
 */

int pantallas_listarPantallas (sPantallas* arrayPantallas, int longitud,char* mensajeError)
{
    int i;
    int retorno=-1;
    if(arrayPantallas!=NULL && longitud>=0)
    {
        for(i=0; i<longitud; i++)
        {
            if(arrayPantallas[i].estado==PANTALLAS_LIBRE)
            {
                printf("\nID: %d - Tipo: %d - Nombre: %s - Direccion: %s -  Precio: %.2f",
                       arrayPantallas[i].idPantalla,arrayPantallas[i].tipo,arrayPantallas[i].nombre,
                       arrayPantallas[i].direccion,arrayPantallas[i].precioPorDia);
                retorno=0;
            }
        }
        if(retorno==-1)
        {
            printf("%s",mensajeError);
        }
    }
    return retorno;
}

//************************************************************************************************************************

/** \brief recorre array y verifica si hay pantallas cargadas
 * \param array recibido por referencia
 * \param longitud del array
 * \return 0 si se realizo la carga correctamente o -1 si no se pudo
 *
 */

int pantallas_hayPantallasCargadas(sPantallas* arrayPantalla,int longitud)
{
    int i;
    int retorno=-1;

    if(arrayPantalla!=NULL && longitud>0)
    {
        for(i=0; i<longitud; i++)
        {
            if(arrayPantalla[i].estado==PANTALLAS_LIBRE)
                retorno=0;
        }
    }
    return retorno;
}

//************************************************************************************************************************

/** \brief recorre array busca indice utilizando un id
 *
 * \param array recibido por referencia
 * \param longitud del array
 * \param id recibido por parametro para buscar indice
 * \param mensaje para el usuario
 * \return 0 OK  o -1 error
 *
 */

int pantallas_buscarIndicePorId (sPantallas* arrayPantallas, int longitud, int id, char* mensaje)
{
    int retorno = -1;
    int i;

    if(arrayPantallas != NULL && longitud > 0 && id >= 0)
    {
        for(i=0; i<longitud ; i++)
        {
            if(arrayPantallas[i].estado == PANTALLAS_LIBRE)
            {
                if(id == arrayPantallas[i].idPantalla)
                {
                    retorno = i;
                    break;
                }
            }
        }
        if(retorno == -1)
        {
            printf("%s", mensaje);
        }
    }
    return retorno;
}

//************************************************************************************************************************

/** \brief recorre array para modificar campos de la estructura
 *
 * \param array recibido por referencia
 * \param longitud del array
 * \param mensaje de error, si no se han cargado pantallas
 * \return 0 OK  o -1 error
 *
 */
int pantallas_modificarPantallas (sPantallas* arrayPantallas, int longitud,char* mensajeError)
{
    int retorno = -1;
    int indice;
    char bNombre[51];
    char bDireccion[100];
    char bPrecio[10];
    int idAux;
    char buffer[10];
    char auxTipo[5];
    int flagTipoPantalla=0;
    int contadorIntentos=0;


    if(arrayPantallas!=NULL && longitud>0)
    {
        if(pantallas_hayPantallasCargadas(arrayPantallas,longitud)==0)
        {
            val_getUnsignedInt(buffer,"Ingrese el ID de la pantalla a modificar", "El ID no se encontro",3,10);
            idAux = atoi(buffer);

            indice = pantallas_buscarIndicePorId(arrayPantallas,longitud,idAux,"El id no se encontro");

            if(indice != -1)
            {
                if(val_getAlfanumericoConSignos(bNombre,"\nIngrese el nombre de la pantalla: ","\nError, solo puede ingresar letras: ",3,51)==0)
                {
                    if(val_getAlfanumericoConSignos(bDireccion, "\nIngrese la direccion: ",
                                                    "\nError, solo puede ingresar letras, numeros y algunos signos: ",3,100)== 0)
                    {
                        if(val_getFloat(bPrecio,"\nIngrese el precio: ","\nError. Solo numeros y 1 punto: ",3,10)==0)
                        {
                            do
                            {
                                val_getUnsignedInt(auxTipo,"\n1- Led.\n2- LCD.\n\nIngrese el tipo de pantalla: ","\nTipo de pantalla invalido. ",3,5);
                                switch(atoi(auxTipo))
                                {
                                case 1:
                                    arrayPantallas[indice].tipo=PANTALLAS_LCD;
                                    flagTipoPantalla=1;
                                    break;
                                case 2:
                                    arrayPantallas[indice].tipo=PANTALLAS_LED;
                                    flagTipoPantalla=1;
                                    break;
                                }
                                contadorIntentos++;
                            }
                            while(flagTipoPantalla==0 && contadorIntentos<3);

                            strncpy(arrayPantallas[indice].nombre,bNombre,51);
                            strncpy(arrayPantallas[indice].direccion,bDireccion,100);
                            arrayPantallas[indice].precioPorDia=atof(bPrecio);
                            arrayPantallas[indice].tipo=atoi(auxTipo);
                            retorno = 0;
                        }
                    }

                }
            }
        }
        else
        {
            printf("%s",mensajeError);
        }
    }
    return retorno;
}

//************************************************************************************************************************

/** \brief recorre array para hacer una baja logica a un elemento del array
 *
 * \param array recibido por referencia
 * \param longitud del array
 * \return 0 OK  o -1 error
 *
 */

int pantallas_darDeBajaPantalla (sPantallas* arrayPantallas, int longitud)
{
    int retorno = -1;
    int idAux;
    char buffer[10];
    int indice;


    val_getUnsignedInt(buffer,"\nIngrese el ID para dar de baja: ", "\nEl ID no se encontro",3,10);
    idAux = atoi(buffer);

    indice = pantallas_buscarIndicePorId(arrayPantallas,longitud,idAux,"No se encontro el ID");

    if(indice != -1)
    {
        arrayPantallas[indice].estado = PANTALLAS_SINCARGAR;
        retorno = 0;

    }
    return retorno;
}

//************************************************************************************************************************
