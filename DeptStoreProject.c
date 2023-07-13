#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

typedef struct stocks
{
    int code, stock;
    float rate;
    char name[20];

} stocks;

typedef struct item
{
    int code, qty;
    float rate, cost;
    char name[20];
} item;

void info_print()
{
    printf("                                    WELCOME TO THE XYZ STORE SERVICES     \n");
        printf("\n");
        printf("                                              ADDRESS:      \n");
        printf("                                              DETAILS       \n");

        printf("\n\n\n");
}

void sorting()
{
    stocks *s, s1;
    FILE *fptr;
    fptr = fopen("record.txt", "rb");
    fseek(fptr, 0, SEEK_END);
    int n = ftell(fptr) / sizeof(stocks);
    rewind(fptr);
    s = (stocks *)calloc(n, sizeof(stocks));

    for (int i = 0; i < n; i++)
        fread(&s[i], sizeof(stocks), 1, fptr);
    fclose(fptr);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (s[i].code < s[j].code)
            {
                s1 = s[i];
                s[i] = s[j];
                s[j] = s1;
            }
        }
    }
    fptr = fopen("record.txt", "wb");

    for (int i = 0; i < n; i++)
        fwrite(&s[i], sizeof(stocks), 1, fptr);

    fclose(fptr);
    free(s);
}

void add_stocks()
{
    system("cls");
    info_print();
    stocks *s;
    FILE *fptr;
    int nost, i;
    printf("Enter how many Products you want to add: ");
    scanf("%d", &nost);
    fptr = fopen("record.txt", "ab");
    system("cls");
    s = (stocks *)calloc(nost, sizeof(stocks));
    for (i = 0; i < nost; i++)
    {

        printf("Enter Product Code: ");
        scanf("%d", &s[i].code);
        printf("Enter the Name of Product: ");
        fflush(stdin);
        scanf("%[^\n]s", &s[i].name);

        printf("\nEnter the Rate of Product: ");
        scanf("%f", &s[i].rate);
        printf("\nEnter the Stock of Product: ");
        scanf("%d", &s[i].stock);

        fwrite(&s[i], sizeof(stocks), 1, fptr);
    }

    fclose(fptr);
    int pressed = 0;
    pressed = getch();
    if (pressed == 13)
    {
        // ADDED FOR BACK CURSOR
        system("cls");

        int position = 1;
        int keypressed = 0;

        while (keypressed != 13)
        {
            system("cls");
            arrowhere(1, position);
            printf("                                       || ADD MORE STOCKS ||\n");
            arrowhere(2, position);
            printf("                                       || BACK ||\n");

            keypressed = getch();

            if (keypressed == 80 && position != 2)
            {
                position++;
            }
            else if (keypressed == 72 && position != 1)
            {
                position--;
            }
            else
            {
                position = position;
            }
        }
        switch (position)
        {
        case 1:
            add_stocks();
            break;

        case 2:
            secondInterface();
            break;

        default:
            printf("YOU SELECTED WRONG OPTION!!");
        }
    }
}

void display_stocks()
{
    system("cls");
    sorting();
    stocks s1;
    int a = 1;
    FILE *fptr;
    fptr = fopen("record.txt", "rb");
    system("cls");
    info_print();

    printf("S.No. CODE       NAME OF PRODUCT          RATE        STOCKS\n");
    while (fread(&s1, sizeof(stocks), 1, fptr))
    {
        printf("\n%-4d%4d\t %-20s%9.2f%13d", a, s1.code, s1.name, s1.rate, s1.stock);
        a++;
    }
    fclose(fptr);
    int pressed = 0;
    pressed = getch();
    if (pressed == 13)
    {
        // ADDED FOR BACK CURSOR
        system("cls");

        int position = 1;
        int keypressed = 0;

        while (keypressed != 13)
        {
            system("cls");
            arrowhere(1, position);
            printf("                                       || BACK ||\n");

            keypressed = getch();

            if (keypressed == 80 && position != 1)
            {
                position++;
            }
            else if (keypressed == 72 && position != 1)
            {
                position--;
            }
            else
            {
                position = position;
            }
        }
        switch (position)
        {
        case 1:
            secondInterface();
            break;

        default:
            printf("YOU SELECTED WRONG OPTION!!");
        }
    }
}

