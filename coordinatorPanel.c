#include "coordinatorPanel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================= INPUT FUNCTIONS ================= */

void readString(char str[], int size)
{
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0';
}

int readInt()
{
    char input[50];
    int value;

    while (1)
    {
        fgets(input, sizeof(input), stdin);

        if (sscanf(input, "%d", &value) == 1)
        {
            return value;
        }

        printf("Invalid input! Enter a number: ");
    }
}

/* ================= FACULTY DASHBOARD ================= */

void facultyDashboard(char userID[])
{
    int choice;

    while (1)
    {
        printf("\n===========================================\n");
        printf("          FACULTY PANEL (ID: %s)\n", userID);
        printf("===========================================\n");

        printf("1. Create New Event\n");
        printf("2. Edit Event Details\n");
        printf("3. Delete Event\n");
        printf("4. View Applied Volunteers & Mark Attendance\n");
        printf("5. Assign Rank & Certificate to Volunteer\n");
        printf("6. Issue Event Certificate to Student\n");
        printf("7. Logout\n");

        printf("-------------------------------------------\n");
        printf("Enter Choice: ");

        choice = readInt();

        switch (choice)
        {
        case 1:
            createEvent();
            break;

        case 2:
            editEvent();
            break;

        case 3:
            deleteEvent();
            break;

        case 4:
            markVolunteerAttendance();
            break;

        case 5:
            giveCertificateAndRankToVolunteer();
            break;

        case 6:
            issueCertificateToStudent();
            break;

        case 7:
            printf("\nLogging out from Faculty Panel...\n");
            return;

        default:
            printf("\nInvalid Choice! Try again.\n");
        }
    }
}

/* ================= CREATE EVENT ================= */

void createEvent(void)
{
    FILE *fp;
    Event ev;

    fp = fopen("events.txt", "a");

    if (fp == NULL)
    {
        printf("\nError opening events.txt!\n");
        return;
    }

    printf("\n===========================================\n");
    printf("              CREATE NEW EVENT\n");
    printf("===========================================\n");
    printf("Enter 0 to go back.\n\n");

    printf("Enter Event ID: ");
    ev.id = readInt();

    if (ev.id == 0)
    {
        fclose(fp);
        return;
    }

    printf("Enter Category: ");
    readString(ev.category, sizeof(ev.category));

    printf("Enter Event Name: ");
    readString(ev.name, sizeof(ev.name));

    printf("Enter Date: ");
    readString(ev.date, sizeof(ev.date));

    printf("Enter Time Slot: ");
    readString(ev.time, sizeof(ev.time));

    printf("Enter Base Price: ");
    ev.capacity = readInt();

    printf("Enter Available Seats: ");
    ev.availableSeats = readInt();

    /*
       Event data is stored using spaces.
       So do not use spaces inside
       Category, Event Name, Date or Time.
    */

    fprintf(fp, "%d %s %s %s %s %d %d\n",
            ev.id,
            ev.category,
            ev.name,
            ev.date,
            ev.time,
            ev.capacity,
            ev.availableSeats);

    fclose(fp);

    printf("\n===========================================\n");
    printf("       Event Created Successfully!\n");
    printf("===========================================\n");
}

/* ================= EDIT EVENT ================= */

