#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "adminPanel.h"
#include "md5.h"
#include "coordinatorPanel.h"

/* Dashboard functions */
void studentDashboard(char userID[]);
void volunteerDashboard(char userID[]);

/* User functions */
void registerUser(void);
void loginUser(void);


/* ================= CLEAR BUFFER ================= */

void clearBuffer(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* Clear input buffer */
    }
}


/* ================= MAIN MENU ================= */

void showMainMenu(void)
{
    int choice;

    while (1)
    {
        printf("\n===========================================\n");
        printf("      UNIVERSITY EVENT MANAGEMENT SYSTEM   \n");
        printf("===========================================\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("-------------------------------------------\n");
        printf("Enter Choice: ");

        if (scanf("%d", &choice) != 1)
        {
            clearBuffer();
            printf("\nInvalid input! Please enter a number.\n");
            continue;
        }

        clearBuffer();

        switch (choice)
        {
            case 1:
                registerUser();
                break;

            case 2:
                loginUser();
                break;

            case 3:
                printf("\nExiting System. Goodbye!\n");
                exit(0);

            default:
                printf("\nInvalid Choice! Please try again.\n");
        }
    }
}


/* ================= REGISTER USER ================= */

void registerUser(void)
{
    FILE *fp;
    User u;

    char hashedPassword[33];

    fp = fopen("registration.txt", "a");

    if (fp == NULL)
    {
        printf("\nError opening registration.txt!\n");
        return;
    }

    printf("\n===========================================\n");
    printf("             USER REGISTRATION             \n");
    printf("===========================================\n");

    printf("1. Student\n");
    printf("2. Volunteer\n");
    printf("-------------------------------------------\n");
    printf("Enter Role: ");

    if (scanf("%d", &u.role) != 1)
    {
        clearBuffer();
        printf("\nInvalid input!\n");
        fclose(fp);
        return;
    }

    clearBuffer();

    /* Check role */
    if (u.role != 1 && u.role != 2)
    {
        printf("\nInvalid Role! Please select 1 or 2.\n");
        fclose(fp);
        return;
    }

    printf("Enter ID: ");
    scanf("%19s", u.id);
    clearBuffer();

    printf("Enter Full Name: ");
    scanf("%49s", u.name);
    clearBuffer();

    printf("Enter Department: ");
    scanf("%29s", u.dept);
    clearBuffer();

    printf("Enter Phone Number: ");
    scanf("%19s", u.phone);
    clearBuffer();

    printf("Enter Password: ");
    scanf("%49s", u.password);
    clearBuffer();


    /* ================= MD5 HASH ================= */

    md5(u.password, hashedPassword);


    /* ================= SAVE USER ================= */

    fprintf(fp,
            "%s %s %s %s %s %d\n",
            u.id,
            u.name,
            u.dept,
            u.phone,
            hashedPassword,
            u.role);

    fclose(fp);


    printf("\n===========================================\n");
    printf("       REGISTRATION SUCCESSFUL!\n");
    printf("===========================================\n");
    printf("Account created successfully.\n");
    printf("You can now login.\n");
}


/* ================= LOGIN USER ================= */

void loginUser(void)
{
    char inputID[20];
    char password[50];
    char hashedPassword[33];

    printf("\n===========================================\n");
    printf("                USER LOGIN                 \n");
    printf("===========================================\n");

    printf("Enter ID: ");
    scanf("%19s", inputID);
    clearBuffer();

    printf("Enter Password: ");
    scanf("%49s", password);
    clearBuffer();


    /* ================= DEFAULT ADMIN ================= */

    if (strcmp(inputID, "admin") == 0 &&
        strcmp(password, "admin123") == 0)
    {
        printf("\nLogin Successful!\n");
        printf("Welcome, System Administrator.\n");

        adminDashboard("admin");

        return;
    }


    /* ================= DEFAULT FACULTY ================= */

    if (strcmp(inputID, "faculty") == 0 &&
        strcmp(password, "faculty123") == 0)
    {
        printf("\nLogin Successful!\n");
        printf("Welcome, Faculty Member.\n");

        facultyDashboard("faculty");

        return;
    }


    /* ================= HASH PASSWORD ================= */

    md5(password, hashedPassword);


    /* ================= OPEN USER FILE ================= */

    FILE *fp = fopen("registration.txt", "r");

    if (fp == NULL)
    {
        printf("\nNo registered users found!\n");
        return;
    }


    User u;
    int found = 0;


    /* ================= SEARCH USER ================= */

    while (fscanf(fp,
                  "%19s %49s %29s %19s %49s %d",
                  u.id,
                  u.name,
                  u.dept,
                  u.phone,
                  u.password,
                  &u.role) == 6)
    {
        /*
           Compare:
           1. User ID
           2. MD5 hashed password
        */

        if (strcmp(inputID, u.id) == 0 &&
            strcmp(hashedPassword, u.password) == 0)
        {
            found = 1;
            break;
        }
    }

    fclose(fp);


    /* ================= LOGIN RESULT ================= */

    if (found)
    {
        printf("\n===========================================\n");
        printf("            LOGIN SUCCESSFUL!\n");
        printf("===========================================\n");

        printf("Welcome, %s!\n", u.name);


        /* Student */
        if (u.role == 1)
        {
            studentDashboard(u.id);
        }

        /* Volunteer */
        else if (u.role == 2)
        {
            volunteerDashboard(u.id);
        }
    }

    else
    {
        printf("\n===========================================\n");
        printf("             LOGIN FAILED!\n");
        printf("===========================================\n");
        printf("Invalid ID or Password!\n");
    }
}