void edit_all()
{
    system("cls");
    info_print();
    stocks s1;

    int a, found = 0, size;
    ;
    FILE *fptr;
    fptr = fopen("record.txt", "r+b");
    printf("Enter The Product Code: ");
    scanf("%d", &a);
    while (fread(&s1, sizeof(stocks), 1, fptr))
    {
        if (s1.code == a)
        {
            found = 1;
            size = sizeof(s1);
            printf("Enter New Product Code: ");
            scanf("%d", &s1.code);
            printf("Enter New Name of Product: ");
            fflush(stdin);
            scanf("%[^\n]s", &s1.name);
            printf("\nEnter The Rate of Product: ");
            scanf("%f", &s1.rate);
            printf("\nEnter the Stock of Product: ");
            scanf("%d", &s1.stock);

            fseek(fptr, -size, SEEK_CUR);
            fwrite(&s1, sizeof(stocks), 1, fptr);
            break;
        }
    }
    if (!found)
    {
        printf("Wrong code\n");
    }
    fclose(fptr);
    int pressed = 0;
    pressed = getch();
    if (pressed == 13)
    {
        // ADDED FOR BACK CURSOR
        system("cls");

        int position = 1;
        int keypressed = 0;

        while (keypressed != 13)
        {
            system("cls");
            arrowhere(1, position);
            printf("                                       || EDIT MORE STOCKS ||\n");
            arrowhere(2, position);
            printf("                                       || BACK ||\n");

            keypressed = getch();

            if (keypressed == 80 && position != 2)
            {
                position++;
            }
            else if (keypressed == 72 && position != 1)
            {
                position--;
            }
            else
            {
                position = position;
            }
        }
        switch (position)
        {
        case 1:
            edit_all();
            break;

        case 2:
            secondInterface();
            break;

        default:
            printf("YOU SELECTED WRONG OPTION!!");
        }
    }
}

void edit_qty()
{
    system("cls");
    info_print();
    stocks s1;
    int a, found = 0, size;
    ;
    FILE *fptr;
    fptr = fopen("record.txt", "r+b");
    printf("Enter The Product Code: ");
    scanf("%d", &a);
    while (fread(&s1, sizeof(stocks), 1, fptr))
    {
        if (s1.code == a)
        {
            found = 1;
            size = sizeof(s1);
            printf("\nEnter the New Stock of Product: ");
            scanf("%d", &s1.stock);

            fseek(fptr, -size, SEEK_CUR);
            fwrite(&s1, sizeof(stocks), 1, fptr);
            break;
        }
    }
    if (!found)
    {
        printf("Wrong code\n");
    }
    fclose(fptr);
    int pressed = 0;
    pressed = getch();
    if (pressed == 13)
    {
        // ADDED FOR BACK CURSOR
        system("cls");

        int position = 1;
        int keypressed = 0;

        while (keypressed != 13)
        {
            system("cls");
            arrowhere(1, position);
            printf("                                       || EDIT MORE STOCKS ||\n");
            arrowhere(2, position);
            printf("                                       || BACK ||\n");

            keypressed = getch();

            if (keypressed == 80 && position != 2)
            {
                position++;
            }
            else if (keypressed == 72 && position != 1)
            {
                position--;
            }
            else
            {
                position = position;
            }
        }
        switch (position)
        {
        case 1:
            edit_qty();
            break;

        case 2:
            secondInterface();
            break;

        default:
            printf("YOU SELECTED WRONG OPTION!!");
        }
    }
}

