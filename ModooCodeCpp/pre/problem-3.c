/*
자기 자신을 호출하는 함수를 이용해서 1 부터 특정한 수까지의 곱을 구하는 프로그램을 만들어보세요. 
(난이도 : 下)
*/

#include <stdio.h>

void input(int *number);
void multipleTo1(int *number, int *result);

int main()
{
    int number;
    int result = 1;

    input(&number);
    multipleTo1(&number, &result);

    printf("%d", result);

    return 0;
}

void input(int *number)
{
    printf("to which index? -> ");
    scanf("%d", number);
}

void multipleTo1(int *number, int *result)
{
    if (*number == 1)
    {
        return;
    }

    *result *= *number;
    (*number)--;
    multipleTo1(number, result);
}