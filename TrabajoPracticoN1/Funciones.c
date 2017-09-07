#include <stdio.h>
#include <stdlib.h>
#include "Funciones.h"

/** \brief Solicita al usuario un valor numerico y valida dicho nro dentro de un rango determinado
 *
 * \param mensaje para pedir dato
 * \param valor ingresado por el usuario
 * \param mensaje de error
 * \return
 *
 */

int ingresarDatos (char msg[],int* valor,char msgError[])
{
    int aux;
    printf("%s",msg);
    scanf("%d",&aux);
    while(aux<=0 || aux>9)
    {
        printf("%s",msgError);
        scanf("%d",&aux);
    }
    *valor=aux;

    return 0;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

 int ingresarNumeros (char msg[],float* numero, int*flag)
{
    printf("%s",msg);
    scanf("%f",numero);
    *flag=1;
    return 0;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

 int suma (float* numero1,float* numero2)
 {
    float resultado=*numero1+*numero2;
    return resultado;
 }

 /** \brief
  *
  * \param
  * \param
  * \return
  *
  */
  int resta (float* numero1, float *numero2)
{
    float resultado= *numero1-*numero2;
    return resultado;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

 float division (float *numero1, float *numero2)
{
    float resultado=*numero1/ *numero2;
    return resultado;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

float multiplicacion (float *numero1, float *numero2)
{
    float resultado=(*numero1)*(*numero2);
    return resultado;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

 long int factorial (int num)
{
    int resultado;
    {
        if(num==1|| num==0)
        {
            return 1;
        }
        resultado=num* factorial(num-1);
        return (resultado);
    }
}
