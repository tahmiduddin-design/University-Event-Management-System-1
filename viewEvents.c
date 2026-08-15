#include <stdio.h>
#include <string.h>
#include "viewEvents.h"

/* ================= SECRET CODES ================= */

#define CLUB_SECRET_CODE "CLUB2026"
#define DEPT_SECRET_CODE "DEPT10"
#define ALUMNI_SECRET_CODE "ALUMNI2026"

/* ================= EVENT LIST ================= */

Event eventList[100];
int eventCount = 0;

/* ================= DEFAULT EVENTS ================= */

void createDefaultEvents(void)
{
    eventList[0] = (Event){1, "Departmental", "CSEFest2026",
                           "15-09-2026", "09:00AM-11:00AM", 500, 50};

    eventList[1] = (Event){2, "Club", "ProgrammingContest",
                           "16-09-2026", "10:00AM-01:00PM", 300, 80};

    eventList[2] = (Event){3, "Club", "RoboticsWorkshop",
                           "18-09-2026", "02:00PM-04:00PM", 200, 60};

    eventList[3] = (Event){4, "Departmental", "TechSeminar",
                           "19-09-2026", "09:00AM-06:00PM", 400, 100};

    eventList[4] = (Event){5, "Club", "CulturalFest",
                           "21-09-2026", "04:00PM-08:00PM", 300, 120};

    eventList[5] = (Event){6, "Alumni", "AlumniReunion",
                           "22-09-2026", "10:00AM-04:00PM", 500, 150};

    eventList[6] = (Event){7, "Club", "SportsTournament",
                           "24-09-2026", "09:00AM-05:00PM", 250, 80};

    eventList[7] = (Event){8, "Departmental", "OrientationProgram",
                           "25-09-2026", "10:00AM-12:00PM", 100, 200};

    eventList[8] = (Event){9, "Alumni", "Convocation",
                           "27-09-2026", "09:00AM-02:00PM", 1000, 300};

    eventList[9] = (Event){10, "Departmental", "FoundationDay",
                           "28-09-2026", "10:00AM-06:00PM", 200, 500};

    eventCount = 10;
}

/* ================= SAVE EVENTS ================= */

void saveEvents(void)
{
    FILE *fp = fopen("events.txt", "w");

    if (fp == NULL)
    {
        printf("\nError saving events!\n");
        return;
    }

    for (int i = 0; i < eventCount; i++)
    {
        fprintf(fp,
                "%d %s %s %s %s %d %d\n",
                eventList[i].id,
                eventList[i].category,
                eventList[i].name,
                eventList[i].date,
                eventList[i].time,
                eventList[i].capacity,
                eventList[i].availableSeats);
    }

    fclose(fp);
}

/* ================= LOAD EVENTS ================= */

void loadEvents(void)
{
    FILE *fp;
    Event ev;

    eventCount = 0;

    fp = fopen("events.txt", "r");

    /*
       If events.txt does not exist,
       create the 10 default events.
    */

    if (fp == NULL)
    {
        createDefaultEvents();
        saveEvents();
        return;
    }

    /*
       Read events from file
    */

    while (fscanf(fp,
                  "%d %29s %49s %19s %19s %d %d",
                  &ev.id,
                  ev.category,
                  ev.name,
                  ev.date,
                  ev.time,
                  &ev.capacity,
                  &ev.availableSeats) == 7)
    {
        eventList[eventCount] = ev;
        eventCount++;

        if (eventCount >= 100)
        {
            break;
        }
    }

    fclose(fp);

    /*
       If file exists but contains nothing,
       restore the 10 default events.
    */

    if (eventCount == 0)
    {
        createDefaultEvents();
        saveEvents();
    }
}

/* ================= SHOW EVENTS ================= */

