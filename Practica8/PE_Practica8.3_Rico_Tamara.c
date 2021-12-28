#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define h 1e-4

float biseccion( float (*f)(float), float tolerancia, float max_iter);
float falsa_posicion( float (*f)(float), float tolerancia, float max_iter);
float newton( float (*f)(float), float tolerancia, float max_iter);
float derivada(float (*f)(float), float x);

float f(float x)
{
    return  x*x-3;
}

int main (void)
{


  int opt, size, i;
  float (*metodos[])(float (*f)(float), float, float) = {biseccion, falsa_posicion, newton};
  char* nombres[] = {"Biseccion", "Falsa posicion", "Newton"};

  size=sizeof(nombres)/sizeof(char*);

  printf("Seleccione un metodo:\n");
  i=1;
  do
  {
    printf("%d) %s\n", i, nombres[i-1]);
  }while(i++<size);

  printf("Ingrese opcion: ");
  scanf("%d", &opt);

  if(opt<=size && opt>=1)
    printf("Solucion: %f", metodos[opt-1](f, 1e-3, 100));
  else
    printf("Seleccione opcion correcta");



  return 0;
}


float biseccion( float (*f)(float), float tolerancia, float max_iter)
{
    //solicitar limite izquierdo y derecho
    float error=1e10, valor, izq, der, xr=0;
    int iter=0;

    printf("Ingrese rango de busqueda (ej 1.0, 2.0):");

    scanf("%f, %f", &izq, &der);

    if(izq>=der || f(der) * f(izq) > 0)
    {
        printf("\n****Intente otro rango****\n");
        return 0;
    }


    while(error>tolerancia && iter<max_iter)
    {
        xr = (izq+der)/2.0;
        if(f(xr) * f(izq) <0)
            der = xr;
        else
            izq = xr;
        iter++;
        error = fabs(f(xr));
    }
    return xr;
}

float falsa_posicion( float (*f)(float), float tolerancia, float max_iter)
{
    //es = tolerancia
    float xi, xu, xr, ea, primera_xr, prueba, fi, fr;
    int iter=0;
    printf("Ingrese rango de busqueda (ej 1.0, 2.0):");
    scanf("%f, %f", &xi, &xu);

    if(xi>=xu || f(xi) * f(xu) > 0)
    {
        printf("\n****Intente otro rango****\n");
        return 0;
    }
    fi=f(xi);
    do
    {
        primera_xr=xr;
        xr=xu-((f(xu)*(xi-xu))/(f(xi)-f(xu)));
        fr=f(xr);
        iter++;
        if(xr!=0)
            ea=fabs(((xr-primera_xr)/xr)*100);
        prueba=fi*fr;
        if(prueba<0)
            xu=xr;
        else if(prueba>0)
        {
            xi=xr;
            fi=fr;
        }
        else
            ea=0;
    }while(ea<tolerancia && iter<max_iter);

    return xr;
}


float newton( float (*f)(float), float tolerancia, float max_iter)
{
    int iter=0;
    float xi, xr, gx, fi, fr;
    printf("Ingrese un valor inicial :");
    scanf("%f", &xi);
    //derivada en el punto xr
    gx=(derivada(f, xi));
    if(gx=0)
    {
        printf("\n****Error matematico****\n");
        return 0;
    }
    do
    {
        xr=xi-(fi/gx);
        xi=xr;
        iter++;
        if(iter>max_iter)
        {
            printf("No converge");
            return 0;
        }
        fi=f(xr);

    }while(fabs(fi)>tolerancia && iter<max_iter);

    return xr;
}

float derivada(float (*f)(float), float x)
{
    return (f(x+h)-f(x-h))/(2*h);
}


