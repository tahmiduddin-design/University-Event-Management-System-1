#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// User Structure
typedef struct {
    char id[20];
    char name[50];
    char dept[30];
    char phone[20];
    char password[30];
    int role;
} User;

// Event Structure
typedef struct {
    int id;
    char category[30];
    char name[50];
    char date[15];
    char time[30];
    int capacity;
    int availableSeats;
} Event;

void clearBuffer();

// Dashboard Function Prototypes
void studentDashboard(char userID[]);
void volunteerDashboard(char userID[]);
void facultyDashboard(char userID[]);
void adminDashboard(char userID[]);

#endif