/*
문자열을 두 개 입력 받아서 먼저 입력받은 문자열에서 나중에 입력받은 문자열의 위치를 검색하는 함수를 만들어보세요. 
만일 없다면 -1 을 리턴하고 있다면 그 위치를 리턴합니다. 
(난이도 : 中)
예를 들어먼저 처음 입력한 것이 I_am_a_boy 이고, 나중에 입력한 것이 am 이였다면 컴퓨터는 I_am_a_boy 에서 am 의 위치를 찾는다. 
이 경우에는 am 의 위치는 2 (처음에서 세번째) 이므로 2 를 리턴한다. 
만일 am 이라는 문자열이 없다면 -1 을 리턴한다.
*/

#include <stdio.h>

void input(char *input1, char *input2);
int findIndex(char *input1, char *input2);

int main()
{
    char string1[100];
    char string2[100];
    int index;

    input(string1, string2);
    index = findIndex(string1, string2);

    if (index == -1)
    {
        printf("no string");
    }
    else
    {
        printf("%d", index);
    }

    return 0;
}

void input(char *input1, char *input2)
{
    printf("the first string -> ");
    scanf("%s", input1);
    printf("the second string -> ");
    scanf("%s", input2);
}

int findIndex(char *input1, char *input2)
{
    int location = 0;
    int incrementIndex = 0;

    while (*input1)
    {
        while (*input1 == *input2)
        {
            input1++;
            input2++;
            incrementIndex++;
            if (*input2 == '\0' && (*input1 == '_' || *input1 == '\0'))
            {
                return location;
            }
            if (*input1 != *input2)
            {
                printf("%d", incrementIndex);
                input2 -= incrementIndex;
                location += incrementIndex;
                incrementIndex = 0;
            }
        }
        input1++;
        location++;
    }

    return -1;
}