void edit_stocks()
{
    system("cls");
info_print();

    int position = 1;
    int keypressed = 0;

    while (keypressed != 13)
    {
        system("cls");

        printf("\n\n\n");

        arrowhere(1, position);
        printf("                                       || EDIT ALL DETAILS ||\n");
        arrowhere(2, position);
        printf("                                       || RE-STOCK QUATITY ||\n");
        arrowhere(3, position);
        printf("                                       || BACK ||\n");

        keypressed = getch();

        if (keypressed == 80 && position != 3)
        {
            position++;
        }
        else if (keypressed == 72 && position != 1)
        {
            position--;
        }
        else
        {
            position = position;
        }
    }
    switch (position)
    {
    case 1:
        edit_all();
        break;

    case 2:
        edit_qty();
        break;

    case 3:
        secondInterface();
        break;

    default:
        printf("YOU SELECTED WRONG OPTION!!");
    }
}

void delete_stocks()
{
    system("cls");
    info_print();
    stocks s1;
    int a, found = 0;
    FILE *fptr, *fptr1;
    fptr = fopen("record.txt", "rb");
    fptr1 = fopen("record1.txt", "wb");
    printf("Enter The Code Of Product To Be Deleted: ");
    scanf("%d", &a);
    while (fread(&s1, sizeof(stocks), 1, fptr))
    {
        if (s1.code == a)
        {
            found = 1;
        }
        else
        {
            fwrite(&s1, sizeof(stocks), 1, fptr1);
        }
    }
    fclose(fptr);
    fclose(fptr1);
    if (found)
    {
        fptr1 = fopen("record1.txt", "rb");
        fptr = fopen("record.txt", "wb");
        while (fread(&s1, sizeof(stocks), 1, fptr1))
        {
            fwrite(&s1, sizeof(stocks), 1, fptr);
        }
        fclose(fptr);
        fclose(fptr1);
    }
    else
    {
        printf("\nProduct Not Found\n");
    }

    int pressed = 0;
    pressed = getch();
    if (pressed == 13)
    {
        // ADDED FOR BACK CURSOR
        system("cls");

        int position = 1;
        int keypressed = 0;

        while (keypressed != 13)
        {
            system("cls");
            arrowhere(1, position);
            printf("                                       || DELETE MORE STOCKS ||\n");
            arrowhere(2, position);
            printf("                                       || BACK ||\n");

            keypressed = getch();

            if (keypressed == 80 && position != 2)
            {
                position++;
            }
            else if (keypressed == 72 && position != 1)
            {
                position--;
            }
            else
            {
                position = position;
            }
        }
        switch (position)
        {
        case 1:
            delete_stocks();
            break;

        case 2:
            secondInterface();
            break;

        default:
            printf("YOU SELECTED WRONG OPTION!!");
        }
    }
}