void showUpcomingEvents(char userID[])
{
    int choice;

    loadEvents();

    printf("\n=========================================================================\n");
    printf("                         UPCOMING EVENTS LIST\n");
    printf("=========================================================================\n");

    if (eventCount == 0)
    {
        printf("No events available right now.\n");
        return;
    }

    /* ================= DISPLAY EVENTS ================= */

    for (int i = 0; i < eventCount; i++)
    {
        printf("\nID        : %d\n", eventList[i].id);
        printf("Type      : %s\n", eventList[i].category);
        printf("Name      : %s\n", eventList[i].name);
        printf("Date      : %s\n", eventList[i].date);
        printf("Time      : %s\n", eventList[i].time);
        printf("Base Fee  : BDT %d\n", eventList[i].capacity);
        printf("Seats     : %d\n", eventList[i].availableSeats);

        printf("-------------------------------------------------------------------------\n");
    }

    /* ================= EVENT MENU ================= */

    printf("\n1. Register for an Event\n");
    printf("2. Back to Student Dashboard\n");

    printf("-------------------------------------------\n");
    printf("Enter Choice: ");

    if (scanf("%d", &choice) != 1)
    {
        clearBuffer();
        printf("\nInvalid input!\n");
        return;
    }

    clearBuffer();

    /* ================= BACK ================= */

    if (choice == 2)
    {
        return;
    }

    /* ================= REGISTER ================= */

    if (choice != 1)
    {
        printf("\nInvalid Choice!\n");
        return;
    }

    int selectedID;

    printf("\nEnter Event ID to Register: ");

    if (scanf("%d", &selectedID) != 1)
    {
        clearBuffer();
        printf("\nInvalid Event ID!\n");
        return;
    }

    clearBuffer();

    /* ================= FIND EVENT ================= */

    int foundIndex = -1;

    for (int i = 0; i < eventCount; i++)
    {
        if (eventList[i].id == selectedID)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        printf("\nInvalid Event ID!\n");
        return;
    }

    /* ================= CHECK SEATS ================= */

    if (eventList[foundIndex].availableSeats <= 0)
    {
        printf("\nSorry! No seats are available for this event.\n");
        return;
    }

    float basePrice = eventList[foundIndex].capacity;

    printf("\n===========================================\n");
    printf("             SELECTED EVENT\n");
    printf("===========================================\n");

    printf("Event Name : %s\n", eventList[foundIndex].name);
    printf("Event Type : %s\n", eventList[foundIndex].category);
    printf("Date       : %s\n", eventList[foundIndex].date);
    printf("Time       : %s\n", eventList[foundIndex].time);
    printf("Base Fee   : BDT %.2f\n", basePrice);

    /* ================= CONFIRM ================= */

    int confirm;

    printf("\nConfirm Payment & Registration?\n");
    printf("1. Pay Now\n");
    printf("2. Cancel\n");

    printf("Enter Choice: ");

    if (scanf("%d", &confirm) != 1)
    {
        clearBuffer();
        printf("\nInvalid input!\n");
        return;
    }

    clearBuffer();

    if (confirm == 2)
    {
        printf("\nRegistration Cancelled.\n");
        return;
    }

    if (confirm != 1)
    {
        printf("\nInvalid Choice!\n");
        return;
    }

    /* ================= DISCOUNT ================= */

    printf("\n==================================================\n");
    printf("              SELECT DISCOUNT CATEGORY\n");
    printf("==================================================\n");

    printf("1. Club Member        (20%% Discount)\n");
    printf("2. Department Student (10%% Discount)\n");
    printf("3. Alumni             (100%% Free)\n");
    printf("4. General Student    (No Discount)\n");
    printf("5. Back\n");

    printf("--------------------------------------------------\n");
    printf("Select Option: ");

    int categoryChoice;

    if (scanf("%d", &categoryChoice) != 1)
    {
        clearBuffer();
        printf("\nInvalid input!\n");
        return;
    }

    clearBuffer();

    /* ================= BACK ================= */

    if (categoryChoice == 5)
    {
        printf("\nReturning to Event Menu...\n");
        return;
    }

    if (categoryChoice < 1 || categoryChoice > 4)
    {
        printf("\nInvalid Discount Category!\n");
        return;
    }

    float discount = 0.0;

    char discountText[60];

    strcpy(discountText, "0% (General Student)");

    char proofCode[30];

    /* ================= CLUB ================= */

    if (categoryChoice == 1)
    {
        printf("\nEnter Club Membership Secret Code: ");
        scanf("%29s", proofCode);
        clearBuffer();

        if (strcmp(proofCode, CLUB_SECRET_CODE) == 0)
        {
            discount = basePrice * 0.20;

            strcpy(discountText,
                   "20% (Club Member Verified)");

            printf("\nProof Verified Successfully!\n");
        }
        else
        {
            printf("\nInvalid Club Code!\n");
            printf("No discount applied.\n");
        }
    }

    /* ================= DEPARTMENT ================= */

    else if (categoryChoice == 2)
    {
        printf("\nEnter Department Verification Code: ");
        scanf("%29s", proofCode);
        clearBuffer();

        if (strcmp(proofCode, DEPT_SECRET_CODE) == 0)
        {
            discount = basePrice * 0.10;

            strcpy(discountText,
                   "10% (Department Student Verified)");

            printf("\nProof Verified Successfully!\n");
        }
        else
        {
            printf("\nInvalid Department Code!\n");
            printf("No discount applied.\n");
        }
    }

    /* ================= ALUMNI ================= */

    else if (categoryChoice == 3)
    {
        printf("\nEnter Alumni Verification Code: ");
        scanf("%29s", proofCode);
        clearBuffer();

        if (strcmp(proofCode, ALUMNI_SECRET_CODE) == 0)
        {
            discount = basePrice;

            strcpy(discountText,
                   "100% (Alumni Verified - Free Entry)");

            printf("\nAlumni Verified Successfully!\n");
        }
        else
        {
            printf("\nInvalid Alumni Code!\n");
            printf("Regular fee will be applied.\n");
        }
    }

    /* ================= GENERAL ================= */

    else
    {
        discount = 0.0;

        strcpy(discountText,
               "0% (General Student)");
    }

    /* ================= FINAL PAYMENT ================= */

    float finalPayable = basePrice - discount;

    printf("\n==================================================\n");
    printf("                FINAL PAYMENT RECEIPT\n");
    printf("==================================================\n");

    printf("Event Name        : %s\n",
           eventList[foundIndex].name);

    printf("Original Base Fee : BDT %.2f\n",
           basePrice);

    printf("Applied Discount  : %s\n",
           discountText);

    printf("Discount Amount   : - BDT %.2f\n",
           discount);

    printf("--------------------------------------------------\n");

    printf("Total Paid Amount : BDT %.2f\n",
           finalPayable);

    printf("==================================================\n");

    /* ================= SAVE PAYMENT ================= */

    FILE *fp = fopen("student_history.txt", "a");

    if (fp == NULL)
    {
        printf("\nPayment file error!\n");
        return;
    }

    fprintf(fp,
            "%s \"%s\" %.2f Paid Completed\n",
            userID,
            eventList[foundIndex].name,
            finalPayable);

    fclose(fp);

    /* ================= REDUCE SEAT ================= */

    eventList[foundIndex].availableSeats--;

    /* Save updated seat count */

    saveEvents();

    /* ================= SUCCESS ================= */

    printf("\n===========================================\n");
    printf("        PAYMENT SUCCESSFUL!\n");
    printf("===========================================\n");

    printf("You are registered for: %s\n",
           eventList[foundIndex].name);

    printf("Remaining Seats: %d\n",
           eventList[foundIndex].availableSeats);
}