#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ---------------- STRUCTURES ---------------- */

struct User {
    char username[30];
    char password[30];
};

struct Bike {
    char name[50];
    int baseFare;
};

struct Ride {
    int rideID;
    char name[100];
    char from[40];
    char to[40];
    char bike[40];
    int distance;
    int totalFare;
};

/* ---------------- GLOBAL STORAGE ---------------- */

struct User users[5] = {
    {"user", "1234"},
    {"krishna", "9999"}
};
int userCount = 2;

struct Bike bikes[6] = {
    {"Scooty", 30},
    {"Sports Bike", 50},
    {"Electric Bike", 40},
    {"Royal Enfield", 80}
};
int bikeCount = 4;

struct Ride rideHistory[20];
int rideCount = 0;

/* ---------------- LOGIN SYSTEM ---------------- */

int loginSystem() {
    char uname[30], pass[30];

    printf("\n=========== LOGIN ===========\n");
    printf("Username: ");
    scanf("%s", uname);
    printf("Password: ");
    scanf("%s", pass);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(uname, users[i].username) == 0 &&
            strcmp(pass, users[i].password) == 0) {
            printf("? Login Successful!\n");
            return 1;
        }
    }

    printf("? Invalid Login!\n");
    return 0;
}

/* ---------------- DISPLAY FUNCTIONS ---------------- */

void displayAreas(const char *areas[], int count) {
    printf("\nAvailable Areas:\n");
    for (int i = 0; i < count; i++)
        printf("%d. %s\n", i + 1, areas[i]);
}

void displayBikes() {
    printf("\nAvailable Bikes:\n");
    for (int i = 0; i < bikeCount; i++)
        printf("%d. %s - Base Fare ?%d/km\n", i + 1, bikes[i].name, bikes[i].baseFare);
}

/* ---------------- MAIN PROGRAM ---------------- */

int main() {
    srand(time(0));

    const char *areas[] = {
        "Ameerpet", "SR Nagar", "Madhapur", "Gachibowli",
        "Kukatpally", "KPHB", "Dilsukhnagar", "LB Nagar"
    };
    int areaCount = 8;

    int distances[8][8] = {
        {0,5,7,10,12,15,18,20},
        {5,0,6,9,11,14,17,19},
        {7,6,0,5,7,10,13,15},
        {10,9,5,0,4,7,10,12},
        {12,11,7,4,0,5,8,10},
        {15,14,10,7,5,0,5,7},
        {18,17,13,10,8,5,0,5},
        {20,19,15,12,10,7,5,0}
    };

    int menu = 0;
    int from, to, bikeChoice, distance, totalFare;
    char riderName[100];
    char timeSlot[20];
    int paymentChoice;
    int rideID;   // ? declared OUTSIDE switch (error FIXED)

    printf("\n?? MEGA INTER-CITY BIKE BOOKING SYSTEM ??\n");

    if (!loginSystem()) return 0;

    do {
        printf("\n========== USER MENU ==========\n");
        printf("1. Book a Ride\n");
        printf("2. View Ride History\n");
        printf("3. Cancel Last Ride\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &menu);

        switch (menu) {

        /* -------- BOOK RIDE -------- */
        case 1: {
            displayAreas(areas, areaCount);

            printf("\nEnter Pickup Area: ");
            scanf("%d", &from);
            printf("Enter Drop Area: ");
            scanf("%d", &to);

            if (from < 1 || to < 1 || from > areaCount || to > areaCount || from == to) {
                printf("? Invalid Area Selection!\n");
                break;
            }

            distance = distances[from - 1][to - 1];

            displayBikes();
            printf("\nSelect Bike: ");
            scanf("%d", &bikeChoice);

            if (bikeChoice < 1 || bikeChoice > bikeCount) {
                printf("? Invalid Bike!\n");
                break;
            }

            printf("Enter Ride Time (Morning / Afternoon / Night): ");
            scanf("%s", timeSlot);

            totalFare = bikes[bikeChoice - 1].baseFare * distance;

            if (strcmp(timeSlot, "Night") == 0)
                totalFare += 50;
            else if (strcmp(timeSlot, "Morning") == 0)
                totalFare += 20;

            printf("\nDistance: %d KM\n", distance);
            printf("Total Fare: ?%d\n", totalFare);

            printf("\nPayment Mode:\n1. Wallet\n2. Card\nChoose: ");
            scanf("%d", &paymentChoice);

            getchar();
            printf("Enter Rider Name: ");
            fgets(riderName, sizeof(riderName), stdin);
            riderName[strcspn(riderName, "\n")] = 0;

            rideID = rand() % 90000 + 10000;

            strcpy(rideHistory[rideCount].name, riderName);
            strcpy(rideHistory[rideCount].from, areas[from - 1]);
            strcpy(rideHistory[rideCount].to, areas[to - 1]);
            strcpy(rideHistory[rideCount].bike, bikes[bikeChoice - 1].name);
            rideHistory[rideCount].distance = distance;
            rideHistory[rideCount].totalFare = totalFare;
            rideHistory[rideCount].rideID = rideID;

            rideCount++;

            printf("\n? RIDE BOOKED SUCCESSFULLY!\n");

            printf("\n========== DIGITAL RIDE RECEIPT ==========\n");
            printf("Ride ID    : %d\n", rideID);
            printf("Rider Name : %s\n", riderName);
            printf("From       : %s\n", areas[from - 1]);
            printf("To         : %s\n", areas[to - 1]);
            printf("Bike       : %s\n", bikes[bikeChoice - 1].name);
            printf("Distance   : %d KM\n", distance);
            printf("Ride Time  : %s\n", timeSlot);
            printf("Total Fare : ?%d\n", totalFare);
            printf("==========================================\n");
            break;
        }

        /* -------- VIEW HISTORY -------- */
        case 2:
            if (rideCount == 0) {
                printf("\nNo ride history found!\n");
            } else {
                printf("\n======= RIDE HISTORY =======\n");
                for (int i = 0; i < rideCount; i++) {
                    printf("\nRide %d\n", i + 1);
                    printf("Ride ID : %d\n", rideHistory[i].rideID);
                    printf("Name    : %s\n", rideHistory[i].name);
                    printf("From    : %s\n", rideHistory[i].from);
                    printf("To      : %s\n", rideHistory[i].to);
                    printf("Bike    : %s\n", rideHistory[i].bike);
                    printf("Fare    : ?%d\n", rideHistory[i].totalFare);
                }
            }
            break;

        /* -------- CANCEL LAST RIDE -------- */
        case 3:
            if (rideCount > 0) {
                rideCount--;
                printf("\n? Last ride cancelled successfully!\n");
            } else {
                printf("\n? No ride to cancel!\n");
            }
            break;

        case 4:
            printf("\nThank you for using the Bike Booking System!\n");
            break;

        default:
            printf("? Invalid Option!\n");
        }

    } while (menu != 4);

    return 0;
}

