#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "validaciones.h"
#define QTY 10

int main()
{
    EMovie movies[QTY];
    char seguir='s';
    int opcion;
    movie_initArray(movies,QTY);
    leer_archivo(movies,QTY,"Aun no se ha creado archivo\n");

    do
    {
        opcion=imprimoMenu();
        //val_getUnsignedInt(opcion,imprimoMenu,3,10);
        switch (opcion)
        {
        case 1:
            movie_add(movies,QTY);
            break;
        case 2:
            movie_deleteMovie(movies,QTY);
            break;
        case 3:
            movie_modifyMovies(movies,QTY,"\nNo hay peliculas cargadas");
            break;
        case 4:
            crear_html(movies,QTY,"No se pudo crear html");
            break;
        case 5:
            seguir = 'n';
            break;
        default:
            printf("\nOpcion Incorrecta. Ingrese una opcion del 1 al 3 y 4 para salir");
            break;
        }
    }
    while(seguir!='n');
    return 0;
}
