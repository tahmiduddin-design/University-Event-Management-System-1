#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[20];
    char name[50];
    char dept[30];
    char phone[20];
    char password[50];
    int role;
} User;

typedef struct {
    int id;
    char category[30];
    char name[50];
    char date[20];
    char time[20];
    int capacity;
    int availableSeats;
} Event;

extern Event eventList[];
extern int eventCount;

void clearBuffer(void);

#endif