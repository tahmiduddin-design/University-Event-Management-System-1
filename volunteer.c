#include "volunteer.h"

void volunteerDashboard(char userID[]) {
    int choice;
    while (1) {
        printf("\n===========================================\n");
        printf("        VOLUNTEER DASHBOARD (ID: %s)       \n", userID);
        printf("===========================================\n");
        printf("1. Apply / Participate in an Event\n");
        printf("2. View My Tasks & Status\n");
        printf("3. Notifications & Certificates\n");
        printf("4. Logout\n");
        printf("-------------------------------------------\n");
        printf("Enter Choice: ");
        if (scanf("%d", &choice) != 1) {
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1: applyForVolunteerEvent(userID); break;
            case 2: viewVolunteerTasks(userID); break;
            case 3: viewVolunteerCertificates(userID); break;
            case 4: printf("\nLogging out from Volunteer Panel...\n"); return;
            default: printf("\nInvalid Choice! Try again.\n");
        }
    }
}

void applyForVolunteerEvent(char userID[]) {
    char eventName[50];
    printf("\n--- PARTICIPATE AS VOLUNTEER ---\n");
    printf("Enter Event Name to Volunteer: ");
    scanf(" %[^\n]", eventName);
    clearBuffer();

    FILE *fp = fopen("volunteer.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "%s \"%s\" None Applied\n", userID, eventName);
        fclose(fp);
        printf("\nSuccessfully Applied for %s! Visible in Faculty Panel.\n", eventName);
    } else {
        printf("File opening error!\n");
    }
}

void viewVolunteerTasks(char userID[]) {
    FILE *fp = fopen("volunteer.txt", "r");
    printf("\n===========================================\n");
    printf("            MY APPLIED EVENTS              \n");
    printf("===========================================\n");
    if (fp == NULL) {
        printf("No volunteer records found.\n");
        return;
    }

    char id[30], eventName[50], rank[20], status[20];
    int found = 0;
    while (fscanf(fp, "%s \"%[^\"]\" %s %s", id, eventName, rank, status) != EOF) {
        if (strcmp(id, userID) == 0) {
            printf("Event: %-20s | Attendance/Status: %s\n", eventName, status);
            found = 1;
        }
    }
    fclose(fp);

    if (!found) printf("You haven't participated in any events yet.\n");
}

void viewVolunteerCertificates(char userID[]) {
    FILE *fp = fopen("volunteerCertificates.txt", "r");
    printf("\n===========================================\n");
    printf("        NOTIFICATIONS & CERTIFICATES       \n");
    printf("===========================================\n");
    if (fp == NULL) {
        printf("No notifications yet.\n");
        return;
    }

    char id[30], msg[200];
    int found = 0;
    while (fscanf(fp, "%s \"%[^\"]\"", id, msg) != EOF) {
        if (strcmp(id, userID) == 0) {
            printf(">> %s\n", msg);
            found = 1;
        }
    }
    fclose(fp);

    if (!found) printf("No notifications found.\n");
}