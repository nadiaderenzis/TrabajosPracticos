#ifndef CONTRATACIONES_H_INCLUDED
#define CONTRATACIONES_H_INCLUDED

typedef struct
{
    int idCliente;
    char cuit[20];
    int diasPublicacion;
    char nombreArchivoVideo[60];
    unsigned int estado;
    int idPantalla;

} sContrataciones;

#endif // CONTRATACIONES_H_INCLUDED

#define CONTRATACIONES_LIBRE -1
#define CONTRATACIONES_ENCURSO 0
#define CONTRATACIONES_FINALIZADA 1

int contrataciones_initArray (sContrataciones* arrayContrataciones, int longitud);
int contrataciones_generarProximoIndice (void);
int contrataciones_contratarPublicidad (sPantallas* arrayPantalla,sContrataciones* arrayContrataciones,int longitudPantalla,
                                        int longitudContrataciones);
int contrataciones_modificarContratacion (sPantallas* arrayPantallas,sContrataciones* arrayContrataciones,int longitudPantalla,
        int longitudContrataciones);
int contrataciones_cancelarContratacion (sPantallas* arrayPantallas,sContrataciones* arrayContrataciones,int longitudPantalla,
        int longitudContrataciones);
int contrataciones_facturacion(sPantallas* arrayPantallas,sContrataciones* arrayContrataciones,int longitudPantalla,
                               int longitudContrataciones);
int contrataciones_listarContrataciones(sPantallas* arrayPantallas,sContrataciones* arrayContrataciones,int longitudPantalla,
                                       int longitudContrataciones);
int contrataciones_listarContratacionesEnCurso(sPantallas* arrayPantallas,sContrataciones* arrayContrataciones,int longitudPantalla,
        int longitudContrataciones);
int contrataciones_listarContratacionesFinalizadas(sPantallas* arrayPantallas,sContrataciones* arrayContrataciones,int longitudPantalla,
        int longitudContrataciones);



