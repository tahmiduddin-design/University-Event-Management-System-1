#include "adminPanel.h"

void adminDashboard(char userID[]) {
    int choice;
    while (1) {
        printf("\n===========================================\n");
        printf("            ADMIN PANEL (ID: %s)          \n", userID);
        printf("===========================================\n");
        printf("1. View System Summary & Total Revenue\n");
        printf("2. View All Registered Users\n");
        printf("3. Search Student by ID\n");
        printf("4. Delete Student Record\n");
        printf("5. View All Payment Records\n");
        printf("6. Logout\n");
        printf("-------------------------------------------\n");
        printf("Enter Choice: ");
        if (scanf("%d", &choice) != 1) {
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1: viewSystemSummaryAndRevenue(); break;
            case 2: viewAllUsers(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: searchPayment(); break;
            case 6: printf("\nLogging out from Admin Panel...\n"); return;
            default: printf("\nInvalid Choice! Try again.\n");
        }
    }
}

void viewSystemSummaryAndRevenue() {
    int studentCount = 0, volunteerCount = 0;
    float totalRevenue = 0.0;

    FILE *fpUser = fopen("registration.txt", "r");
    if (fpUser != NULL) {
        User u;
        while (fscanf(fpUser, "%s %s %s %s %s %d", u.id, u.name, u.dept, u.phone, u.password, &u.role) != EOF) {
            if (u.role == 1) studentCount++;
            else if (u.role == 2) volunteerCount++;
        }
        fclose(fpUser);
    }

    FILE *fpPay = fopen("student_history.txt", "r");
    if (fpPay != NULL) {
        char id[30], evName[50], s1[20], s2[20];
        float amount;
        while (fscanf(fpPay, "%s \"%[^\"]\" %f %s %s", id, evName, &amount, s1, s2) != EOF) {
            totalRevenue += amount;
        }
        fclose(fpPay);
    }

    printf("\n===========================================\n");
    printf("         SYSTEM OVERVIEW & REVENUE         \n");
    printf("===========================================\n");
    printf("Total Registered Students   : %d\n", studentCount);
    printf("Total Registered Volunteers : %d\n", volunteerCount);
    printf("-------------------------------------------\n");
    printf("Total Collected Revenue     : BDT %.2f\n", totalRevenue);
    printf("===========================================\n");
}

void viewAllUsers() {
    FILE *fp = fopen("registration.txt", "r");
    if (fp == NULL) {
        printf("\nNo registered users found.\n");
        return;
    }

    printf("\n===================================================================================\n");
    printf("                               ALL REGISTERED USERS                                \n");
    printf("===================================================================================\n");
    printf("%-10s | %-20s | %-8s | %-12s | %s\n", "ID", "Name", "Dept", "Phone", "Role");
    printf("-----------------------------------------------------------------------------------\n");

    User u;
    while (fscanf(fp, "%s %s %s %s %s %d", u.id, u.name, u.dept, u.phone, u.password, &u.role) != EOF) {
        char roleName[20];
        if (u.role == 1) strcpy(roleName, "Student");
        else if (u.role == 2) strcpy(roleName, "Volunteer");
        else strcpy(roleName, "Other");

        printf("%-10s | %-20s | %-8s | %-12s | %s\n", u.id, u.name, u.dept, u.phone, roleName);
    }
    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen("registration.txt", "r");
    if (fp == NULL) { printf("\nNo user database found.\n"); return; }

    char targetID[30];
    printf("\nEnter Student ID to Search: "); scanf("%s", targetID); clearBuffer();

    User u;
    int found = 0;
    while (fscanf(fp, "%s %s %s %s %s %d", u.id, u.name, u.dept, u.phone, u.password, &u.role) != EOF) {
        if (strcmp(targetID, u.id) == 0 && u.role == 1) {
            printf("\nStudent Found!\nID: %s | Name: %s | Dept: %s | Phone: %s\n", u.id, u.name, u.dept, u.phone);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) printf("\nStudent ID not found.\n");
}

void deleteStudent() {
    FILE *fp = fopen("registration.txt", "r");
    if (fp == NULL) { printf("\nNo user database found.\n"); return; }

    char targetID[30];
    printf("\nEnter Student ID to Delete: "); scanf("%s", targetID); clearBuffer();

    FILE *temp = fopen("temp.txt", "w");
    User u;
    int deleted = 0;

    while (fscanf(fp, "%s %s %s %s %s %d", u.id, u.name, u.dept, u.phone, u.password, &u.role) != EOF) {
        if (strcmp(targetID, u.id) == 0 && u.role == 1) {
            deleted = 1;
            continue;
        }
        fprintf(temp, "%s %s %s %s %s %d\n", u.id, u.name, u.dept, u.phone, u.password, u.role);
    }
    fclose(fp); fclose(temp);
    remove("registration.txt"); rename("temp.txt", "registration.txt");

    if (deleted) printf("\nStudent ID %s deleted successfully!\n", targetID);
    else printf("\nStudent ID not found.\n");
}

void searchPayment() {
    FILE *fp = fopen("student_history.txt", "r");
    if (fp == NULL) { printf("\nNo payment records found.\n"); return; }

    printf("\n=========================================================================\n");
    printf("                          ALL PAYMENT RECORDS                            \n");
    printf("=========================================================================\n");

    char id[30], eventName[50], s1[20], s2[20];
    float amount;

    while (fscanf(fp, "%s \"%[^\"]\" %f %s %s", id, eventName, &amount, s1, s2) != EOF) {
        printf("User ID: %-10s | Event: %-22s | Paid: BDT %.2f | Status: %s\n", id, eventName, amount, s2);
    }
    fclose(fp);
}