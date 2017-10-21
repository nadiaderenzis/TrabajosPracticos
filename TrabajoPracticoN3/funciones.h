#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

typedef struct{
    char titulo[20];
    unsigned char genero;
    int duracion;
    char descripcion[50];
    int puntaje;
    char linkImagen[50];
    int idMovies;
    unsigned char estado;
}EMovie;

#endif // FUNCIONES_H_INCLUDED
#define GENERO_SUSPENSO 0
#define GENERO_DRAMA 1
#define GENERO_SCIFI 2
#define GENERO_COMEDIA 3

#define MOVIE_FREE 0
#define MOVIE_NOTFREE 1

int imprimoMenu(void);

int leer_archivo (EMovie* arrayMovie, int lenght, char* mensajeError);
int escribir_archivo(EMovie* arrayMovie, int lenght, char* mensajeError);
int crear_html(EMovie* arrayMovie, int lenght, char* mensajeError);

int movie_initArray (EMovie* arrayMovie, int lenght);

int movie_add (EMovie* arrayMovie, int lenght);
int movie_buscarIndicePorId (EMovie* arrayMovie, int lenght, int id, char* mensaje);
int movie_hayPeliculasCargadas(EMovie* arrayMovie,int lenght);
int movie_modifyMovies (EMovie* arrayMovie, int lenght,char* mensajeError);
int movie_deleteMovie (EMovie* arrayMovie, int lenght);
