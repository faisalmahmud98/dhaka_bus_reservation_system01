#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Bus {
    int busNumber;
    char name[50];
    char source[50];
    char destination[50];
    char stops[200];
    int totalSeats;
    int availableSeats;
    float fare;           
};

struct User {
    char username[50];
    char password[50];
};

void displayMainMenu() {
    printf("\n=== Dhaka Bus Reservation: Main Menu ===\n");
    printf("1. Login\n");
    printf("2. Exit\n");
    printf("Enter your choice: ");
}

void displayUserMenu() {
    printf("\n=== User Menu ===\n");
    printf("1. Book a Ticket\n");
    printf("2. Cancel a Ticket\n");
    printf("3. Check Bus Status\n");
    printf("4. View All Buses\n");
    printf("5. Logout\n");
    printf("Enter your choice: ");
}

int loginUser(struct User users[], int numUsers, char username[], char password[]) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

int findBus(struct Bus buses[], int numBuses, int busNumber) {
    for (int i = 0; i < numBuses; i++) {
        if (buses[i].busNumber == busNumber) return i;
    }
    return -1;
}

void viewAllBuses(struct Bus buses[], int numBuses) {
    printf("\n%-5s %-20s %-14s %-14s %-6s %-8s\n",
           "No.", "Bus Name", "From", "To", "Seats", "Fare(Tk)");
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < numBuses; i++) {
        printf("%-5d %-20s %-14s %-14s %-6d %-8.0f\n",
               buses[i].busNumber, buses[i].name, buses[i].source,
               buses[i].destination, buses[i].availableSeats, buses[i].fare);
    }
}

void bookTicket(struct Bus buses[], int numBuses) {
    viewAllBuses(buses, numBuses);
    printf("\nEnter Bus Number: ");
    int busNumber;
    scanf("%d", &busNumber);

    int idx = findBus(buses, numBuses, busNumber);
    if (idx == -1) {
        printf("Bus Number %d not found.\n", busNumber);
        return;
    }

    printf("Enter Number of Seats: ");
    int seats;
    scanf("%d", &seats);

    if (seats <= 0) {
        printf("Invalid number of seats.\n");
    } else if (buses[idx].availableSeats < seats) {
        printf("Sorry, only %d seats are available.\n", buses[idx].availableSeats);
    } else {
        buses[idx].availableSeats -= seats;
        printf("Booking successful! %d seat(s) on %s (%s -> %s).\n",
               seats, buses[idx].name, buses[idx].source, buses[idx].destination);
        printf("Total fare: %.0f Tk\n", seats * buses[idx].fare);
    }
}

void cancelTicket(struct Bus buses[], int numBuses) {
    printf("\nEnter Bus Number: ");
    int busNumber;
    scanf("%d", &busNumber);

    int idx = findBus(buses, numBuses, busNumber);
    if (idx == -1) {
        printf("Bus Number %d not found.\n", busNumber);
        return;
    }

    printf("Enter Number of Seats to Cancel: ");
    int seats;
    scanf("%d", &seats);

    if (seats <= 0) {
        printf("Invalid number of seats.\n");
    } else if (seats > buses[idx].totalSeats - buses[idx].availableSeats) {
        printf("Error: You can't cancel more seats than were booked.\n");
    } else {
        buses[idx].availableSeats += seats;
        printf("Cancellation successful! %d seat(s) canceled on %s.\n",
               seats, buses[idx].name);
        printf("Refund: %.0f Tk\n", seats * buses[idx].fare);
    }
}

void checkBusStatus(struct Bus buses[], int numBuses) {
    printf("\nEnter Bus Number: ");
    int busNumber;
    scanf("%d", &busNumber);

    int idx = findBus(buses, numBuses, busNumber);
    if (idx == -1) {
        printf("Bus Number %d not found.\n", busNumber);
        return;
    }

    printf("\nBus Number     : %d\n", buses[idx].busNumber);
    printf("Bus Name       : %s\n", buses[idx].name);
    printf("Route          : %s -> %s\n", buses[idx].source, buses[idx].destination);
    printf("Stoppages      : %s\n", buses[idx].stops);
    printf("Total Seats    : %d\n", buses[idx].totalSeats);
    printf("Available Seats: %d\n", buses[idx].availableSeats);
    printf("Fare           : %.0f Tk\n", buses[idx].fare);
}

int main() {
    struct User users[5] = {
        {"user1", "pass1"}, {"user2", "pass2"}, {"user3", "pass3"},
        {"user4", "pass4"}, {"user5", "pass5"},
    };
    int numUsers = 5;

    struct Bus buses[6] = {
        {101, "Bihanga Paribahan", "Mirpur-12", "Sadarghat",
         "Mirpur-10, Kazipara, Agargaon, Farmgate, Shahbag, Paltan, Gulistan",
         40, 40, 40.0},
        {102, "Victor Classic", "Gabtoli", "Motijheel",
         "Mohammadpur, Asad Gate, Dhanmondi, Shahbag, Paltan",
         40, 40, 35.0},
        {103, "Turag Paribahan", "Uttara", "Sadarghat",
         "Airport, Banani, Mohakhali, Farmgate, Shahbag, Gulistan",
         45, 45, 50.0},
        {104, "Balaka", "Mirpur-1", "Jatrabari",
         "Mirpur-10, Technical, Shyamoli, Farmgate, Gulistan, Sayedabad",
         40, 40, 45.0},
        {105, "Anabil Super", "Uttara", "Motijheel",
         "Abdullahpur, Airport, Khilkhet, Banani, Mohakhali, Malibagh, Kamalapur",
         36, 36, 55.0},
        {106, "Akash Paribahan", "Savar", "Gulistan",
         "Aminbazar, Gabtoli, Mohammadpur, Asad Gate, Farmgate, Shahbag",
         40, 40, 60.0},
    };
    int numBuses = 6;

    int loggedInUserId = -1;

    while (1) {
        if (loggedInUserId == -1) {
            displayMainMenu();
            int choice;
            scanf("%d", &choice);

            if (choice == 1) {
                char username[50], password[50];
                printf("Enter Username: ");
                scanf("%49s", username);
                printf("Enter Password: ");
                scanf("%49s", password);

                loggedInUserId = loginUser(users, numUsers, username, password);
                if (loggedInUserId == -1)
                    printf("Login failed. Please check your username and password.\n");
                else
                    printf("Login successful. Welcome, %s!\n", username);
            } else if (choice == 2) {
                printf("Exiting the program.\n");
                break;
            } else {
                printf("Invalid choice. Please try again.\n");
            }
        } else {
            displayUserMenu();
            int userChoice;
            scanf("%d", &userChoice);

            switch (userChoice) {
            case 1: bookTicket(buses, numBuses); break;
            case 2: cancelTicket(buses, numBuses); break;
            case 3: checkBusStatus(buses, numBuses); break;
            case 4: viewAllBuses(buses, numBuses); break;
            case 5:
                printf("Logging out.\n");
                loggedInUserId = -1;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            }
        }
    }
    return 0;
}
