#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pantallas.h"
#include "contrataciones.h"
#include "validar.h"
#include "informes.h"

/** \brief initArray inicializa el campo ESTADO de la estructura
 * \param array recibido por referencia
 * \param longitud del array
 * \return 0 OK  o -1 error
 *
 */

int contrataciones_initArray (sContrataciones* arrayContrataciones, int longitud)
{
    int retorno = -1;
    int i;

    if(arrayContrataciones != NULL && longitud > 0)
    {
        for(i=0; i<longitud ; i++)
        {
            arrayContrataciones[i].estado = CONTRATACIONES_LIBRE;
            retorno = 0;
        }
    }
    return retorno;
}

//************************************************************************************************************************

/** \brief genera un id autoincrementable
 * \return retorna idAutoincrementable
 */

static int idAutoincrementable = -1;

int contrataciones_generarProximoIndice (void)
{
    idAutoincrementable++;
    return idAutoincrementable;
}

//************************************************************************************************************************

/** \brief recorre array y asigna un CUIT a pantallas precargadas
 *
 * \param array recibido por referencia
 * \param array recibido por referencia
 * \param longitudPantalla del array
 * \param longitudContrataciones del array
 * \return 0 OK  o -1 error
 *
 */

int contrataciones_contratarPublicidad (sPantallas* arrayPantalla,sContrataciones* arrayContrataciones,int longitudPantalla,
                                        int longitudContrataciones)
{
    int retorno = -1;
    int idAux;
    char buffer[10];
    int indicePantalla;
    int i;
    int indiceContrataciones;
    char bCuit[15];
    char bDias[50];
    char bnombreArchivo[50];


    if((arrayPantalla != NULL && arrayContrataciones != NULL) && (longitudPantalla >= 0 && longitudContrataciones  >= 0))
    {
        if(pantallas_listarPantallas(arrayPantalla,longitudPantalla,"No se han cargado pantallas")==0)
        {
            val_getUnsignedInt(buffer,"\n\nIngrese el id de la pantalla: ", "\nIngrese solo numeros",3,10);
            idAux=atoi(buffer);
            indicePantalla=pantallas_buscarIndicePorId(arrayPantalla,longitudPantalla,idAux,"No se encontro id");

            if(indicePantalla!=-1)
            {
                for(i=0; i<longitudContrataciones; i++)
                {
                    if(arrayContrataciones[i].estado == CONTRATACIONES_LIBRE)
                    {
                        indiceContrataciones = i;
                        break;
                    }
                }

                if(val_getCuit(bCuit,"\nIngrese el CUIT: ","\nError, el formato es xx-xxxxxxxx-x: ",3,15)==0)
                {
                    if(val_getUnsignedInt(bDias, "\nIngresa la cantidad de dias a alquilar: ", "\nError, puede ingresar numeros: ",3,50)== 0)
                    {
                        if(val_getAlfanumericoConSignos(bnombreArchivo,"\nIngrese el nombre del archivo: ","\nError, solo puede ingresar letras: ",3,50)==0)
                        {
                            {
                                strncpy(arrayContrataciones[indiceContrataciones].cuit, bCuit, 15);
                                arrayContrataciones[indiceContrataciones].diasPublicacion=atoi(bDias);
                                strncpy(arrayContrataciones[indiceContrataciones].nombreArchivoVideo,bnombreArchivo, 50);
                                arrayContrataciones[indiceContrataciones].idCliente = contrataciones_generarProximoIndice();
                                arrayContrataciones[indiceContrataciones].estado = CONTRATACIONES_ENCURSO;
                                arrayContrataciones[indiceContrataciones].idPantalla = idAux;
                                arrayPantalla[indicePantalla].estado=PANTALLAS_CONTRATADA;
                                retorno = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    return retorno;
}

//************************************************************************************************************************

/** \brief recorre array de
 *
 * \param array recibido por referencia
 * \param array recibido por referencia
 * \param longitud del array
 * \param longit del array
 * \param mensaje1 y mensaje2 de error para el usuario
 * \return 0 OK  o -1 error
 *
 */

int contrataciones_modificarContratacion (sPantallas* arrayPantallas,sContrataciones* arrayContrataciones,int longitudPantalla,
        int longitudContrataciones)
{
    int retorno = -1;
    int idAux;
    char buffer[10];
    int indicePantalla;
    int i,j;
    int indiceContrataciones;
    char auxCuit[15];
    char bDias[10];


    if((arrayPantallas != NULL && arrayContrataciones != NULL) && (longitudPantalla > 0 && longitudContrataciones  > 0))
    {
        if(val_getCuit(auxCuit,"\nIngrese el CUIT: ","\nError, el formato es xx-xxxxxxxx-x: ",3,15)==0)
        {
            for(i=0; i<longitudContrataciones; i++)
            {
                if(strcmp(arrayContrataciones[i].cuit, auxCuit) == 0)
                {
                    indiceContrataciones=i;
                    for(j=0; j<longitudPantalla; j++)
                    {
                        if(arrayContrataciones[i].idPantalla==arrayPantallas[j].idPantalla)
                        {
                            indicePantalla=j;
                            printf("\nID: %d - Tipo: %d - Nombre: %s - Direccion: %s -  Precio: %.2f",
                                   arrayPantallas[indicePantalla].idPantalla,
                                   arrayPantallas[indicePantalla].tipo,
                                   arrayPantallas[indicePantalla].nombre,
                                   arrayPantallas[indicePantalla].direccion,
                                   arrayPantallas[indicePantalla].precioPorDia);
                            retorno=0;
                        }

                    }
                }

            }
        }

        if(val_getUnsignedInt(buffer,"\n\nIngrese el id de la pantalla a modificar: ", "\nIngrese solo numeros",3,10)==0)
        {
            idAux=atoi(buffer);
            for(i=0; i<longitudContrataciones; i++)
            {
                if(arrayContrataciones[i].idPantalla==idAux)
                {
                    if(val_getUnsignedInt(bDias, "\nIngresa la cantidad de dias a alquilar: ", "\nError, puede ingresar numeros: ",3,10)== 0)
                    {
                        arrayContrataciones[indiceContrataciones].diasPublicacion=atoi(bDias);
                        retorno=0;
                    }
                }
            }
        }
    }
    return retorno;
}

//************************************************************************************************************************

/** \brief recorre 2 arrays comparando datos para dar de baja un registro
 *
 * \param array recibido por referencia
 * \param array recibido por referencia
 * \param longitud del array
 * \param longit del array
 * \param mensaje1 y mensaje2 de error para el usuario
 * \return 0 OK  o -1 error
 *
 */

int contrataciones_cancelarContratacion (sPantallas* arrayPantallas,sContrataciones* arrayContrataciones,int longitudPantalla,
        int longitudContrataciones)
{
    int retorno = -1;
    int idAux;
    char buffer[10];
    int indicePantalla;
    int i,j;
    char auxCuit[15];



    if((arrayPantallas != NULL && arrayContrataciones != NULL) && (longitudPantalla > 0 && longitudContrataciones  > 0))
    {
        if(val_getCuit(auxCuit,"\nIngrese el CUIT: ","\nError, el formato es xx-xxxxxxxx-x: ",3,15)==0)
        {
            for(i=0; i<longitudContrataciones; i++)
            {
                if(arrayContrataciones[i].estado==CONTRATACIONES_ENCURSO)
                {
                    if(strcmp(arrayContrataciones[i].cuit, auxCuit) == 0)
                    {
                        for(j=0; j<longitudPantalla; j++)
                        {
                            if(arrayContrataciones[i].idPantalla==arrayPantallas[j].idPantalla)
                            {
                                indicePantalla=j;
                                printf("\nID: %d - Tipo: %d - Nombre: %s - Direccion: %s -  Precio: %.2f",
                                       arrayPantallas[indicePantalla].idPantalla,
                                       arrayPantallas[indicePantalla].tipo,
                                       arrayPantallas[indicePantalla].nombre,
                                       arrayPantallas[indicePantalla].direccion,
                                       arrayPantallas[indicePantalla].precioPorDia);
                                retorno=0;
                            }
                        }
                    }
                }
            }
        }
        if(val_getUnsignedInt(buffer,"\n\nIngrese el id de la pantalla del cual desea cancelar la publicacion: ",
                              "\nIngrese solo numeros",3,10)==0)
        {
            idAux=atoi(buffer);
            for(i=0; i<longitudContrataciones; i++)
            {
                if(arrayContrataciones[i].idPantalla==idAux)
                {
                    arrayContrataciones[i].estado=CONTRATACIONES_FINALIZADA;
                }
            }
            for(i=0;i<longitudContrataciones;i++)
            {
                if(arrayPantallas[i].idPantalla==idAux)
                {
                    arrayPantallas[i].estado=PANTALLAS_LIBRE;
                }
            }
        }
    }
    return retorno;
}

//************************************************************************************************************************

/** \brief recorre 2 arrays comparando datos para dar de baja un registro de forma lógica
 *
 * \param array recibido por referencia
 * \param array recibido por referencia
 * \param longitudPantalla longitud del array
 * \param longitudContrataciones longitud del array
 * \return 0 OK  o -1 error
 *
 */

int contrataciones_facturacion(sPantallas* arrayPantallas,sContrataciones* arrayContrataciones,int longitudPantalla,
                               int longitudContrataciones)
{
    int retorno = -1;
    int indicePantalla;
    int i,j;
    int indiceContrataciones;
    char auxCuit[15];
    float importeApagar;


    if((arrayPantallas != NULL && arrayContrataciones != NULL) && (longitudPantalla > 0 && longitudContrataciones  > 0))
    {
        if(val_getCuit(auxCuit,"\nIngrese el CUIT: ","\nError, el formato es xx-xxxxxxxx-x: ",3,15)==0)
        {
            for(i=0; i<longitudContrataciones; i++)
            {
                if(arrayContrataciones[i].estado!=CONTRATACIONES_LIBRE)
                {
                    if(strcmp(arrayContrataciones[i].cuit, auxCuit) == 0)
                    {
                        indiceContrataciones=i;
                        for(j=0; j<longitudPantalla; j++)
                        {
                            if(arrayContrataciones[i].idPantalla==arrayPantallas[j].idPantalla)
                            {
                                indicePantalla=j;
                                printf("\nEl importe a pagar por la pantalla %d es: %.2f",
                                       arrayPantallas[indicePantalla].idPantalla,
                                       importeApagar=(arrayContrataciones[indiceContrataciones].diasPublicacion*arrayPantallas[indicePantalla].precioPorDia));
                                retorno=0;
                            }
                        }
                    }
                }
            }
        }
    }
    return retorno;
}
//************************************************************************************************************************

/** \brief recorre 2 arrays e imprime los registros que poseen contrataciones, comparando ambos arrays
 *
 * \param array recibido por referencia
 * \param array recibido por referencia
 * \param longitudPantalla, longitud del array
 * \param longitudContratacion, longitud del array
 * \return 0 OK  o -1 error
 *
 */

int contrataciones_listarContrataciones(sPantallas* arrayPantallas,sContrataciones* arrayContrataciones,int longitudPantalla,
                                        int longitudContrataciones)
{
    int retorno = -1;
    int indicePantalla;
    int i,j;
    int indiceContrataciones;
    char auxCuit[15];



    if((arrayPantallas != NULL && arrayContrataciones != NULL) && (longitudPantalla > 0 && longitudContrataciones  > 0))
    {
        if(val_getCuit(auxCuit,"\nIngrese el CUIT: ","\nError, el formato es xx-xxxxxxxx-x: ",3,15)==0)
        {
            for(i=0; i<longitudContrataciones; i++)
            {
                if(arrayContrataciones[i].estado!=CONTRATACIONES_LIBRE)
                {
                    if(strcmp(arrayContrataciones[i].cuit, auxCuit) == 0)
                    {
                        indiceContrataciones=i;
                        for(j=0; j<longitudPantalla; j++)
                        {
                            if(arrayContrataciones[i].idPantalla==arrayPantallas[j].idPantalla)
                            {
                                indicePantalla=j;
                                printf("\nNombre de la pantalla: %s - Nombre del archivo de video: %s - Dias contratados: %d - CUIT: %s",
                                       arrayPantallas[indicePantalla].nombre,
                                       arrayContrataciones[indiceContrataciones].nombreArchivoVideo,
                                       arrayContrataciones[indiceContrataciones].diasPublicacion,
                                       arrayContrataciones[indiceContrataciones].cuit);
                                retorno=0;
                            }
                        }
                    }
                }
            }
        }
    }
    return retorno;
}

//************************************************************************************************************************

/** \brief recorre array e imprime por pantalla los registros cuyo estado es EN_CURSO
 *
 * \param array recibido por referencia
 * \param array recibido por referencia
 * \param longitudPantalla, longitud del array
 * \param longitudContratacion, longitud del array
 * \return 0 OK  o -1 error
 *
 */

int contrataciones_listarContratacionesEnCurso(sPantallas* arrayPantallas,sContrataciones* arrayContrataciones,int longitudPantalla,
        int longitudContrataciones)
{
    int retorno=-1;
    int i;
    int j;
    int indiceContrataciones;
    int indicePantalla;
    float importeApagar;

    if((arrayPantallas != NULL && arrayContrataciones != NULL) && (longitudPantalla > 0 && longitudContrataciones  > 0))
    {
        for(i=0; i<longitudContrataciones; i++)
        {
            if(arrayContrataciones[i].estado==CONTRATACIONES_ENCURSO)
            {
                printf("\nPosicion: %d - ID: %d - CUIT: %s",i,arrayContrataciones[i].idCliente,arrayContrataciones[i].cuit);
                indiceContrataciones=i;
                for(j=0; j<longitudPantalla; j++)
                {
                    if(arrayContrataciones[i].idPantalla==arrayPantallas[j].idPantalla)
                    {
                        indicePantalla=j;
                        printf("\nEl importe a pagar por la pantalla %d es: %.2f",
                               arrayPantallas[indicePantalla].idPantalla,
                               importeApagar=(arrayContrataciones[indiceContrataciones].diasPublicacion*arrayPantallas[indicePantalla].precioPorDia));
                        retorno=0;
                    }
                }
            }
        }
    }
    return retorno;
}
//************************************************************************************************************************
/** \brief recorre array e imprime por pantalla todos los registros cuyo estado es FINALIZADO
 *
 * \param array recibido por referencia
 * \param array recibido por referencia
 * \param longitudPantalla, longitud del array
 * \param longitudContratacion, longitud del array
 * \return 0 OK  o -1 error
 *
 */

int contrataciones_listarContratacionesFinalizadas(sPantallas* arrayPantallas,sContrataciones* arrayContrataciones,int longitudPantalla,
        int longitudContrataciones)
{
    int retorno=-1;
    int i;
    int j;
    int indiceContrataciones;
    int indicePantalla;
    float importeApagar;

    if((arrayPantallas != NULL && arrayContrataciones != NULL) && (longitudPantalla > 0 && longitudContrataciones  > 0))
    {
        for(i=0; i<longitudContrataciones; i++)
        {
            if(arrayContrataciones[i].estado==CONTRATACIONES_FINALIZADA)
            {
                printf("\nPosicion: %d - ID: %d - CUIT: %s",i,arrayContrataciones[i].idCliente,arrayContrataciones[i].cuit);
                indiceContrataciones=i;
                for(j=0; j<longitudPantalla; j++)
                {
                    if(arrayContrataciones[i].idPantalla==arrayPantallas[j].idPantalla)
                    {
                        indicePantalla=j;
                        printf("\nEl importe a pagar por la pantalla %d es: %.2f",
                               arrayPantallas[indicePantalla].idPantalla,
                               importeApagar=(arrayContrataciones[indiceContrataciones].diasPublicacion*arrayPantallas[indicePantalla].precioPorDia));
                        retorno=0;
                    }
                }
            }
        }
    }
    return retorno;
}
//************************************************************************************************************************
