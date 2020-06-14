/*
도서 관리 프로그램을 만들어봅시다. 프로그램에는 다음과 같은 기능들이 구현되어 있어야 합니다. (난이도 : 上)
책을 새로 추가하는 기능 (책의 총 개수는 100 권이라 하자. 이 때, 각 책의 정보는 제목, 저자의 이름, 출판사로 한다)
책의 제목을 검색하면 그 책의 정보가 나와야 한다.
위와 마찬가지로 저자, 출판사 검색 기능이 있어야 한다.
책을 빌리는 기능.
책을 반납하는 기능
*/

#include <stdio.h>

void showMenu(int *choice);
void choiceAction(char (*book)[30], char (*author)[30], char (*publish)[30], int *isBorrowed, int *numberOfBooks, int *userChoice);
void showAllBookStatus(char (*book)[30], char (*author)[30], char (*publish)[30], int *isBorrowed, int *numberOfBooks);
void showOneBookStatus(char (*book)[30], char (*author)[30], char (*publish)[30], int *isBorrowed, int index);
void addBook(char (*book)[30], char (*author)[30], char (*publish)[30], int *isBorrowed, int *numberOfBooks);
void searchBook(char (*book)[30], char (*author)[30], char (*publish)[30], int *isBorrowed, int *numberOfBooks, int *userChoice);
void borrowBook(char (*book)[30], char (*author)[30], char (*publish)[30], int *isBorrowed, int *numberOfBooks, int *userChoice);
void returnBook(char (*book)[30], char (*author)[30], char (*publish)[30], int *isBorrowed, int *numberOfBooks, int *userChoice);
void searchFilter(char (*book)[30], char (*author)[30], char (*publish)[30], int *isBorrowed, int *numberOfBooks, int *searchChoice);
int cmpString(char *searchText, char *searchArray);

int main()
{
    char book[100][30], author[100][30], publish[100][30];
    int isBorrowed[100];
    int numberOfBooks = 0;
    int userChoice;

    while (1)
    {
        showMenu(&userChoice);

        if (userChoice == 5)
        {
            printf("Program Terminated\n");
            return 0;
        }

        choiceAction(book, author, publish, isBorrowed, &numberOfBooks, &userChoice);

        if (userChoice == 123456789)
        {
            printf("Wrong Choice\n");
            return 0;
        }
    }

    return 0;
}

void showMenu(int *choice)
{
    printf("\n\n\n\n\nLibrary\n");
    printf("Menu\n");
    printf("1. Add Book\n");
    printf("2. Search Book\n");
    printf("3. Borrow Book\n");
    printf("4. Return Book\n");
    printf("5. Exit Program\n");

    printf("Choice -> ");
    scanf("%d", choice);
}

void choiceAction(char (*book)[30], char (*author)[30], char (*publish)[30], int *isBorrowed, int *numberOfBooks, int *userChoice)
{
    printf("\n\n\n\n\n");
    switch (*userChoice - 1)
    {
    case 0:
        printf("Add Book Choice\n");
        addBook(book, author, publish, isBorrowed, numberOfBooks);
        return;
    case 1:
        printf("Search Book Choice\n");
        searchBook(book, author, publish, isBorrowed, numberOfBooks, userChoice);
        return;
    case 2:
        printf("Borrow Book Choice\n");
        borrowBook(book, author, publish, isBorrowed, numberOfBooks, userChoice);
        return;
    case 3:
        printf("Return Book Choice\n");
        returnBook(book, author, publish, isBorrowed, numberOfBooks, userChoice);
        return;
    default:
        *userChoice = 123456789;
        return;
    }
}

void showAllBookStatus(char (*book)[30], char (*author)[30], char (*publish)[30], int *isBorrowed, int *numberOfBooks)
{
    int i;

    printf("\tBook Name\t\t\t\tAuthor Name\t\t\t\tPublish Name\t\t\t\tStatus\n");

    for (i = 0; i < *numberOfBooks; i++)
    {
        showOneBookStatus(book, author, publish, isBorrowed, i);
    }
}

void showOneBookStatus(char (*book)[30], char (*author)[30], char (*publish)[30], int *isBorrowed, int index)
{
    printf("%d.\t %s\t\t\t\t\t", index + 1, book[index]);
    printf("%s\t\t\t\t\t", author[index]);
    printf("%s\t\t\t\t\t", publish[index]);
    if (isBorrowed[index])
    {
        printf("Borrowed\n");
    }
    else
    {
        printf("Remain\n");
    }
}

