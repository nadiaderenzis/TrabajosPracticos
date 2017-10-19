#ifndef PANTALLAS_H_INCLUDED
#define PANTALLAS_H_INCLUDED

typedef struct
{
    int idPantalla;
    unsigned char tipo;
    char nombre[51];
    char direccion[100];
    float precioPorDia;
    unsigned int estado;

}sPantallas;

#endif // PANTALLAS_H_INCLUDED

#define PANTALLAS_SINCARGAR -1
#define PANTALLAS_LIBRE 0
#define PANTALLAS_CONTRATADA 1

#define PANTALLAS_LCD 0
#define PANTALLAS_LED 1

int pantallas_initArray (sPantallas* arrayPantallas, int longitud);
int pantallas_generarProximoId (void);
int pantallas_cargarPantallas (sPantallas* arrayPantallas,int longitud);
int pantallas_listarPantallas (sPantallas* arrayPantallas, int longitud,char* mensajeError);
int pantallas_hayPantallasCargadas(sPantallas* arrayPantalla,int longitud);
int pantallas_buscarIndicePorId (sPantallas* arrayPantallas, int longitud, int id, char* mensaje);
int pantallas_modificarPantallas (sPantallas* arrayPantallas, int longitud,char* mensajeError);
int pantallas_darDeBajaPantalla (sPantallas* arrayPantallas, int longitud);
