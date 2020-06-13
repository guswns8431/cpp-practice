/* 
N 진법에서 M 진법으로 변환하는 프로그램을 만들어보세요. 
(단, 36진법까지 표현 가능하다. 숫자 10개, 알파벳 26개)
(난이도 : 中)
*/

#include <stdio.h>

void input(int *former, int *latter, char *inputValue);
void formerToDec(int *former, int *decValue, char *inputValue);
void decToLatter(int *latter, int *decValue, char *result);
void printReverseResult(char *resultValue);

int main()
{
    int former, latter;
    int decValue = 0;
    char inputValue[100] = {0};
    char resultValue[100] = {0};

    input(&former, &latter, inputValue);
    formerToDec(&former, &decValue, inputValue);
    decToLatter(&latter, &decValue, resultValue);
    printReverseResult(resultValue);

    return 0;
}

void input(int *former, int *latter, char *inputValue)
{
    printf("from ? -> ");
    scanf("%d", former);
    printf("to ? -> ");
    scanf("%d", latter);
    printf("which value ? -> ");
    scanf("%s", inputValue);
}

int valueSize(char *inputValue)
{
    int index = 0;
    while (inputValue[index] != 0)
    {
        index++;
    }

    return index;
}

int characterToValue(char character)
{
    if (character >= 48 && character <= 57)
    {
        return character - 48;
    }
    else if (character >= 65 && character <= 90)
    {
        return character - 55;
    }
    else if (character >= 97 && character <= 122)
    {
        return character - 87;
    }
}

char valueToCharacter(int number)
{
    if (number >= 0 && number <= 9)
    {
        return number + 48;
    }
    else if (number >= 10 && number <= 35)
    {
        return number + 55;
    }
}

void formerToDec(int *former, int *decValue, char *inputValue)
{
    int i;
    int size = valueSize(inputValue);
    int measure = 1;

    for (i = size - 1; i >= 0; i--)
    {
        *decValue += (measure * characterToValue(inputValue[i]));
        measure *= *former;
    }
}

void decToLatter(int *latter, int *decValue, char *resultValue)
{
    int index = 0;

    while (*decValue)
    {
        resultValue[index] = valueToCharacter(*decValue % *latter);
        printf("%c", resultValue[index]);
        *decValue /= *latter;
        index++;
    }
}

void printReverseResult(char *resultValue)
{
    int i;
    int size = valueSize(resultValue);

    for (i = size - 1; i >= 0; i--)
    {
        printf("%c", resultValue[i]);
    }
}