void search_by_name()
{
    system("cls");
    info_print();
    char name[20];
    stocks s1;
    int a = 1, d, found;
    found = 0;
    d = 1;
    FILE *fptr;
    fptr = fopen("record.txt", "rb");
    fflush(stdin);
    printf("Enter The Product Name: ");
    scanf("%[^\n]s", &name);
    printf("\n");
    while (fread(&s1, sizeof(stocks), 1, fptr))
    {
        if (strcmp(s1.name, name) == 0)
        {
            found = 1;

            if (d == 1)
            {
                printf("S.No. CODE       NAME OF PRODUCT          RATE        STOCKS\n");
            }
            printf("\n%-4d%4d\t %-20s%9.2f%13d", a, s1.code, s1.name, s1.rate, s1.stock);
            a++;
            d++;
        }
    }
    if (!found)
        printf("No Match Found\n");
    fclose(fptr);
    int pressed = 0;
    pressed = getch();
    if (pressed == 13)
    {
        // ADDED FOR BACK CURSOR
        system("cls");

        int position = 1;
        int keypressed = 0;

        while (keypressed != 13)
        {
            system("cls");
            arrowhere(1, position);
            printf("                                       || SEARCH MORE PRODUCTS ||\n");
            arrowhere(2, position);
            printf("                                       || BACK ||\n");

            keypressed = getch();

            if (keypressed == 80 && position != 2)
            {
                position++;
            }
            else if (keypressed == 72 && position != 1)
            {
                position--;
            }
            else
            {
                position = position;
            }
        }
        switch (position)
        {
        case 1:
            search_by_name();
            break;

        case 2:
            secondInterface();
            break;

        default:
            printf("YOU SELECTED WRONG OPTION!!");
        }
    }
}
void search_by_code()
{
    system("cls");
    info_print();
    stocks s1;
    int a = 1, b, d, found;
    found = 0;
    d = 1;
    FILE *fptr;
    fptr = fopen("record.txt", "rb");
    printf("Enter The Code: ");
    scanf("%d", &b);
    printf("\n");
    while (fread(&s1, sizeof(stocks), 1, fptr) == 1)
    {
        if (s1.code == b)
        {
            found = 1;
            if (d == 1)
            {
                printf("S.No. CODE       NAME OF PRODUCT          RATE        STOCKS\n");
            }
            printf("\n%-4d%4d\t %-20s%9.2f%13d", a, s1.code, s1.name, s1.rate, s1.stock);
            a++;
            d++;
        }
    }
    if (!found)
        printf("No Match Found\n");
    fclose(fptr);
    int pressed = 0;
    pressed = getch();
    if (pressed == 13)
    {
        // ADDED FOR BACK CURSOR
        system("cls");

        int position = 1;
        int keypressed = 0;

        while (keypressed != 13)
        {
            system("cls");
            arrowhere(1, position);
            printf("                                       || SEARCH MORE PRODUCTS ||\n");
            arrowhere(2, position);
            printf("                                       || BACK ||\n");

            keypressed = getch();

            if (keypressed == 80 && position != 2)
            {
                position++;
            }
            else if (keypressed == 72 && position != 1)
            {
                position--;
            }
            else
            {
                position = position;
            }
        }
        switch (position)
        {
        case 1:
            search_by_code();
            break;

        case 2:
            secondInterface();
            break;

        default:
            printf("YOU SELECTED WRONG OPTION!!");
        }
    }
}

void search_by_rate()
{
    system("cls");
    info_print();
    stocks s1;
    int a = 1, b, d, found;
    d = 1;
    found = 0;
    FILE *fptr;
    fptr = fopen("record.txt", "rb");
    printf("Enter The Rate: ");
    scanf("%d", &b);
    printf("\n");
    while (fread(&s1, sizeof(stocks), 1, fptr))
    {
        if (s1.rate == (float)b)
        {
            found = 1;
            if (d == 1)
            {
                printf("S.No. CODE       NAME OF PRODUCT          RATE        STOCKS\n");
            }
            printf("\n%-4d%4d\t %-20s%9.2f%13d", a, s1.code, s1.name, s1.rate, s1.stock);
            a++;
            d++;
        }
    }
    if (!found)
        printf("No Match Found\n");
    fclose(fptr);
    int pressed = 0;
    pressed = getch();
    if (pressed == 13)
    {
        // ADDED FOR BACK CURSOR
        system("cls");

        int position = 1;
        int keypressed = 0;

        while (keypressed != 13)
        {
            system("cls");
            arrowhere(1, position);
            printf("                                       || SEARCH MORE PRODUCTS ||\n");
            arrowhere(2, position);
            printf("                                       || BACK ||\n");

            keypressed = getch();

            if (keypressed == 80 && position != 2)
            {
                position++;
            }
            else if (keypressed == 72 && position != 1)
            {
                position--;
            }
            else
            {
                position = position;
            }
        }
        switch (position)
        {
        case 1:
            search_by_rate();
            break;

        case 2:
            secondInterface();
            break;

        default:
            printf("YOU SELECTED WRONG OPTION!!");
        }
    }
}