void addBook(char (*book)[30], char (*author)[30], char (*publish)[30], int *isBorrowed, int *numberOfBooks)
{
    printf("Book Name -> ");
    scanf("%s", book[*numberOfBooks]);

    printf("Author Name -> ");
    scanf("%s", author[*numberOfBooks]);

    printf("Publish Name -> ");
    scanf("%s", publish[*numberOfBooks]);

    isBorrowed[(*numberOfBooks)++] = 0;
}

void searchBook(char (*book)[30], char (*author)[30], char (*publish)[30], int *isBorrowed, int *numberOfBooks, int *userChoice)
{
    int searchChoice;
    int findIndex;

    showAllBookStatus(book, author, publish, isBorrowed, numberOfBooks);

    printf("\n\n\n\n\n1. Search by Book Name\n");
    printf("2. Search by Author Name\n");
    printf("3. Search by Publish Name\n");
    printf("Enter the Number to Search -> ");
    scanf("%d", &searchChoice);

    if (searchChoice >= 1 && searchChoice <= 3)
    {
        searchFilter(book, author, publish, isBorrowed, numberOfBooks, &searchChoice);
    }
    else
    {
        *userChoice = 123456789;
        return;
    }
}

void borrowBook(char (*book)[30], char (*author)[30], char (*publish)[30], int *isBorrowed, int *numberOfBooks, int *userChoice)
{
    int borrowNumber;

    showAllBookStatus(book, author, publish, isBorrowed, numberOfBooks);

    printf("\n\n\n\n\nEnter the Book Number to Borrow -> ");
    scanf("%d", &borrowNumber);

    if (*numberOfBooks == 0 || borrowNumber > *numberOfBooks)
    {
        *userChoice = 123456789;
        return;
    }

    switch (isBorrowed[borrowNumber - 1])
    {
    case 0:
        printf("\nBorrowed");
        isBorrowed[borrowNumber - 1] = 1;
        return;
    case 1:
        printf("\nAlready Borrowed");
        return;
    }
}

void returnBook(char (*book)[30], char (*author)[30], char (*publish)[30], int *isBorrowed, int *numberOfBooks, int *userChoice)
{
    int returnNumber;

    showAllBookStatus(book, author, publish, isBorrowed, numberOfBooks);

    printf("\n\n\n\n\nEnter the Book Number to Return -> ");
    scanf("%d", &returnNumber);

    if (*numberOfBooks == 0 || returnNumber > *numberOfBooks)
    {
        *userChoice = 123456789;
        return;
    }

    switch (isBorrowed[returnNumber - 1])
    {
    case 0:
        printf("\nAlready Returned");
        return;
    case 1:
        isBorrowed[returnNumber - 1] = 0;
        printf("\nReturned");
        return;
    }
}

void searchFilter(char (*book)[30], char (*author)[30], char (*publish)[30], int *isBorrowed, int *numberOfBooks, int *searchChoice)
{
    int i;
    char searchText[30];

    printf("\n\n\n\n\n");

    switch (*searchChoice - 1)
    {
    case 0:
        printf("Enter Book Name to Search -> ");
        break;
    case 1:
        printf("Enter Author Name to Search -> ");
        break;
    case 2:
        printf("Enter Publish Name to Search -> ");
        break;
    }

    scanf("%s", searchText);

    printf("\tBook Name\t\t\t\tAuthor Name\t\t\t\tPublish Name\t\t\t\tStatus\n");

    switch (*searchChoice - 1)
    {
    case 0:
        for (i = 0; i < *numberOfBooks; i++)
        {
            if (cmpString(searchText, book[i]))
            {
                showOneBookStatus(book, author, publish, isBorrowed, i);
            }
        }
        break;
    case 1:
        for (i = 0; i < *numberOfBooks; i++)
        {
            if (cmpString(searchText, author[i]))
            {
                showOneBookStatus(book, author, publish, isBorrowed, i);
            }
        }
        break;
    case 2:
        for (i = 0; i < *numberOfBooks; i++)
        {
            if (cmpString(searchText, publish[i]))
            {
                showOneBookStatus(book, author, publish, isBorrowed, i);
            }
        }
        break;
    }
}

int cmpString(char *searchText, char *searchArray)
{
    int incrementIndex = 0;

    while (*searchArray)
    {
        while (*searchArray == *searchText)
        {
            searchArray++;
            searchText++;
            incrementIndex++;
            if (*searchText == '\0')
            {
                return 1;
            }

            if (*searchArray != *searchText)
            {
                searchText -= incrementIndex;
                incrementIndex = 0;
            }
        }

        searchArray++;
    }

    return 0;
}