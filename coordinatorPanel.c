#include "coordinatorPanel.h"

void facultyDashboard(char userID[]) {
    int choice;
    while (1) {
        printf("\n===========================================\n");
        printf("          FACULTY PANEL (ID: %s)           \n", userID);
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
        if (scanf("%d", &choice) != 1) {
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1: createEvent(); break;
            case 2: editEvent(); break;
            case 3: deleteEvent(); break;
            case 4: markVolunteerAttendance(); break;
            case 5: giveCertificateAndRankToVolunteer(); break;
            case 6: issueCertificateToStudent(); break;
            case 7: printf("\nLogging out from Faculty Panel...\n"); return;
            default: printf("\nInvalid Choice! Try again.\n");
        }
    }
}

void markVolunteerAttendance(void) {
    FILE *fp = fopen("volunteer.txt", "r");
    if (fp == NULL) {
        printf("\nNo volunteers have participated yet.\n");
        return;
    }

    printf("\n=========================================================================\n");
    printf("                  VOLUNTEER PARTICIPATION LIST                           \n");
    printf("=========================================================================\n");
    printf("%-12s | %-25s | %-10s | %s\n", "Volunteer ID", "Event Name", "Rank", "Current Status");
    printf("-------------------------------------------------------------------------\n");

    char id[30], eventName[50], rank[20], status[20];
    int count = 0;
    while (fscanf(fp, "%s \"%[^\"]\" %s %s", id, eventName, rank, status) != EOF) {
        printf("%-12s | %-25s | %-10s | %s\n", id, eventName, rank, status);
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("No volunteer applications found.\n");
        return;
    }

    char targetID[30], targetEvent[50];
    printf("\nEnter Volunteer ID to Mark Attendance: ");
    scanf("%s", targetID);
    clearBuffer();

    printf("Enter Event Name: ");
    scanf(" %[^\n]", targetEvent);
    clearBuffer();

    int attChoice;
    printf("\nSet Attendance:\n1. Present\n2. Absent\nChoice (1-2): ");
    scanf("%d", &attChoice);
    clearBuffer();

    char newStatus[20];
    if (attChoice == 1) strcpy(newStatus, "Present");
    else strcpy(newStatus, "Absent");

    fp = fopen("volunteer.txt", "r");
    FILE *temp = fopen("temp_volunteer.txt", "w");
    int found = 0;

    while (fscanf(fp, "%s \"%[^\"]\" %s %s", id, eventName, rank, status) != EOF) {
        if (strcmp(id, targetID) == 0 && strcmp(eventName, targetEvent) == 0) {
            found = 1;
            fprintf(temp, "%s \"%s\" %s %s\n", id, eventName, rank, newStatus);
        } else {
            fprintf(temp, "%s \"%s\" %s %s\n", id, eventName, rank, status);
        }
    }
    fclose(fp);
    fclose(temp);

    remove("volunteer.txt");
    rename("temp_volunteer.txt", "volunteer.txt");

    if (found) {
        printf("\nSuccess! Attendance updated to '%s' for Volunteer ID: %s.\n", newStatus, targetID);
        FILE *fpNotif = fopen("volunteerCertificates.txt", "a");
        if (fpNotif != NULL) {
            fprintf(fpNotif, "%s \"Attendance for '%s': Marked as %s by Faculty.\"\n", targetID, targetEvent, newStatus);
            fclose(fpNotif);
        }
    } else {
        printf("\nVolunteer ID or Event Name not matched!\n");
    }
}

void createEvent(void) {
    FILE *fp = fopen("events.txt", "a");
    if (fp == NULL) { printf("Error opening file!\n"); return; }

    Event ev;
    printf("\n--- CREATE EVENT ---\n");
    printf("Enter Event ID: "); scanf("%d", &ev.id); clearBuffer();
    printf("Enter Category (Departmental/Club/Alumni): "); scanf("%s", ev.category); clearBuffer();
    printf("Enter Event Name: "); scanf("%s", ev.name); clearBuffer();
    printf("Enter Date: "); scanf("%s", ev.date); clearBuffer();
    printf("Enter Time Slot: "); scanf("%s", ev.time); clearBuffer();
    printf("Enter Base Price: "); scanf("%d", &ev.capacity); clearBuffer();
    printf("Enter Fan Count needed: "); scanf("%d", &ev.availableSeats); clearBuffer();

    fprintf(fp, "%d %s %s %s %s %d %d\n", ev.id, ev.category, ev.name, ev.date, ev.time, ev.capacity, ev.availableSeats);
    fclose(fp);
    printf("\nEvent Created Successfully!\n");
}