void search_stocks()
{
    system("cls");
info_print();
    int position = 1;
    int keypressed = 0;

    while (keypressed != 13)
    {
        system("cls");

        printf("\n\n\n");

        arrowhere(1, position);
        printf("                                       || SEARCH BY NAME ||\n");
        arrowhere(2, position);
        printf("                                       || SEARCH BY CODE ||\n");
        arrowhere(3, position);
        printf("                                       || SEARCH BY RATE ||\n");
        arrowhere(4, position);
        printf("                                       || BACK ||\n");

        keypressed = getch();

        if (keypressed == 80 && position != 4)
        {
            position++;
        }
        else if (keypressed == 72 && position != 1)
        {
            position--;
        }
        else
        {
            position = position;
        }
    }
    switch (position)
    {
    case 1:
        search_by_name();
        break;

    case 2:
        search_by_code();
        break;

    case 3:
        search_by_rate();
        break;

    case 4:
        secondInterface();
        break;

    default:
        printf("YOU SELECTED WRONG OPTION!!");
    }
}

void bill_code()
{
    stocks s1;
    item item1;
    int a = 1, b, c, qty, size, found = 0;
    char billno[10], date[15];
    float cost = 0, total = 0;
    FILE *fptr, *fptr1;
    fptr = fopen("record.txt", "r+b");
    fptr1 = fopen("bill.txt", "w+b");
    system("cls");
    info_print();
    printf("Enter Bill No.:");
    scanf("%s", &billno);
    printf("\nEnter Date.:");
    scanf("%s", &date);

    while (1)
    {

        printf("Enter item code:");
        scanf("%d", &b);

        if (b == 0)
        {
            break;
        }

        printf("Enter The quantity: ");
        scanf("%d", &qty);
        rewind(fptr);
        while (fread(&s1, sizeof(stocks), 1, fptr))
        {

            if (s1.code == b)
            {
                found = 1;
                cost = qty * s1.rate;
                s1.stock = s1.stock - qty;
                if (s1.stock < 0)
                {
                    break;
                }
                strcpy(item1.name, s1.name);
                item1.qty = qty;
                item1.rate = s1.rate;
                item1.cost = qty * s1.rate;
                ;
                item1.code = s1.code;
                total = total + item1.cost;

                size = sizeof(s1);

                fseek(fptr, -size, SEEK_CUR);
                fwrite(&s1, sizeof(stocks), 1, fptr);
                fwrite(&item1, sizeof(item), 1, fptr1);

                break;
            }
        }
        if (found == 0)
        {
            printf("Wrong code\n");
        }
    }
    fclose(fptr);
    fclose(fptr1);

    fptr1 = fopen("bill.txt", "rb");

    system("cls");

    printf("        ");
    printf("                          XYZ DEPARTMENT STORE");
    printf("        ");
    printf("\n                                    BILL NUMBER:%s\n", billno);
    printf("                                    Date:%s\n ", date);

    printf("S.No. CODE       NAME OF PRODUCT          RATE        QUANTITY     COST\n");
    while (fread(&item1, sizeof(item), 1, fptr1))
    {
        printf("\n%-4d%6d\t %-20s%9.2f%13d%17f", a, item1.code, item1.name, item1.rate, item1.qty, item1.cost);
        a++;
    }
    printf("\n \n\n\n                                   TOTAL:%f\n", total);
    fclose(fptr1);
    int pressed = 0;
    pressed = getch();
    if (pressed == 13)
    {
        // ADDED FOR BACK CURSOR
        system("cls");

        int position = 1;
        int keypressed = 0;

        while (keypressed != 13)
        {
            system("cls");
            arrowhere(1, position);
            printf("                                       || CALCULATE ANOTHER BILL ||\n");
            arrowhere(2, position);
            printf("                                       || BACK ||\n");

            keypressed = getch();

            if (keypressed == 80 && position != 2)
            {
                position++;
            }
            else if (keypressed == 72 && position != 1)
            {
                position--;
            }
            else
            {
                position = position;
            }
        }
        switch (position)
        {
        case 1:
            bill_code();
            break;

        case 2:
            menu1interface();
            break;

        default:
            printf("YOU SELECTED WRONG OPTION!!");
        }
    }
}

