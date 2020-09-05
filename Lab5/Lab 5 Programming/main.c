#include "math.h"
#include <stdio.h>

int GetN(double x1, double x2, double accuracy);
double CalculateRow(double x, int N);
unsigned long int Factorial(int n);

int main()
{
    double Accuracy = 0.000001; //Заданная точность
    const int M = 5; //Заданное кол-во строк
    //Диапазон изменяющихся значений функций
    const double B = 4;
    const double A = 0;
    const double Step = 0.1; //Заданный шаг изменения
    double x = 0;
    int CounterOfStep;
    int countInARow;
    double X1 = 0;
    double X2 = 0;
    printf("Введите значение первой точки: ");
    if (scanf("%lf", &X1) != 1)
    {
        printf("Ошибка ввода значения первой точки\n");
        return -1;
    }
    if ((X1 < 0) || (X1 > 4))
    {
        printf("Ошибка ввода значения первой точки\n");
        return -1;
    }
    printf("Введите значение второй точки: ");
    if (scanf("%lf", &X2) != 1)
    {
        printf("Ошибка ввода значения первой точки\n");
        return -1;
    }
    if ((X2 < 0) || (X2 > 4))
    {
        printf("Ошибка ввода значения второй точки\n");
        return -1;
    }
    CounterOfStep = (B - A) / Step + 1; //Число шагов
    countInARow = CounterOfStep / M + 1; //Число значений в строке
    int n;
    n = GetN(X1,X2, Accuracy);
    int i;
    int j;
    double valueOfFunction;
    for (i = 0; i < M; i++) //Количество строк
    {
        for (j = 0; j < countInARow; j++) //Число значений в одной строке
        {
            if (x - Step > B) break;
            
            valueOfFunction = CalculateRow(x, n);
            printf("%10.6f\t\t", valueOfFunction);
            x += Step;
        }
        printf("\n");
        //printf("%f\n", Factorial(7));
    }
    return 0;
}

int GetN(double x1, double x2, double accuracy) /*Подсчет кол-ва членов ряда, необхожимых для вычисления значения с заданной точностью
                                                 Передача занчения А и A + Step в х1 и х2*/
{
    double TrueValue1;
    double TrueValue2;
    double LineValue1;
    double LineValue2;
    int N = 0;
    int n = 0;
    
    TrueValue1 = exp(x1);
    TrueValue2 = exp(x2);
    LineValue1 = 1;
    LineValue2= 1;
    //Пока разница вычисленного значения не попадает в область заданной точности
    while ((fabs(LineValue1 - TrueValue1) > accuracy) || (fabs(LineValue2 - TrueValue2) > accuracy))
    {
        N++;
        n++;
        LineValue1 += (pow(x1, n) / Factorial(n));
        LineValue2 += (pow(x2, n) / Factorial(n));
        
    }
    printf("Необхоlимое количество членов ряда для заданной точности = %d\n", N);
    return N;
}

unsigned long int Factorial(int n)
{
    double i;
    for (i = 1; n > 1; i *= (n--));
    return i;
}

double CalculateRow(double x, int N)
{
    int i = 0;
    double result = 1;
    for (i = 1; i < N; i++)
    {
        result += (pow(x, i) / Factorial(i));
    }
    return result;
}
