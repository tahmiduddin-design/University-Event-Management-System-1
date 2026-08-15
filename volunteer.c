#include <stdio.h>
#include <string.h>
#include "volunteer.h"

/* ================= VOLUNTEER DASHBOARD ================= */

void volunteerDashboard(char userID[])
{
    int choice;

    while (1)
    {
        printf("\n===========================================\n");
        printf("        VOLUNTEER DASHBOARD (ID: %s)\n", userID);
        printf("===========================================\n");
        printf("1. Apply / Participate in an Event\n");
        printf("2. View My Tasks & Status\n");
        printf("3. Notifications & Certificates\n");
        printf("4. Logout\n");
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
            applyForVolunteerEvent(userID);
            break;

        case 2:
            viewVolunteerTasks(userID);
            break;

        case 3:
            viewVolunteerCertificates(userID);
            break;

        case 4:
            printf("\nLogging out from Volunteer Panel...\n");
            return;

        default:
            printf("\nInvalid Choice! Please try again.\n");
        }
    }
}


/* ================= APPLY FOR EVENT ================= */

void applyForVolunteerEvent(char userID[])
{
    char eventName[50];
    int choice;

    printf("\n===========================================\n");
    printf("        VOLUNTEER EVENT APPLICATION\n");
    printf("===========================================\n");

    printf("Enter Event Name: ");
    fgets(eventName, sizeof(eventName), stdin);
    eventName[strcspn(eventName, "\n")] = '\0';

    /* Empty input check */
    if (strlen(eventName) == 0)
    {
        printf("\nEvent name cannot be empty!\n");
        return;
    }

    /* Back option */
    if (strcmp(eventName, "0") == 0)
    {
        printf("\nReturning to Volunteer Dashboard...\n");
        return;
    }

    /* Check whether already applied */
    FILE *fp = fopen("volunteer.txt", "r");

    if (fp != NULL)
    {
        char id[30];
        char oldEvent[50];
        char rank[20];
        char status[20];

        while (fscanf(fp,
                      "%29s \"%49[^\"]\" %19s %19s",
                      id,
                      oldEvent,
                      rank,
                      status) == 4)
        {
            if (strcmp(id, userID) == 0 &&
                strcmp(oldEvent, eventName) == 0)
            {
                fclose(fp);

                printf("\nYou have already applied for this event!\n");
                return;
            }
        }

        fclose(fp);
    }

    printf("\n-------------------------------------------\n");
    printf("Event Name : %s\n", eventName);
    printf("-------------------------------------------\n");
    printf("1. Confirm Application\n");
    printf("2. Back\n");
    printf("Enter Choice: ");

    if (scanf("%d", &choice) != 1)
    {
        clearBuffer();
        printf("\nInvalid input!\n");
        return;
    }

    clearBuffer();

    if (choice == 2)
    {
        printf("\nReturning to Volunteer Dashboard...\n");
        return;
    }

    if (choice != 1)
    {
        printf("\nInvalid Choice!\n");
        return;
    }

    /* Save application */
    fp = fopen("volunteer.txt", "a");

    if (fp == NULL)
    {
        printf("\nError opening volunteer.txt!\n");
        return;
    }

    fprintf(fp,
            "%s \"%s\" None Applied\n",
            userID,
            eventName);

    fclose(fp);

    printf("\n===========================================\n");
    printf("       APPLICATION SUCCESSFUL!\n");
    printf("===========================================\n");
    printf("Volunteer ID : %s\n", userID);
    printf("Event        : %s\n", eventName);
    printf("Status       : Applied\n");
    printf("-------------------------------------------\n");
    printf("Your application is now visible to Faculty.\n");
}


/* ================= VIEW MY TASKS ================= */

void viewVolunteerTasks(char userID[])
{
    FILE *fp;

    char id[30];
    char eventName[50];
    char rank[20];
    char status[20];

    int found = 0;
    int choice;

    printf("\n===========================================\n");
    printf("            MY APPLIED EVENTS\n");
    printf("===========================================\n");

    fp = fopen("volunteer.txt", "r");

    if (fp == NULL)
    {
        printf("\nNo volunteer records found.\n");

        printf("\n1. Back\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);
        clearBuffer();

        return;
    }

    printf("%-25s | %-10s | %-10s\n",
           "Event Name",
           "Rank",
           "Status");

    printf("-------------------------------------------\n");

    while (fscanf(fp,
                  "%29s \"%49[^\"]\" %19s %19s",
                  id,
                  eventName,
                  rank,
                  status) == 4)
    {
        if (strcmp(id, userID) == 0)
        {
            printf("%-25s | %-10s | %-10s\n",
                   eventName,
                   rank,
                   status);

            found = 1;
        }
    }

    fclose(fp);

    if (!found)
    {
        printf("You haven't applied for any events yet.\n");
    }

    printf("\n-------------------------------------------\n");
    printf("1. Back\n");
    printf("Enter Choice: ");

    if (scanf("%d", &choice) != 1)
    {
        clearBuffer();
        return;
    }

    clearBuffer();
}


/* ================= NOTIFICATIONS & CERTIFICATES ================= */

void viewVolunteerCertificates(char userID[])
{
    FILE *fp;

    char id[30];
    char msg[200];

    int found = 0;
    int choice;

    printf("\n===========================================\n");
    printf("       NOTIFICATIONS & CERTIFICATES\n");
    printf("===========================================\n");

    fp = fopen("volunteerCertificates.txt", "r");

    if (fp == NULL)
    {
        printf("\nNo notifications yet.\n");

        printf("\n1. Back\n");
        printf("Enter Choice: ");

        if (scanf("%d", &choice) != 1)
            clearBuffer();
        else
            clearBuffer();

        return;
    }

    while (fscanf(fp,
                  "%29s \"%199[^\"]\"",
                  id,
                  msg) == 2)
    {
        if (strcmp(id, userID) == 0)
        {
            printf("\n>> %s\n", msg);
            found = 1;
        }
    }

    fclose(fp);

    if (!found)
    {
        printf("\nNo notifications or certificates found.\n");
    }

    printf("\n-------------------------------------------\n");
    printf("1. Back\n");
    printf("Enter Choice: ");

    if (scanf("%d", &choice) != 1)
    {
        clearBuffer();
        return;
    }

    clearBuffer();
}