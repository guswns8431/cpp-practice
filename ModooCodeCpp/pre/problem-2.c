/*
유클리도 호제법을 이용해서 N 개의 수들의 최대공약수를 구하는 함수를 만들어보세요. 
유클리드 호제법이 무엇인지 모르신다면, 인터넷 검색을 활용하는 것을 추천합니다. 
(댓글을 달아도 돼요) 
(난이도 : 中上)
*/

#include <stdio.h>

void input(int *number, int *numbers);
int gcd(int a, int b);

int main()
{
    int i;
    int gcdValue;
    int number;
    int numbers[100];

    input(&number, numbers);
    gcdValue = gcd(numbers[0], numbers[1]);

    for (i = 2; i < number; i++)
    {
        gcdValue = gcd(gcdValue, numbers[i]);
    }

    printf("%d", gcdValue);

    return 0;
}

void input(int *number, int *numbers)
{
    int i;

    printf("how many? -> ");
    scanf("%d", number);

    for (i = 0; i < *number; i++)
    {
        scanf("%d", &numbers[i]);
    }
}
int gcd(int a, int b)
{
    return a % b == 0 ? b : gcd(b, a % b);
}