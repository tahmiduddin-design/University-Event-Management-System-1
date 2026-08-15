#include "viewEvents.h"

// Secret Verification Codes for Proof
#define CLUB_SECRET_CODE "CLUB2026"
#define DEPT_SECRET_CODE "DEPT10"
#define ALUMNI_SECRET_CODE "ALUMNI2026"

Event eventList[10] = {
    {1, "Departmental", "CSE Fest 2026",        "15-09-2026", "09:00 AM - 11:00 AM", 500, 50},
    {2, "Club",         "Programming Contest",  "16-09-2026", "10:00 AM - 01:00 PM", 300, 80},
    {3, "Club",         "Robotics Workshop",   "18-09-2026", "02:00 PM - 04:00 PM", 200, 60},
    {4, "Departmental", "Tech Seminar",         "19-09-2026", "09:00 AM - 06:00 PM", 400, 100},
    {5, "Club",         "Cultural Fest",        "21-09-2026", "04:00 PM - 08:00 PM", 300, 120},
    {6, "Alumni",       "Alumni Reunion",       "22-09-2026", "10:00 AM - 04:00 PM", 500, 150},
    {7, "Club",         "Sports Tournament",    "24-09-2026", "09:00 AM - 05:00 PM", 250, 80},
    {8, "Departmental", "Orientation Program",  "25-09-2026", "10:00 AM - 12:00 PM", 100, 200},
    {9, "Alumni",       "Convocation",          "27-09-2026", "09:00 AM - 02:00 PM", 1000, 300},
    {10,"Departmental", "Foundation Day",       "28-09-2026", "10:00 AM - 06:00 PM", 200, 500}
};

void showUpcomingEvents(char userID[]) {
    printf("\n=========================================================================\n");
    printf("                           UPCOMING EVENTS LIST                          \n");
    printf("=========================================================================\n");

    for (int i = 0; i < 10; i++) {
        printf("ID: %d | Type: %-12s | Name: %s\n", eventList[i].id, eventList[i].category, eventList[i].name);
        printf("Date: %s | Time: %s | Base Fee: BDT %d\n", eventList[i].date, eventList[i].time, eventList[i].capacity);
        printf("-------------------------------------------------------------------------\n");
    }

    int choice;
    printf("\n1. Register for an Event\n2. Back to Dashboard\nEnter Choice: ");
    if (scanf("%d", &choice) != 1) {
        clearBuffer();
        return;
    }
    clearBuffer();

    if (choice == 1) {
        int selectedID;
        printf("Enter Event ID to Register: ");
        scanf("%d", &selectedID);
        clearBuffer();

        int foundIndex = -1;
        for (int i = 0; i < 10; i++) {
            if (eventList[i].id == selectedID) {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex != -1) {
            float basePrice = eventList[foundIndex].capacity;

            printf("\nSelected Event : %s", eventList[foundIndex].name);
            printf("\nEvent Type     : %s", eventList[foundIndex].category);
            printf("\nBase Fee       : BDT %.2f\n", basePrice);

            int confirm;
            printf("\nConfirm Payment & Registration?\n");
            printf("1. Pay Now (Confirm)\n");
            printf("2. Cancel\n");
            printf("Choice: ");
            scanf("%d", &confirm);
            clearBuffer();

            if (confirm == 1) {
                printf("\n==================================================\n");
                printf("             SELECT YOUR DISCOUNT CATEGORY        \n");
                printf("==================================================\n");
                printf("1. Club Member         (20%% Discount - Proof Required)\n");
                printf("2. Department Student  (10%% Discount - Proof Required)\n");
                printf("3. Alumni              (100%% Free     - Proof Required)\n");
                printf("4. General Student     (No Discount)\n");
                printf("--------------------------------------------------\n");
                printf("Select Option (1-4): ");

                int categoryChoice;
                scanf("%d", &categoryChoice);
                clearBuffer();

                float discount = 0.0;
                char discountText[60] = "No Discount";
                char proofCode[30];

                if (categoryChoice == 1) {
                    printf("Enter Club Membership Secret Code: ");
                    scanf("%s", proofCode);
                    clearBuffer();

                    if (strcmp(proofCode, CLUB_SECRET_CODE) == 0) {
                        discount = basePrice * 0.20;
                        strcpy(discountText, "20% (Club Member Verified)");
                        printf(">> Proof Verified Successfully!\n");
                    } else {
                        printf(">> Invalid Club Code! No discount applied.\n");
                        discount = 0.0;
                    }
                } else if (categoryChoice == 2) {
                    printf("Enter Department Verification Code: ");
                    scanf("%s", proofCode);
                    clearBuffer();

                    if (strcmp(proofCode, DEPT_SECRET_CODE) == 0) {
                        discount = basePrice * 0.10;
                        strcpy(discountText, "10% (Department Student Verified)");
                        printf(">> Proof Verified Successfully!\n");
                    } else {
                        printf(">> Invalid Department Code! No discount applied.\n");
                        discount = 0.0;
                    }
                } else if (categoryChoice == 3) {
                    printf("Enter Alumni Verification Passcode: ");
                    scanf("%s", proofCode);
                    clearBuffer();

                    if (strcmp(proofCode, ALUMNI_SECRET_CODE) == 0) {
                        discount = basePrice;
                        strcpy(discountText, "100% (Alumni Verified - Free Entry)");
                        printf(">> Alumni Verified Successfully!\n");
                    } else {
                        printf(">> Invalid Alumni Passcode! Regular fee applied.\n");
                        discount = 0.0;
                    }
                } else {
                    discount = 0.0;
                    strcpy(discountText, "0% (General Student)");
                }

                float finalPayable = basePrice - discount;

                // Show Receipt After Verification
                printf("\n==================================================\n");
                printf("                 FINAL PAYMENT RECEIPT            \n");
                printf("==================================================\n");
                printf("Event Name        : %s\n", eventList[foundIndex].name);
                printf("Original Base Fee : BDT %.2f\n", basePrice);
                printf("Applied Discount  : %s\n", discountText);
                printf("Discount Amount   : - BDT %.2f\n", discount);
                printf("--------------------------------------------------\n");
                printf("Total Paid Amount : BDT %.2f\n", finalPayable);
                printf("==================================================\n");

                FILE *fp = fopen("student_history.txt", "a");
                if (fp != NULL) {
                    fprintf(fp, "%s \"%s\" %.2f Paid Completed\n", userID, eventList[foundIndex].name, finalPayable);
                    fclose(fp);
                }
                printf("Payment Successful! You are registered for %s.\n", eventList[foundIndex].name);
            } else {
                printf("\nRegistration Cancelled!\n");
            }
        } else {
            printf("\nInvalid Event ID! Please select an ID from the list.\n");
        }
    }
}