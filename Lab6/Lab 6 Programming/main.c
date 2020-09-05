#include <stdio.h>
#include "math.h"
#include "stdlib.h"


double ChordMethod(double *function);
double Function1(double x); //Функция задания 1
double Function2(double x);
double Sum();

const double Eps1 = 0.001;
const double Eps2 = 0.0005;
int SplitLine = 10; //Число отрезков разбиения

int main()
{
    double Task1;
    double Task2;
    Task1 = ChordMethod(Function1);
    printf("TASK 1: \n");
    printf("Value of x = %lf \n", Task1);
    printf("Value of F(x) = %lf \n", Function1(Task1));
    
    Task2 = Sum();
    printf("TASK 2: \n");
    printf("Value of Integral = %lf \n", Task2);
    
    return 0;
    
}
double Function1(double x)
{
    return (2*sin(x)*sin(x))/3-0.75*cos(x)*cos(x);
}

double Function2(double x)
{
    return sqrt(tan(x));
}

double ChordMethod(double *function)
{
    double x;
    double A = 0;
    double Pi = atan(1)*4;
    double B;
    double Fa;
    double Fb;
    double Fx;
    
    B = Pi/2;
    while(1)
    {
        Fa = Function1(A);
        Fb = Function1(B);
        x = (A*Fb - B*Fa)/(Fb-Fa);
        Fx = Function1(x);
    
        if (Fx * Fa < 0)
        {
            B = x;
        }
        else
        {
            A = x;
        }
        if (fabs(Fx) < Eps1) break;
    }
    return x;
}

double Sum()
{
    int i = 0;
    double A = 0.0;
    double Pi = atan(1)*4;
    double B;
    double H;
    double S = 0;
    double NewS = 0;
    
    B = Pi/6;
    H = (B - A)/SplitLine;
    for(i; i < (SplitLine - 1); i++)
    {
        S += Function2(A + H*i + H/2);
    }
    S *= H;
    SplitLine++;
    
    while (1)
    {
        H = (B - A)/SplitLine;
        for(i; i < SplitLine - 1; i++)
        {
            NewS += Function2(A + H*i + H/2);
        }
        NewS *= H;
//        printf("S = %lf\n", S);
        if(fabs((NewS - S)) < Eps2)
        {
            break;
        }
        else
        {
            SplitLine++;
            S = NewS;
            NewS = 0;
        }
    }
    return NewS;
}