void employee_details()
{
    system("cls");
    FILE *ptr;
    char c;
    ptr = fopen("employee_details.txt", "r");

    c = fgetc(ptr);

    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(ptr);
    }

    fclose(ptr);

    int pressed = 0;
    pressed = getch();
    if (pressed == 13)
    {
        // ADDED FOR BACK CURSOR
        system("cls");

        int position = 1;
        int keypressed = 0;

        while (keypressed != 13)
        {
            system("cls");
            arrowhere(1, position);
            printf("                                       || BACK ||\n");

            keypressed = getch();

            if (keypressed == 80 && position != 1)
            {
                position++;
            }
            else if (keypressed == 72 && position != 1)
            {
                position--;
            }
            else
            {
                position = position;
            }
        }
        switch (position)
        {
        case 1:
            menu1interface();
            break;

        default:
            printf("YOU SELECTED WRONG OPTION!!");
        }
    }
}

void menu1interface()
{
    system("cls");

    int position = 1;
    int keypressed = 0;

    while (keypressed != 13)
    {
        system("cls");
        info_print();

        

        arrowhere(1, position);
        printf("                                       || CALCULATE BILL ||\n");
        arrowhere(2, position);
        printf("                                       || CHECK EMPLOYEE DETAILS ||\n");
        arrowhere(3, position);
        printf("                                       || MANAGE GOODS ||\n");
        arrowhere(4, position);
        printf("                                       || EXIT ||\n");

        keypressed = getch();

        if (keypressed == 80 && position != 4)
        {
            position++;
        }
        else if (keypressed == 72 && position != 1)
        {
            position--;
        }
        else
        {
            position = position;
        }
    }
    switch (position)
    {
    case 1:
        bill_code();
        break;

    case 2:
        employee_details();
        break;

    case 3:
        secondInterface();
        break;

    case 4:
        exit(1);
        break;

    default:
        printf("YOU SELECTED WRONG OPTION!!");
    }
}

void secondInterface()
{
    system("cls");

    int position = 1;
    int keypressed = 0;

    while (keypressed != 13)
    {
        system("cls");
        info_print();

        arrowhere(1, position);
        printf("                                       || ADD STOCKS ||\n");
        arrowhere(2, position);
        printf("                                       || DISPLAY STOCKS ||\n");
        arrowhere(3, position);
        printf("                                       || EDIT STOCKS ||\n");
        arrowhere(4, position);
        printf("                                       || DELETE STOCKS ||\n");
        arrowhere(5, position);
        printf("                                       || SEARCH ITEM ||\n");
        arrowhere(6, position);
        printf("                                       || BACK ||\n");

        keypressed = getch();

        if (keypressed == 80 && position != 6)
        {
            position++;
        }
        else if (keypressed == 72 && position != 1)
        {
            position--;
        }
        else
        {
            position = position;
        }
    }
    switch (position)
    {
    case 1:
        add_stocks();
        break;

    case 2:
        display_stocks();
        break;

    case 3:
        edit_stocks();
        break;

    case 4:
        delete_stocks();
        break;

    case 5:
        search_stocks();
        break;

    case 6:
        menu1interface();
        break;

    default:
        printf("YOU SELECTED WRONG OPTION!!");
    }
}

void arrowhere(int realPosition, int arrowPosition)
{
    if (realPosition == arrowPosition)
    {
        printf("   --->> - ");
    }
}

int main()
{
    menu1interface();
    return 0;
}