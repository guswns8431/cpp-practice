/*
에라토스테네스의 체를 이용해서 1 부터 N 까지의 소수를 구하는 프로그램을 만들어보세요. 
(난이도 : 中)
*/

#include <stdio.h>

void input(int *number);
void primeNumber(int *number, int *numbers);
void printPrimeNumber(int *number, int *numbers);

int main()
{
    int number;
    int numbers[10001] = {0};

    input(&number);
    primeNumber(&number, numbers);
    printPrimeNumber(&number, numbers);
    return 0;
}

void input(int *number)
{
    printf("to which index? -> ");
    scanf("%d", number);
}

void primeNumber(int *number, int *numbers)
{
    int i, j;

    for (i = 2; i < *number + 1; i++)
    {
        for (j = i * 2; j < *number + 1; j += i)
        {
            numbers[j]++;
        }
    }
}

void printPrimeNumber(int *number, int *numbers)
{
    int i;
    for (i = 2; i < *number + 1; i++)
    {
        if (numbers[i] == 0)
        {
            printf("%d\n", i);
        }
    }
}