void editEvent(void)
{
    FILE *fp;
    FILE *temp;

    char line[500];
    int targetID;
    int found = 0;

    fp = fopen("events.txt", "r");

    if (fp == NULL)
    {
        printf("\nNo events found!\n");
        return;
    }

    printf("\n===========================================\n");
    printf("                 EDIT EVENT\n");
    printf("===========================================\n");
    printf("Enter 0 to go back.\n\n");

    printf("Enter Event ID to Edit: ");
    targetID = readInt();

    if (targetID == 0)
    {
        fclose(fp);
        return;
    }

    temp = fopen("temp_events.txt", "w");

    if (temp == NULL)
    {
        fclose(fp);
        printf("\nError creating temporary file!\n");
        return;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        int currentID;

        /* Get Event ID from current line */
        if (sscanf(line, "%d", &currentID) != 1)
        {
            fprintf(temp, "%s", line);
            continue;
        }

        /* If Event ID matches */
        if (currentID == targetID)
        {
            Event ev;

            found = 1;

            printf("\n===========================================\n");
            printf("               EVENT FOUND!\n");
            printf("===========================================\n");

            ev.id = targetID;

            printf("Enter New Category: ");
            readString(ev.category, sizeof(ev.category));

            printf("Enter New Event Name: ");
            readString(ev.name, sizeof(ev.name));

            printf("Enter New Date: ");
            readString(ev.date, sizeof(ev.date));

            printf("Enter New Time Slot: ");
            readString(ev.time, sizeof(ev.time));

            printf("Enter New Base Price: ");
            ev.capacity = readInt();

            printf("Enter New Available Seats: ");
            ev.availableSeats = readInt();

            fprintf(temp,
                    "%d %s %s %s %s %d %d\n",
                    ev.id,
                    ev.category,
                    ev.name,
                    ev.date,
                    ev.time,
                    ev.capacity,
                    ev.availableSeats);
        }
        else
        {
            /* Keep other events unchanged */
            fprintf(temp, "%s", line);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("events.txt");

    if (rename("temp_events.txt", "events.txt") != 0)
    {
        printf("\nError updating events file!\n");
        return;
    }

    if (found)
    {
        printf("\n===========================================\n");
        printf("       EVENT UPDATED SUCCESSFULLY!\n");
        printf("===========================================\n");
    }
    else
    {
        printf("\nEvent ID %d not found!\n", targetID);
    }
}

/* ================= DELETE EVENT ================= */

void deleteEvent(void)
{
    FILE *fp;
    FILE *temp;

    Event ev;
    int targetID;
    int deleted = 0;

    fp = fopen("events.txt", "r");

    if (fp == NULL)
    {
        printf("\nNo events found!\n");
        return;
    }

    printf("\n===========================================\n");
    printf("              DELETE EVENT\n");
    printf("===========================================\n");
    printf("Enter 0 to go back.\n\n");

    printf("Enter Event ID to Delete: ");
    targetID = readInt();

    if (targetID == 0)
    {
        fclose(fp);
        return;
    }

    temp = fopen("temp_events.txt", "w");

    if (temp == NULL)
    {
        fclose(fp);
        printf("\nError creating temporary file!\n");
        return;
    }

    while (fscanf(fp,
                  "%d %49s %49s %49s %49s %d %d",
                  &ev.id,
                  ev.category,
                  ev.name,
                  ev.date,
                  ev.time,
                  &ev.capacity,
                  &ev.availableSeats) == 7)
    {
        if (ev.id == targetID)
        {
            deleted = 1;
            continue;
        }

        fprintf(temp,
                "%d %s %s %s %s %d %d\n",
                ev.id,
                ev.category,
                ev.name,
                ev.date,
                ev.time,
                ev.capacity,
                ev.availableSeats);
    }

    fclose(fp);
    fclose(temp);

    remove("events.txt");
    rename("temp_events.txt", "events.txt");

    if (deleted)
    {
        printf("\n===========================================\n");
        printf("       Event Deleted Successfully!\n");
        printf("===========================================\n");
    }
    else
    {
        printf("\nEvent ID %d not found!\n", targetID);
    }
}

/* ================= VOLUNTEER ATTENDANCE ================= */

void markVolunteerAttendance(void)
{
    FILE *fp;
    FILE *temp;

    char id[30];
    char eventName[50];
    char rank[20];
    char status[20];

    char targetID[30];
    char targetEvent[50];

    int count = 0;
    int found = 0;
    int choice;

    fp = fopen("volunteer.txt", "r");

    if (fp == NULL)
    {
        printf("\nNo volunteer applications found!\n");
        return;
    }

    printf("\n=====================================================================\n");
    printf("                    VOLUNTEER PARTICIPATION LIST\n");
    printf("=====================================================================\n");

    printf("%-15s | %-25s | %-10s | %-10s\n",
           "Volunteer ID",
           "Event Name",
           "Rank",
           "Status");

    printf("---------------------------------------------------------------------\n");

    while (fscanf(fp,
                  "%29s \"%49[^\"]\" %19s %19s",
                  id,
                  eventName,
                  rank,
                  status) == 4)
    {
        printf("%-15s | %-25s | %-10s | %-10s\n",
               id,
               eventName,
               rank,
               status);

        count++;
    }

    fclose(fp);

    if (count == 0)
    {
        printf("\nNo volunteer applications found!\n");
        return;
    }

    printf("\nEnter 0 to go back.\n");

    printf("\nEnter Volunteer ID: ");
    readString(targetID, sizeof(targetID));

    if (strcmp(targetID, "0") == 0)
    {
        return;
    }

    printf("Enter Event Name: ");
    readString(targetEvent, sizeof(targetEvent));

    printf("\n1. Present\n");
    printf("2. Absent\n");
    printf("0. Back\n");

    printf("Enter Attendance Choice: ");
    choice = readInt();

    if (choice == 0)
    {
        return;
    }

    if (choice != 1 && choice != 2)
    {
        printf("\nInvalid attendance choice!\n");
        return;
    }

    fp = fopen("volunteer.txt", "r");
    temp = fopen("temp_volunteer.txt", "w");

    if (fp == NULL || temp == NULL)
    {
        if (fp != NULL)
            fclose(fp);

        if (temp != NULL)
            fclose(temp);

        printf("\nFile error!\n");
        return;
    }

    while (fscanf(fp,
                  "%29s \"%49[^\"]\" %19s %19s",
                  id,
                  eventName,
                  rank,
                  status) == 4)
    {
        if (strcmp(id, targetID) == 0 &&
            strcmp(eventName, targetEvent) == 0)
        {
            found = 1;

            if (choice == 1)
            {
                strcpy(status, "Present");
            }
            else
            {
                strcpy(status, "Absent");
            }
        }

        fprintf(temp,
                "%s \"%s\" %s %s\n",
                id,
                eventName,
                rank,
                status);
    }

    fclose(fp);
    fclose(temp);

    remove("volunteer.txt");
    rename("temp_volunteer.txt", "volunteer.txt");

    if (found)
    {
        printf("\n===========================================\n");
        printf("       Attendance Updated Successfully!\n");
        printf("===========================================\n");

        printf("Volunteer ID : %s\n", targetID);
        printf("Event        : %s\n", targetEvent);

        if (choice == 1)
            printf("Status       : Present\n");
        else
            printf("Status       : Absent\n");
    }
    else
    {
        printf("\nVolunteer ID or Event Name not found!\n");
    }
}

/* ================= VOLUNTEER RANK + CERTIFICATE ================= */

void giveCertificateAndRankToVolunteer(void)
{
    FILE *fp;

    char vID[30];
    char rank[20];

    printf("\n===========================================\n");
    printf("        VOLUNTEER RANK & CERTIFICATE\n");
    printf("===========================================\n");

    printf("Enter 0 to go back.\n\n");

    printf("Enter Volunteer ID: ");
    readString(vID, sizeof(vID));

    if (strcmp(vID, "0") == 0)
    {
        return;
    }

    printf("Enter Rank (Gold/Silver/Bronze): ");
    readString(rank, sizeof(rank));

    if (strcmp(rank, "Gold") != 0 &&
        strcmp(rank, "Silver") != 0 &&
        strcmp(rank, "Bronze") != 0)
    {
        printf("\nInvalid Rank!\n");
        printf("Please use Gold, Silver or Bronze.\n");
        return;
    }

    fp = fopen("volunteerCertificates.txt", "a");

    if (fp == NULL)
    {
        printf("\nError opening certificate file!\n");
        return;
    }

    fprintf(fp,
            "%s \"Rank: %s | Certificate Issued\"\n",
            vID,
            rank);

    fclose(fp);

    printf("\n===========================================\n");
    printf("   Rank & Certificate Issued Successfully!\n");
    printf("===========================================\n");
}

/* ================= STUDENT CERTIFICATE ================= */

void issueCertificateToStudent(void)
{
    FILE *fp;

    char studentID[30];
    char eventName[50];
    char issueDate[20];

    printf("\n===========================================\n");
    printf("          STUDENT CERTIFICATE\n");
    printf("===========================================\n");

    printf("Enter 0 to go back.\n\n");

    printf("Enter Student ID: ");
    readString(studentID, sizeof(studentID));

    if (strcmp(studentID, "0") == 0)
    {
        return;
    }

    printf("Enter Event Name: ");
    readString(eventName, sizeof(eventName));

    printf("Enter Issue Date (DD-MM-YYYY): ");
    readString(issueDate, sizeof(issueDate));

    fp = fopen("certificate.txt", "a");

    if (fp == NULL)
    {
        printf("\nError opening certificate.txt!\n");
        return;
    }

    fprintf(fp,
            "%s \"%s\" %s\n",
            studentID,
            eventName,
            issueDate);

    fclose(fp);

    printf("\n===========================================\n");
    printf("     Certificate Issued Successfully!\n");
    printf("===========================================\n");

    printf("Student ID : %s\n", studentID);
    printf("Event      : %s\n", eventName);
    printf("Issue Date : %s\n", issueDate);
}