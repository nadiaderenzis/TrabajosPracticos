#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pantallas.h"
#include "contrataciones.h"
#include "validar.h"
#include "informes.h"

#define MAXPANT 4
#define MAXCONT 5
int main()
{
    sPantallas pantallas[MAXPANT];
    sContrataciones contrataciones[MAXCONT];

    pantallas_initArray(pantallas,MAXPANT);
    contrataciones_initArray(contrataciones,MAXCONT);
    char opcion[10];
    int salir;

    do
    {
        val_getUnsignedInt(opcion,
                           "\n\n1- Alta de pantalla.\n2- Modificar datos de pantalla.\n3- Baja de pantalla.\n4- Contratar una publicidad.\n5- Modificar condiciones de publicacion.\n6- Cancelar contratacion.\n7- Consulta facturacion.\n8- Listar contrataciones.\n9- Listar pantallas\n10- Informar\n0- SALIR\n\nIngrese una opcion: ",
                           "\n\nIngrese una opcion valida.\n",3,10);

        switch(atoi(opcion))
        {
        case 1:
            pantallas_cargarPantallas(pantallas, MAXPANT);
            break;
        case 2:
            pantallas_modificarPantallas(pantallas,MAXPANT,"No hay pantallas cargadas");
            break;
        case 3:
            pantallas_darDeBajaPantalla(pantallas,MAXPANT);
            break;
        case 4:
            contrataciones_contratarPublicidad(pantallas,contrataciones,MAXPANT,MAXCONT);
            break;
        case 5:
            contrataciones_modificarContratacion(pantallas,contrataciones,MAXPANT,MAXCONT);
            break;
        case 6:
            contrataciones_cancelarContratacion(pantallas,contrataciones,MAXPANT,MAXCONT);
            break;
        case 7:
            contrataciones_facturacion(pantallas,contrataciones,MAXPANT,MAXCONT);
            break;
        case 8:
            contrataciones_listarContrataciones(pantallas,contrataciones,MAXPANT,MAXCONT);
            break;
        case 9:
            pantallas_listarPantallas(pantallas,MAXPANT,"No hay pantallas para listar");
            break;
        case 10:
            informes_clienteContratacionesEimporte(pantallas,contrataciones,MAXPANT,MAXCONT);
            break;
        case 0:
            salir=0;
            break;
        }
    }
    while(salir != 0);
    return 0;
}

