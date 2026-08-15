#include "common.h"
#include "menu.h"

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void showMainMenu() {
    int choice;
    while (1) {
        printf("\n===========================================\n");
        printf("    UNIVERSITY EVENT MANAGEMENT SYSTEM     \n");
        printf("===========================================\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("-------------------------------------------\n");
        printf("Enter Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            clearBuffer();
            printf("\nInvalid Choice! Try again.\n");
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3:
                printf("\nExiting System. Goodbye!\n");
                exit(0);
            default: printf("\nInvalid Choice!\n");
        }
    }
}

void registerUser() {
    FILE *fp = fopen("registration.txt", "a");
    if (fp == NULL) {
        printf("File opening error!\n");
        return;
    }

    User u;
    printf("\n===========================================\n");
    printf("             USER REGISTRATION             \n");
    printf("===========================================\n");
    printf("Select Role:\n1. Student\n2. Volunteer\n");
    printf("-------------------------------------------\n");
    printf("Enter Role (1-2): ");
    
    if (scanf("%d", &u.role) != 1) {
        clearBuffer();
        printf("\nInvalid input!\n");
        fclose(fp);
        return;
    }
    clearBuffer();

    if (u.role < 1 || u.role > 2) {
        printf("\nInvalid Role selected!\n");
        fclose(fp);
        return;
    }

    printf("Enter ID: ");
    scanf("%s", u.id); clearBuffer();

    printf("Enter Full Name: ");
    scanf("%s", u.name); clearBuffer();

    printf("Enter Department: ");
    scanf("%s", u.dept); clearBuffer();

    printf("Enter Phone Number: ");
    scanf("%s", u.phone); clearBuffer();

    printf("Enter Password: ");
    scanf("%s", u.password); clearBuffer();

    fprintf(fp, "%s %s %s %s %s %d\n", u.id, u.name, u.dept, u.phone, u.password, u.role);
    fclose(fp);

    printf("\nRegistration Successful! You can now log in.\n");
}

void loginUser() {
    char inputID[20], pass[30];

    printf("\n===========================================\n");
    printf("                USER LOGIN                 \n");
    printf("===========================================\n");
    printf("Enter ID: ");
    scanf("%s", inputID); clearBuffer();

    printf("Enter Password: ");
    scanf("%s", pass); clearBuffer();

    // 1. Direct Default Admin Login Check
    if (strcmp(inputID, "admin") == 0 && strcmp(pass, "admin123") == 0) {
        printf("\nLogin Successful! Welcome, System Administrator.\n");
        adminDashboard("admin");
        return;
    }

    // 2. Direct Default Faculty Login Check
    if (strcmp(inputID, "faculty") == 0 && strcmp(pass, "faculty123") == 0) {
        printf("\nLogin Successful! Welcome, Faculty Member.\n");
        facultyDashboard("faculty");
        return;
    }

    // 3. Check Registered Students and Volunteers from File
    FILE *fp = fopen("registration.txt", "r");
    if (fp == NULL) {
        printf("\nNo registered users found or invalid credentials!\n");
        return;
    }

    User u;
    int found = 0;

    while (fscanf(fp, "%s %s %s %s %s %d", u.id, u.name, u.dept, u.phone, u.password, &u.role) != EOF) {
        if (strcmp(inputID, u.id) == 0 && strcmp(pass, u.password) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found == 1) {
        printf("\nLogin Successful! Welcome, %s (%s).\n", u.name, u.id);

        if (u.role == 1) studentDashboard(u.id);
        else if (u.role == 2) volunteerDashboard(u.id);
    } else {
        printf("\nInvalid ID or Password!\n");
    }
}