void editEvent(void) {
    FILE *fp = fopen("events.txt", "r");
    if (fp == NULL) { printf("\nNo events found.\n"); return; }

    int targetID, found = 0;
    printf("\nEnter Event ID to Edit: "); scanf("%d", &targetID); clearBuffer();

    FILE *temp = fopen("temp_events.txt", "w");
    Event ev;

    while (fscanf(fp, "%d %s %s %s %s %d %d", &ev.id, ev.category, ev.name, ev.date, ev.time, &ev.capacity, &ev.availableSeats) != EOF) {
        if (ev.id == targetID) {
            found = 1;
            printf("Enter New Category: "); scanf("%s", ev.category); clearBuffer();
            printf("Enter New Name: "); scanf("%s", ev.name); clearBuffer();
            printf("Enter New Date: "); scanf("%s", ev.date); clearBuffer();
            printf("Enter New Time: "); scanf("%s", ev.time); clearBuffer();
            printf("Enter New Base Price: "); scanf("%d", &ev.capacity); clearBuffer();
        }
        fprintf(temp, "%d %s %s %s %s %d %d\n", ev.id, ev.category, ev.name, ev.date, ev.time, ev.capacity, ev.availableSeats);
    }
    fclose(fp); fclose(temp);
    remove("events.txt"); rename("temp_events.txt", "events.txt");

    if (found) printf("\nEvent ID %d updated successfully!\n", targetID);
    else printf("\nEvent ID %d not found!\n", targetID);
}

void deleteEvent(void) {
    FILE *fp = fopen("events.txt", "r");
    if (fp == NULL) { printf("\nNo events found.\n"); return; }

    int targetID, deleted = 0;
    printf("\nEnter Event ID to Delete: "); scanf("%d", &targetID); clearBuffer();

    FILE *temp = fopen("temp_events.txt", "w");
    Event ev;

    while (fscanf(fp, "%d %s %s %s %s %d %d", &ev.id, ev.category, ev.name, ev.date, ev.time, &ev.capacity, &ev.availableSeats) != EOF) {
        if (ev.id == targetID) { deleted = 1; continue; }
        fprintf(temp, "%d %s %s %s %s %d %d\n", ev.id, ev.category, ev.name, ev.date, ev.time, ev.capacity, ev.availableSeats);
    }
    fclose(fp); fclose(temp);
    remove("events.txt"); rename("temp_events.txt", "events.txt");

    if (deleted) printf("\nEvent ID %d deleted successfully!\n", targetID);
    else printf("\nEvent ID %d not found!\n", targetID);
}

void giveCertificateAndRankToVolunteer(void) {
    char vID[30], rank[20];
    printf("\n--- RANK & CERTIFICATE ISSUANCE (VOLUNTEER) ---\n");
    printf("Enter Volunteer ID: "); scanf("%s", vID); clearBuffer();
    printf("Enter Rank (Gold/Silver/Bronze): "); scanf("%s", rank); clearBuffer();

    FILE *fp = fopen("volunteerCertificates.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "%s \"You received rank %s and a Certificate for your service!\"\n", vID, rank);
        fclose(fp);
        printf("\nCertificate & Rank notification sent to Volunteer ID: %s!\n", vID);
    }
}

void issueCertificateToStudent(void) {
    char sID[30], eventName[50], issueDate[20];
    printf("\n--- ISSUE CERTIFICATE TO STUDENT ---\n");
    printf("Enter Student ID: "); scanf("%s", sID); clearBuffer();
    printf("Enter Event Name: "); scanf(" %[^\n]", eventName); clearBuffer();
    printf("Enter Issue Date (DD-MM-YYYY): "); scanf("%s", issueDate); clearBuffer();

    FILE *fp = fopen("certificate.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "%s \"%s\" %s\n", sID, eventName, issueDate);
        fclose(fp);
        printf("\nCertificate issued successfully for Student ID: %s!\n", sID);
    }
}