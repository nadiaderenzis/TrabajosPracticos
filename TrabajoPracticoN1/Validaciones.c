#include <stdio.h>
#include <stdlib.h>
#include "Funciones.h"

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

int validacionOperandos(int* flagNro1,int* flagNro2, char msgErrorFlag1[],char msgErrorFlag2[])
{
    int retorno=-1;
    if(*flagNro1==1 && *flagNro2==1)
    {
        retorno=0;
    }
    else
    {
        if(*flagNro1==0)
        {
            printf("%s",msgErrorFlag1);

        }
        if(*flagNro2==0)
        {
            printf("%s",msgErrorFlag2);
        }
    }


    return retorno;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

int validacionDivisor (float* numero2,char msgError[])
{
    while(*numero2==0)
    {
        printf("%s",msgError);
        scanf("%f",numero2);
    }
    return 0;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

int validacionUnicoOperando(int* flagNro1,char msgErrorFlag1[])
{
    int retorno=-1;
    if(*flagNro1==1)
    {
        retorno=0;
    }
    else
    {
        printf("%s",msgErrorFlag1);

    }
    return retorno;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

int esEntero(float num)
{
    int entero;
    if(num<0)
    {
        return 0;
    }
    else
    {
        entero=(int)num;
        if(num-entero!=0)
        {
            return 0;
        }
        else
            return 1;
    }

}
