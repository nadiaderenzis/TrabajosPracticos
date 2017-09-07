#include <stdio.h>
#include <stdlib.h>
#include "Funciones.h"
#include "Validaciones.h"

int main()
{
    char seguir='s';
    float num1=0, num2=0,resultadoSuma,resultadoResta,resultadoDivision,resultadoMultiplicacion;
    int opcion,flag1=0,flag2=0,resultadoFactorial;

    while(seguir=='s')
    {
        printf("\n1- Ingresar 1er operando (A=%.2f)\n",num1);
        printf("2- Ingresar 2do operando (B=%.2f)\n",num2);
        printf("3- Calcular la suma (A=%.2f+B=%.2f)\n",num1,num2);
        printf("4- Calcular la resta (A=%.2f-B=%.2f)\n",num1,num2);
        printf("5- Calcular la division (A=%.2f/B=%.2f)\n",num1,num2);
        printf("6- Calcular la multiplicacion (A=%.2f*B=%.2f)\n",num1,num2);
        printf("7- Calcular el factorial (A=%.2f!)\n",num1);
        printf("8- Calcular todas las operaciones\n");
        printf("9- Salir\n");

        ingresarDatos("\nIngrese la opcion deseada: ",&opcion,"\nOpcion incorrecta, por favor elija una opcion del 1 al 8 y 9 para salir ");
        system("cls");
        switch(opcion)

        {
        case 1:
            ingresarNumeros("\nIngrese un operando: ",&num1,&flag1);
            break;
        case 2:
            ingresarNumeros("\nIngrese otro operando: ",&num2,&flag2);
            break;
        case 3:
            if(validacionOperandos(&flag1,&flag2,"\nNo se ha ingresado el 1er operando","\nNo se ha ingresado el 2do operando\n")==0)
                {
                    printf("\nResultado de la suma: %.2f",resultadoSuma=suma(&num1,&num2));
                }
            break;
        case 4:
             if(validacionOperandos(&flag1,&flag2,"\nNo se ha ingresado el 1er operando","\nNo se ha ingresado el 2do operando\n")==0)
                {
                    printf("\nResultado de la resta: %.2f",resultadoResta=resta(&num1,&num2));
                }
            break;
        case 5:
             if(validacionOperandos(&flag1,&flag2,"\nNo se ha ingresado el 1er operando","\nNo se ha ingresado el 2do operando\n")==0)
                {
                    validacionDivisor(&num2,"El divisor no puede ser 0, ingrese un valor valido: ");
                    printf("\nResultado de la division: %.2f",resultadoDivision=division(&num1,&num2));
                }
            break;
        case 6:
            if(validacionOperandos(&flag1,&flag2,"\nNo se ha ingresado el 1er operando","\nNo se ha ingresado el 2do operando\n")==0)
                {
                    printf("\nResultado de la multiplicacion: %.2f",resultadoMultiplicacion=multiplicacion(&num1,&num2));
                }
            break;
        case 7:
            if(validacionUnicoOperando(&flag1,"\nNo se ha ingresado un numero para operar")==0)
            {
                if(esEntero(num1)==1)
                {
                    printf("\nEl factorial del nro ingresado es: %d",resultadoFactorial=factorial(num1));
                }else
                {
                    printf("No se puede calcular factorial de un numero negativo o de un numero con decimal\n");
                }
            }
            break;
        case 8:
            if(validacionOperandos(&flag1,&flag2,"\nNo se ha ingresado el 1er operando","\nNo se ha ingresado el 2do operando\n")==0)
            {
                validacionDivisor(&num2,"El divisor no puede ser 0, ingrese un valor valido: ");
                printf("\nResultado de la suma: %.2f",resultadoSuma=suma(&num1,&num2));
                printf("\nResultado de la resta: %.2f",resultadoResta=resta(&num1,&num2));
                printf("\nResultsdo de la multiplicacion %.2f",resultadoMultiplicacion=multiplicacion(&num1,&num2));
                printf("\nResultado de la division %.2f",resultadoDivision=division(&num1,&num2));
                if(esEntero(num1)==1)
                {
                    printf("\nEl factorial del nro ingresado es: %d",resultadoFactorial=factorial(num1));
                }else
                {
                    printf("No se puede calcular factorial de un numero negativo o de un numero con decimal\n");
                }
            }
            break;
        case 9:
            seguir = 'n';
            break;
        }



    }
    return 0;
}
