#include "common.h"
#include "studentLogin.h"
#include "viewEvents.h"

/* ================= STUDENT DASHBOARD ================= */

void studentDashboard(char userID[])
{
    int choice;

    while (1)
    {
        printf("\n===========================================\n");
        printf("         STUDENT DASHBOARD (ID: %s)\n", userID);
        printf("===========================================\n");

        printf("1. View Upcoming Events & Register\n");
        printf("2. My Profile & Participation History\n");
        printf("3. My Certificates\n");
        printf("4. Edit Profile\n");
        printf("5. Logout\n");

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
            showUpcomingEvents(userID);
            break;

        case 2:
            viewStudentProfile(userID);
            break;

        case 3:
            viewStudentCertificates(userID);
            break;

        case 4:
            editStudentProfile(userID);
            break;

        case 5:
            printf("\nLogging out from Student Panel...\n");
            return;

        default:
            printf("\nInvalid Choice! Please try again.\n");
        }
    }
}

/* ================= VIEW PROFILE & HISTORY ================= */

void viewStudentProfile(char userID[])
{
    FILE *fp;

    fp = fopen("student_history.txt", "r");

    printf("\n===========================================\n");
    printf("        MY PARTICIPATION HISTORY\n");
    printf("===========================================\n");

    if (fp == NULL)
    {
        printf("No history found for Student ID: %s\n", userID);
        return;
    }

    char id[30];
    char eventName[50];
    char status1[20];
    char status2[20];

    float amount;

    int found = 0;

    while (fscanf(fp,
                  "%29s \"%49[^\"]\" %f %19s %19s",
                  id,
                  eventName,
                  &amount,
                  status1,
                  status2) == 5)
    {
        if (strcmp(id, userID) == 0)
        {
            printf("Event  : %-22s\n", eventName);
            printf("Paid   : BDT %.2f\n", amount);
            printf("Status : %s\n", status2);
            printf("-------------------------------------------\n");

            found = 1;
        }
    }

    fclose(fp);

    if (!found)
    {
        printf("No events registered yet.\n");
    }
}

/* ================= VIEW CERTIFICATES ================= */

void viewStudentCertificates(char userID[])
{
    FILE *fp;

    fp = fopen("certificate.txt", "r");

    printf("\n===========================================\n");
    printf("             MY CERTIFICATES\n");
    printf("===========================================\n");

    if (fp == NULL)
    {
        printf("No certificates issued yet.\n");
        return;
    }

    char id[30];
    char eventName[50];
    char issueDate[20];

    int found = 0;

    while (fscanf(fp,
                  "%29s \"%49[^\"]\" %19s",
                  id,
                  eventName,
                  issueDate) == 3)
    {
        if (strcmp(id, userID) == 0)
        {
            printf("Event      : %s\n", eventName);
            printf("Issue Date : %s\n", issueDate);
            printf("-------------------------------------------\n");

            found = 1;
        }
    }

    fclose(fp);

    if (!found)
    {
        printf("No certificates found.\n");
    }
}

/* ================= EDIT STUDENT PROFILE ================= */

void editStudentProfile(char userID[])
{
    FILE *fp;
    FILE *temp;

    fp = fopen("registration.txt", "r");

    if (fp == NULL)
    {
        printf("\nUser database error!\n");
        return;
    }

    temp = fopen("temp.txt", "w");

    if (temp == NULL)
    {
        printf("\nCould not create temporary file!\n");
        fclose(fp);
        return;
    }

    User u;

    int updated = 0;

    while (fscanf(fp,
                  "%19s %49s %29s %19s %49s %d",
                  u.id,
                  u.name,
                  u.dept,
                  u.phone,
                  u.password,
                  &u.role) == 6)
    {
        /* Find the logged-in student */
        if (strcmp(u.id, userID) == 0 &&
            u.role == 1)
        {
            updated = 1;

            printf("\n===========================================\n");
            printf("             EDIT MY PROFILE\n");
            printf("===========================================\n");

            printf("Current Name  : %s\n", u.name);
            printf("Current Dept  : %s\n", u.dept);
            printf("Current Phone : %s\n", u.phone);

            printf("-------------------------------------------\n");

            /* New Name */
            printf("Enter New Name: ");
            scanf("%49s", u.name);
            clearBuffer();

            /* New Department */
            printf("Enter New Department: ");
            scanf("%29s", u.dept);
            clearBuffer();

            /* New Phone */
            printf("Enter New Phone: ");
            scanf("%19s", u.phone);
            clearBuffer();

            /* New Password */
            printf("Enter New Password: ");
            scanf("%49s", u.password);
            clearBuffer();
        }

        /*
           Save the user information.
           If the user was not edited,
           old information remains unchanged.
        */

        fprintf(temp,
                "%s %s %s %s %s %d\n",
                u.id,
                u.name,
                u.dept,
                u.phone,
                u.password,
                u.role);
    }

    fclose(fp);
    fclose(temp);

    /* Replace old file with updated file */

    remove("registration.txt");

    if (rename("temp.txt", "registration.txt") != 0)
    {
        printf("\nError updating profile!\n");
        return;
    }

    if (updated)
    {
        printf("\n===========================================\n");
        printf("       PROFILE UPDATED SUCCESSFULLY!\n");
        printf("===========================================\n");

        printf("Your information has been updated.\n");
    }
    else
    {
        printf("\nStudent record not found!\n");
    }
}