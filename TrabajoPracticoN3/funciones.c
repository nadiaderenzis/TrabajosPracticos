#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "validaciones.h"

/** \brief imprime menu y toma valor ingresado por el usuario
 *
 * \param
 * \param
 * \return retorna valor ingresado por el usuario
 *
 */
int imprimoMenu(void)
{
    char opcion[10];
    printf("MENU");
    printf("\n\n1- Agregar pelicula\n");
    printf("2- Borrar pelicula\n");
    printf("3- Modificar pelicula\n");
    printf("4- Generar pagina web\n");
    printf("5- Salir\n\n");
    val_getUnsignedInt(opcion,"\nELECCION: ","Opcion invalida, Ingrese un valor valido:  ",3,10);

    return atoi(opcion);
}
/************************************************************************************************************************/

/** \brief lee archivo de datos
 *
 * \param arrayMovie, array de la estructira recibida por referencia
 * \param lenght, longitud del array
 * \param mensajeError mensaje al usuario
 * \return 0 OK  o -1 error
 *
 */
int leer_archivo (EMovie* arrayMovie, int lenght, char* mensajeError)
{
    FILE *fmovie;
    int cantidadLeida;

    fmovie=fopen("datos","r");
    if(fmovie!=NULL)
    {
        cantidadLeida=fread(arrayMovie,sizeof(EMovie),lenght,fmovie);
        if(cantidadLeida==1)
        {
            printf("ok");
        }
    }
    else
    {
        printf("%s",mensajeError);
    }
    fclose(fmovie);
    return 0;
}
/************************************************************************************************************************/

/** \brief escribe archivo de datos
 *
 * \param arrayMovie, array de la estructira recibida por referencia
 * \param lenght, longitud del array
 * \param mensajeError mensaje al usuario
 * \return 0 OK  o -1 error
 *
 */
int escribir_archivo(EMovie* arrayMovie, int lenght, char* mensajeError)
{
    FILE *fmovie;
    int cantidadEscrita;

    fmovie=fopen("datos","w");
    if(fmovie!=NULL)
    {
        cantidadEscrita=fwrite(arrayMovie,sizeof(EMovie),lenght,fmovie);
        if(cantidadEscrita==1)
        {
            printf("ok");
        }
    }
    else
    {
        printf("%s",mensajeError);
    }
    fclose(fmovie);
    return 0;
}

/************************************************************************************************************************/
/** \brief initArray inicializa los campos de la esctructura
 * \param array recibido por referencia
 * \param lenght, longitud del array
 * \return 0 OK  o -1 error
 *
 */
int movie_initArray (EMovie* arrayMovie, int lenght)
{
    int retorno = -1;
    int i;
    if(arrayMovie != NULL && lenght > 0)
    {
        for(i=0; i<lenght; i++)
        {
            arrayMovie[i].estado = MOVIE_FREE;
            retorno=0;
        }

    }
    return retorno;
}
/************************************************************************************************************************/

/** \brief genera un id autoincrementable
 * \return retorna idAutoincrementable
 */

static int idAutoincrementable = -1;

int movie_generarProximoId (void)
{
    idAutoincrementable++;
    return idAutoincrementable;
}

//************************************************************************************************************************

/** \brief cargaPelicula realiza la carga de datos
 * \param arrayPantalla array recibido por parametro
 * \param longitud del array
 * \return 0 si se realizo la carga correctamente o -1 si no se pudo
 *
 */

