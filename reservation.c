#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOMS 10
typedef struct {
    int roomNumber;
    char guestName[50];
} Reservation;
typedef struct {
    Reservation reservations[MAX_ROOMS];
    int numReservations;
} Hotel;

void initializeHotel(Hotel *hotel) {
    hotel->numReservations = 0;
}

// Function to add a reservation
int addReservation(Hotel *hotel, int roomNumber, const char *guestName) {
    if (hotel->numReservations >= MAX_ROOMS) {
        printf("Error: Maximum reservations reached.\n");
        return -1; // Failed to add reservation
    }

    // Check for room availability
    for (int i = 0; i < hotel->numReservations; ++i) {
        if (hotel->reservations[i].roomNumber == roomNumber) {
            printf("Error: Room %d is already reserved.\n", roomNumber);
            return -1; // Failed to add reservation
        }
    }

    // Add the reservation
    hotel->reservations[hotel->numReservations].roomNumber = roomNumber;
    strncpy(hotel->reservations[hotel->numReservations].guestName, guestName, sizeof(hotel->reservations[0].guestName));
    hotel->numReservations++;

    printf("Reservation added successfully.\n");
    return 0; // Successful reservation
}

// Function to display all reservations
void displayReservations(const Hotel *hotel) {
    printf("Room\tGuest\n");
    for (int i = 0; i < hotel->numReservations; ++i) {
        printf("%d\t%s\n", hotel->reservations[i].roomNumber, hotel->reservations[i].guestName);
    }
}

// Function to find a reservation by room number
int findReservationIndex(const Hotel *hotel, int roomNumber) {
    for (int i = 0; i < hotel->numReservations; ++i) {
        if (hotel->reservations[i].roomNumber == roomNumber) {
            return i; // Return the index of the reservation
        }
    }
    return -1; // Reservation not found
}

// Function to modify a reservation
int modifyReservation(Hotel *hotel, int roomNumber, const char *newGuestName) {
    int index = findReservationIndex(hotel, roomNumber);
    if (index != -1) {
        // Modify the guest name
        strncpy(hotel->reservations[index].guestName, newGuestName, sizeof(hotel->reservations[0].guestName));
        printf("Reservation modified successfully.\n");
        return 0; // Successful modification
    } else {
        printf("Error: Reservation not found.\n");
        return -1; // Failed to modify reservation
    }
}

// Function to cancel a reservation
int cancelReservation(Hotel *hotel, int roomNumber) {
    int index = findReservationIndex(hotel, roomNumber);
    if (index != -1) {
        // Remove the reservation by shifting elements
        for (int i = index; i < hotel->numReservations - 1; ++i) {
            hotel->reservations[i] = hotel->reservations[i + 1];
        }
        hotel->numReservations--;
        printf("Reservation canceled successfully.\n");
        return 0; // Successful cancellation
    } else {
        printf("Error: Reservation not found.\n");
        return -1; // Failed to cancel reservation
    }
}

int main() {
    Hotel hotel;
    initializeHotel(&hotel);

    // Adding some sample reservations
    addReservation(&hotel, 101, "John Doe");
    addReservation(&hotel, 102, "Jane Smith");
    addReservation(&hotel, 103, "Bob Johnson");

    // Displaying all reservations
    printf("\nInitial Reservations:\n");
    displayReservations(&hotel);

    // Try to add a reservation with a conflicting room number
    addReservation(&hotel, 101, "Alice Adams");

    // Displaying all reservations after conflicting reservation attempt
    printf("\nReservations after conflicting attempt:\n");
    displayReservations(&hotel);

    // Modifying a reservation
    modifyReservation(&hotel, 102, "Updated Guest");

    // Displaying all reservations after modification
    printf("\nReservations after modification:\n");
    displayReservations(&hotel);

    // Canceling a reservation
    cancelReservation(&hotel, 103);

    // Displaying all reservations after cancellation
    printf("\nReservations after cancellation:\n");
    displayReservations(&hotel);

    return 0;
}





