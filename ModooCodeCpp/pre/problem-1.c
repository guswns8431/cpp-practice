/* 
문제 1
사용자로 부터 5 명의 학생의 수학, 국어, 영어 점수를 입력 받아서 평균이 가장 높은 사람 부터 평균이 가장 낮은 사람까지 정렬되어 출력하도록 하세요. 
특히, 평균을 기준으로 평균 이상인 사람 옆에는 '합격', 아닌 사람은 '불합격' 을 출력하게 해보세요 
(난이도 : 中上).
*/

#include <stdio.h>

void input(int (*score)[3], int rowSize);
void makeAvg(int (*score)[3], int rowSize, int *avg);
void selectionSort(int *avg);
void output(int *avg);

int main()
{
    int score[5][3];
    int avg[5];

    input(score, 5);
    makeAvg(score, 5, avg);
    selectionSort(avg);
    output(avg);

    return 0;
}

void input(int (*score)[3], int rowSize)
{
    int i, j;

    for (i = 0; i < rowSize; i++)
    {
        for (j = 0; j < 3; j++)
        {
            scanf("%d", &score[i][j]);
        }
    }
}

void makeAvg(int (*score)[3], int rowSize, int *avg)
{
    int i, j;
    int sum;

    for (i = 0; i < rowSize; i++)
    {
        sum = 0;
        for (j = 0; j < 3; j++)
        {
            sum += score[i][j];
        }
        sum /= 5;
        avg[i] = sum;
    }
}

void selectionSort(int *avg)
{
    int i, j;
    int selectedIndex, temp;

    for (i = 0; i < 5; i++)
    {
        selectedIndex = i;

        for (j = i + 1; j < 5; j++)
        {
            if (avg[selectedIndex] < avg[j])
            {
                selectedIndex = j;
            }
        }

        temp = avg[i];
        avg[i] = avg[selectedIndex];
        avg[selectedIndex] = temp;
    }
}

void output(int *avg)
{
    int i;
    int sum = 0;
    char pfscore;

    for (i = 0; i < 5; i++)
    {
        sum += avg[i];
    }
    sum /= 5;

    for (i = 0; i < 5; i++)
    {
        if (avg[i] >= sum)
        {
            pfscore = 'p';
        }
        else
        {
            pfscore = 'f';
        }

        printf("%d score is %c\n", avg[i], pfscore);
    }
}