int movie_add (EMovie* arrayMovie, int lenght)
{
    int retorno=-1;
    int i, index;
    char auxTitulo[20];
    char auxGenero[5];
    char auxDuracion[10];
    char auxDescripcion[50];
    char auxPuntaje[10];
    char auxLink[50];
    int contadorIntentos;
    int flagGenero;

    if(arrayMovie != NULL && lenght >= 0)
    {
        for(i=0; i<lenght; i++)
        {
            if(arrayMovie[i].estado == MOVIE_FREE)
            {
                index = i;
                break;
            }
        }

        if(val_getAlfanumerico(auxTitulo,"\nIngrese el nombre de la pelicula: ","\nError en el formato del titulo",3,20)==0)
        {
            do
            {
                val_getUnsignedInt(auxGenero,"\n1-Suspenso\n2-Drama\n3-Sci-fi\n4-Comedia\n\nIngrese el genero: ","\nGenero invalido ",3,5);
                switch(atoi(auxGenero))
                {
                case 1:
                    arrayMovie[index].genero=GENERO_SUSPENSO;
                    flagGenero=1;
                    break;
                case 2:
                    arrayMovie[index].genero=GENERO_DRAMA;
                    flagGenero=1;
                    break;
                case 3:
                    arrayMovie[index].genero=GENERO_SCIFI;
                    flagGenero=1;
                    break;
                case 4:
                    arrayMovie[index].genero=GENERO_COMEDIA;
                    flagGenero=1;
                    break;
                }
                contadorIntentos++;
            }
            while(contadorIntentos<3 && flagGenero==0);
            if(flagGenero==1)
            {
                if(val_getUnsignedInt(auxDuracion,"\nIngrese duracion: ","\nIngrese solo numeros: ",3,10)==0)
                {
                    if(val_getAlfanumerico(auxDescripcion,"\nIngrese descripcion: ","\nFormato erroneo: ",3,50)==0)
                    {
                        if(val_getUnsignedInt(auxPuntaje,"\nIngrese puntaje: ","\nIngrese solo nros: ",3,10)==0)
                        {
                            if(val_getAlfanumerico(auxLink,"Ingrese link: ","\nError link: ",3,50)==0)
                            {
                                arrayMovie[index].estado = MOVIE_NOTFREE;
                                strncpy(arrayMovie[index].titulo,auxTitulo,20);
                                arrayMovie[index].duracion=atoi(auxDuracion);
                                strncpy(arrayMovie[index].descripcion,auxDescripcion,50);
                                arrayMovie[index].puntaje=atoi(auxPuntaje);
                                strncpy(arrayMovie[index].linkImagen,auxLink,50);
                                arrayMovie[index].idMovies=movie_generarProximoId();
                                escribir_archivo(arrayMovie,lenght,"Error en la carga de datos");
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

/** \brief recorre array busca indice utilizando un id
 *
 * \param arrayMovie, array recibido por referencia
 * \param lenght, longitud del array
 * \param id recibido por parametro para buscar indice
 * \param mensaje para el usuario
 * \return 0 OK  o -1 error
 *
 */

int movie_buscarIndicePorId (EMovie* arrayMovie, int lenght, int id, char* mensaje)
{
    int retorno = -1;
    int i;

    if(arrayMovie != NULL && lenght > 0 && id >= 0)
    {
        for(i=0; i<lenght ; i++)
        {
            if(arrayMovie[i].estado == MOVIE_NOTFREE)
            {
                if(id == arrayMovie[i].idMovies)
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

/** \brief recorre array y verifica si hay pantallas cargadas
 * \param array recibido por referencia
 * \param longitud del array
 * \return 0 si se realizo la carga correctamente o -1 si no se pudo
 *
 */

int movie_hayPeliculasCargadas(EMovie* arrayMovie,int lenght)
{
    int i;
    int retorno=-1;

    if(arrayMovie!=NULL && lenght>0)
    {
        for(i=0; i<lenght; i++)
        {
            if(arrayMovie[i].estado==MOVIE_NOTFREE)
                retorno=0;
        }
    }
    return retorno;
}
/************************************************************************************************************************/
/** \brief recorre array para modificar campos de la estructura
 *
 * \param arrayMovie, array recibido por referencia
 * \param lenght, longitud del array
 * \param mensaje de error, si no se han cargado peliculas
 * \return 0 OK  o -1 error
 *
 */
int movie_modifyMovies (EMovie* arrayMovie, int lenght,char* mensajeError)
{
    int retorno = -1;
    char auxTitulo[20];
    char auxGenero[5];
    char auxDuracion[10];
    char auxDescripcion[50];
    char auxPuntaje[10];
    char auxLink[50];
    int contadorIntentos;
    int flagGenero;
    int indice;
    int idAux;
    char buffer[10];


    if(arrayMovie!=NULL && lenght>0)
    {
        if(movie_hayPeliculasCargadas(arrayMovie,lenght)==0)
        {
            val_getUnsignedInt(buffer,"Ingrese el ID de la pelicula a modificar: ", "\nEl ID no se encontro, Ingrese nuevamente el ID: ",3,10);
            idAux = atoi(buffer);

            indice = movie_buscarIndicePorId(arrayMovie,lenght,idAux,"\nEl id no se encontro");

            if(indice != -1)
            {
                if(val_getAlfanumerico(auxTitulo,"\nIngrese el nombre de la pelicula: ","\nError en el formato del titulo",3,20)==0)
                {
                    do
                    {
                        val_getUnsignedInt(auxGenero,"\n1-Suspenso\n2-Drama\n3-Sci-fi\n4-Comedia\n\nIngrese el genero: ","\nGenero invalido ",3,5);
                        switch(atoi(auxGenero))
                        {
                        case 1:
                            arrayMovie[indice].genero=GENERO_SUSPENSO;
                            flagGenero=1;
                            break;
                        case 2:
                            arrayMovie[indice].genero=GENERO_DRAMA;
                            flagGenero=1;
                            break;
                        case 3:
                            arrayMovie[indice].genero=GENERO_SCIFI;
                            flagGenero=1;
                            break;
                        case 4:
                            arrayMovie[indice].genero=GENERO_COMEDIA;
                            flagGenero=1;
                            break;
                        }
                        contadorIntentos++;
                    }
                    while(contadorIntentos<3 && flagGenero==0);
                    if(flagGenero==1)
                    {
                        if(val_getUnsignedInt(auxDuracion,"\nIngrese duracion: ","\nIngrese solo numeros: ",3,10)==0)
                        {
                            if(val_getAlfanumerico(auxDescripcion,"\nIngrese descripcion: ","\nFormato erroneo: ",3,50)==0)
                            {
                                if(val_getUnsignedInt(auxPuntaje,"\nIngrese puntaje: ","\nIngrese solo nros: ",3,10)==0)
                                {
                                    if(val_getAlfanumerico(auxLink,"Ingrese link: ","\nError link",3,50)==0)
                                    {
                                        strncpy(arrayMovie[indice].titulo,auxTitulo,20);
                                        arrayMovie[indice].duracion=atoi(auxDuracion);
                                        strncpy(arrayMovie[indice].descripcion,auxDescripcion,50);
                                        arrayMovie[indice].puntaje=atoi(auxPuntaje);
                                        strncpy(arrayMovie[indice].linkImagen,auxLink,50);
                                        escribir_archivo(arrayMovie,lenght,"Error en la carga de datos");
                                        retorno = 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }else
        {
            printf("%s",mensajeError);
        }
    }
    return retorno;
}

/************************************************************************************************************************/
/** \brief recorre array para hacer una baja logica a un elemento del array
 *
 * \param arrayMovie, array recibido por referencia
 * \param lenght, longitud del array
 * \return 0 OK  o -1 error
 *
 */
int movie_deleteMovie (EMovie* arrayMovie, int lenght)
{
    int retorno = -1;
    int idAux;
    char buffer[10];
    int indice;


    val_getUnsignedInt(buffer,"\nIngrese el ID para dar de baja: ", "\nEl ID no se encontro ",3,10);
    idAux = atoi(buffer);

    indice = movie_buscarIndicePorId(arrayMovie,lenght,idAux,"\nNo se encontro el ID");

    if(indice != -1)
    {
        arrayMovie[indice].estado = MOVIE_FREE;
        escribir_archivo(arrayMovie,lenght,"Error en la carga de datos");
        retorno = 0;

    }
    return retorno;
}
/************************************************************************************************************************/

/** \brief genera un  archivo html
 *
 * \param arrayMovie, array de la estructura recibida por referencia
 * \param lenght, longitud del array
 * \param mensajeError mensaje al usuario
 * \return 0 OK  o -1 error
 *
 */
int crear_html(EMovie* arrayMovie, int lenght, char* mensajeError)
{
    FILE *fmovie;
    FILE *fHeader;
    FILE *fBody;
    int i;
    char header[1300];
    char body[1500];

    fmovie=fopen("index.html","w");

    if(fmovie!=NULL)
    {
        fHeader=fopen("Header.txt","r");
        fscanf(fHeader,"%s",header);
        fclose(fHeader);
        fprintf(fmovie,"%s",header);

        fBody=fopen("Body.txt","r");
        fread(body,sizeof(char),1500,fBody);
        fclose(fBody);

        for(i=0; i<lenght; i++)
        {
            if(arrayMovie[i].estado==MOVIE_NOTFREE)
            {
                fprintf(fmovie,body,(arrayMovie+i)->linkImagen, (arrayMovie+i)->titulo, (arrayMovie+i)->genero,
                        (arrayMovie+i)->puntaje, (arrayMovie+i)->duracion, (arrayMovie+i)->descripcion);
            }
        }
    }
    else
    {
        printf("%s",mensajeError);
    }

    fclose(fmovie);
    return 0;
}
