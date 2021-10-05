#include <bits/stdc++.h>
using namespace std;
/* Defintion of record of type student */
struct student
{
    char name[50];
    int score;
};

/* Global data variable */
FILE *file;

/* Function prototypes */
void display_all()
{
    struct student data;
    printf("\n\nDISPLAY ALL RECORD !!!\n");
    file = fopen("student.txt", "rb");
    while ((fread(&data, sizeof(data), 1, file)) > 0)
    {
        //display(data);
        printf("\nName of student : %s", data.name);
        printf("\nScore in test 1 : %d", data.score);
        printf("\n====================================\n");
    }
    fclose(file);
}

void modify_student()
{
    struct student data;
    int no, found = 0;
    printf("\nTo Modify ");
    printf("\nPlease Enter The name of student: ");
    char nm[50];
    scanf("%s", nm);
    file = fopen("student.txt", "rb+");
    while ((fread(&data, sizeof(data), 1, file)) > 0 && found == 0)
    {
        if(strcmp(nm,data.name)==0)
        {
            data.score=data.score+5;
            fseek(file,  - (long)sizeof(data), 1);
            fwrite(&data, sizeof(data), 1, file);
            printf("\n Record Updated");
            found = 1;
        }
    }
    fclose(file);
    if (found == 0)
    {
        struct student data;
        file = fopen("student.txt", "ab");
        strcpy(data.name,nm);
        data.score=5;
        fwrite(&data, sizeof(data), 1, file);
        fclose(file);
        printf("\nStudent Record Has Been Created ");
    }
}

void class_result()
{
    struct student data;
    file = fopen("student.txt", "rb");
    if (file == NULL)
    {
        printf("ERROR!!! FILE COULD NOT BE OPEN\n\n Go To Entry Menu to create File");
        printf("\n\n Program is closing ....");
        return;
    }

    printf("\nALL PLAYERS RESULT \n");
    printf("=================================\n");
    printf("Name\t\tScore\n");
    printf("=================================\n");

    while ((fread(&data, sizeof(data), 1, file)) > 0)
    {
        printf("%-15s %-7d\n",data.name, data.score);
    }
    fclose(file);
}

void result_menu()
{
    int rno, ans;
    char choice;

    printf("\n\nResult Menu");
    printf("\n1. Class Result\n2.Back to Main Menu");
    printf("\nEnter Choice (1-3)? ");
    scanf("%d", &ans);
    switch (ans)
    {
    case 1:
        class_result();
        break;
    case 2:
        break;
    default:
        printf("\a");
    }
}

void entry_menu()
{
    int choice;
    printf("\n\nEntry Menu");
    printf("\n1.Display all players records");
    printf("\n2.Modify player record");
    printf("\n3.Back to main menu");
    printf("\nEnter your choice (1-3): ");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        display_all();
        break;
    case 2:
        modify_student();
        break;
    case 3:
        break;
    default:
        printf("\a");
        entry_menu();
    }
}
int main()
{
    int choice;
    do
    {
        printf("\n\nMain Menu");
        printf("\n1. Result Menu");
        printf("\n2. Entry/Edit Menu");
        printf("\n3. Exit");
        printf("\nPlease select your choice (1-3): ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            result_menu();
            break;
        case 2:
            entry_menu();
        }
    }
    while (choice != 3);
    return 0;
}

