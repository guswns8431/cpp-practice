/*
계산기를 만들어보세요. 
사용자가 1 을 누르면 +, 2 를 누르면 - 와 같은 방식으로 해서 만들면 됩니다. 
물론 이전의 계산 결과는 계속 누적되어야 하고, 지우기 기능도 있어야 합니다. 
(물론 하나의 함수에 구현하는 것이 아니라 여러개의 함수로 분할해서 만들어야겠죠?) 
(난이도 : 中)
*/

#include <stdio.h>

void calc(double *number, double *result);
void addNum(double *number, double *result);
void subNum(double *number, double *result);
void mulNum(double *number, double *result);
void divNum(double *number, double *result);

int main()
{
    double number;
    double result = 0;

    printf("calc init(by input order, not priority of operator)\n");

    scanf("%lf", &number);
    result = number;

    calc(&number, &result);

    printf("%.3lf", result);

    return 0;
}

void calc(double *number, double *result)
{
    char operatorChar;
    scanf("%c", &operatorChar);

    switch (operatorChar)
    {
    case '+':
        addNum(number, result);
        break;
    case '-':
        subNum(number, result);
        break;
    case '*':
        mulNum(number, result);
        break;
    case '/':
        divNum(number, result);
        break;
    default:
        return;
    }
}

void addNum(double *number, double *result)
{
    scanf("%lf", number);
    *result += *number;
    calc(number, result);
}

void subNum(double *number, double *result)
{
    scanf("%lf", number);
    *result -= *number;
    calc(number, result);
}

void mulNum(double *number, double *result)
{
    scanf("%lf", number);
    *result *= *number;
    calc(number, result);
}

void divNum(double *number, double *result)
{
    scanf("%lf", number);
    *result /= *number;
    calc(number, result);
}