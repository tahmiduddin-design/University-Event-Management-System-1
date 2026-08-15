#include "common.h"
#include "studentLogin.h"
#include "viewEvents.h"

void studentDashboard(char userID[]) {
    int choice;
    while (1) {
        printf("\n===========================================\n");
        printf("         STUDENT DASHBOARD (ID: %s)        \n", userID);
        printf("===========================================\n");
        printf("1. View Upcoming Events & Register\n");
        printf("2. My Profile & Participation History\n");
        printf("3. My Certificates\n");
        printf("4. Edit Profile (Name, Phone, Password)\n");
        printf("5. Logout\n");
        printf("-------------------------------------------\n");
        printf("Enter Choice: ");
        if (scanf("%d", &choice) != 1) {
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1: showUpcomingEvents(userID); break;
            case 2: viewStudentProfile(userID); break;
            case 3: viewStudentCertificates(userID); break;
            case 4: editStudentProfile(userID); break;
            case 5: printf("\nLogging out from Student Panel...\n"); return;
            default: printf("\nInvalid Choice! Try again.\n");
        }
    }
}

void viewStudentProfile(char userID[]) {
    FILE *fp = fopen("student_history.txt", "r");
    printf("\n===========================================\n");
    printf("         MY PARTICIPATION HISTORY          \n");
    printf("===========================================\n");

    if (fp == NULL) {
        printf("No history found for ID: %s.\n", userID);
        return;
    }

    char id[30], eventName[50], status1[20], status2[20];
    float amount;
    int found = 0;

    while (fscanf(fp, "%s \"%[^\"]\" %f %s %s", id, eventName, &amount, status1, status2) != EOF) {
        if (strcmp(id, userID) == 0) {
            printf("Event: %-22s | Paid: BDT %.2f | Status: %s\n", eventName, amount, status2);
            found = 1;
        }
    }
    fclose(fp);

    if (!found) printf("No events registered yet.\n");
}

void viewStudentCertificates(char userID[]) {
    FILE *fp = fopen("certificate.txt", "r");
    printf("\n===========================================\n");
    printf("               MY CERTIFICATES             \n");
    printf("===========================================\n");

    if (fp == NULL) {
        printf("No certificates issued yet.\n");
        return;
    }

    char id[30], eventName[50], issueDate[20];
    int found = 0;

    while (fscanf(fp, "%s \"%[^\"]\" %s", id, eventName, issueDate) != EOF) {
        if (strcmp(id, userID) == 0) {
            printf("Certificate Issued for: %s (Date: %s)\n", eventName, issueDate);
            found = 1;
        }
    }
    fclose(fp);

    if (!found) printf("No certificates found.\n");
}

void editStudentProfile(char userID[]) {
    FILE *fp = fopen("registration.txt", "r");
    if (fp == NULL) {
        printf("\nUser database error!\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("\nTemporary file creation error!\n");
        fclose(fp);
        return;
    }

    User u;
    int updated = 0;

    while (fscanf(fp, "%s %s %s %s %s %d", u.id, u.name, u.dept, u.phone, u.password, &u.role) != EOF) {
        if (strcmp(u.id, userID) == 0 && u.role == 1) {
            updated = 1;
            printf("\n===========================================\n");
            printf("            EDIT MY PROFILE                \n");
            printf("===========================================\n");
            printf("Current Name      : %s\n", u.name);
            printf("Current Dept      : %s\n", u.dept);
            printf("Current Phone     : %s\n", u.phone);
            printf("-------------------------------------------\n");

            printf("Enter New Full Name: ");
            scanf("%s", u.name);
            clearBuffer();

            printf("Enter New Department: ");
            scanf("%s", u.dept);
            clearBuffer();

            printf("Enter New Phone Number: ");
            scanf("%s", u.phone);
            clearBuffer();

            printf("Enter New Password: ");
            scanf("%s", u.password);
            clearBuffer();
        }
        fprintf(temp, "%s %s %s %s %s %d\n", u.id, u.name, u.dept, u.phone, u.password, u.role);
    }

    fclose(fp);
    fclose(temp);

    remove("registration.txt");
    rename("temp.txt", "registration.txt");

    if (updated) {
        printf("\nProfile updated successfully! New password and info saved.\n");
    } else {
        printf("\nStudent record not found!\n");
    }
}