#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void add(int a, int b)
{
    printf("Sum: %d\n", a + b);
}

void sub(int a, int b)
{
    printf("Difference: %d\n", a - b);
}

void multiply(int a, int b)
{
    printf("Product: %d\n", a * b);
}

void divide(int a, int b)
{
    if (b != 0)
        printf("Quotient: %.2f\n", (float)a / b);
    else
        printf("Error: Division by zero\n");
}

void square(int a)
{
    printf("Square: %d\n", a * a);
}

void sqroot(int a)
{
    if (a >= 0)
        printf("Square root: %.2f\n", sqrt(a));
    else
        printf("Error: Square root of negative number\n");
}

void cube(int a)
{
    printf("Cube: %d\n", a * a * a);
}

void cuberoot(int a)
{
    printf("Cube root: %.2f\n", cbrt(a));
}

void addline()
{
    for (int i = 0; i < 30; i++)
    {
        printf("-");
    }
    printf("\n");
}

int main()
{
    int a, b;
    int choice;
    char option;
    addline();
    printf("\tSimple Calculator\n");
    addline();

    printf("Enter value of A: ");
    scanf("%d", &a);
    printf("Enter value of B: ");
    scanf("%d", &b);
    do
    {
        printf("\n1) Addition");
        printf("\n2) Subtraction");
        printf("\n3) Multiplication");
        printf("\n4) Division");
        printf("\n5) Square");
        printf("\n6) Square Root");
        printf("\n7) Cube");
        printf("\n8) Cube Root");
        printf("\n9) Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            add(a, b);
            break;
        case 2:
            sub(a, b);
            break;
        case 3:
            multiply(a, b);
            break;
        case 4:
            divide(a, b);
            break;
        case 5:
            printf("Square of A or B (enter A or B): ");
            scanf(" %c", &option);
            if (option == 'A' || option == 'a')
                square(a);
            else if (option == 'B' || option == 'b')
                square(b);
            else
                printf("Invalid option\n");
            break;
        case 6:
            printf("Square root of A or B (enter A or B): ");
            scanf(" %c", &option);
            if (option == 'A' || option == 'a')
                sqroot(a);
            else if (option == 'B' || option == 'b')
                sqroot(b);
            else
                printf("Invalid option\n");
            break;
        case 7:
            printf("Cube of A or B (enter A or B): ");
            scanf(" %c", &option);
            if (option == 'A' || option == 'a')
                cube(a);
            else if (option == 'B' || option == 'b')
                cube(b);
            else
                printf("Invalid option\n");
            break;
        case 8:
            printf("Cube root of A or B (enter A or B): ");
            scanf(" %c", &option);
            if (option == 'A' || option == 'a')
                cuberoot(a);
            else if (option == 'B' || option == 'b')
                cuberoot(b);
            else
                printf("Invalid option\n");
            break;
        case 9:
            exit(0);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 9);
    return 0;
}
