#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include "common.h"


// Admin Panel
void adminDashboard(char userID[]);


// Admin Features
void viewSystemSummaryAndRevenue(void);
void viewAllUsers(void);
void searchStudent(void);
void deleteStudent(void);
void searchPayment(void);


#endif