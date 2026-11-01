#include <stdio.h>
#include "contact.h"

int main() 
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook);   // Initialize address book and load contacts from file

    do 
    {
        // -------- Menu Display --------
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save and Exit\n");       
        // printf("7. Exit\n");   // Optional extra exit option
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');  // Flush newline from input buffer
         
        // -------- Menu Actions --------
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);   // Add new contact
                break;
            case 2:
                searchContact(&addressBook);   // Search existing contact
                break;
            case 3:
                editContact(&addressBook);     // Edit contact details
                break;
            case 4:
                deleteContact(&addressBook);   // Delete a contact
                break;
            case 5:          
                listContacts(&addressBook);    // Display all contacts
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);   // Save contacts before exit
                break;
            default:
                printf("Invalid choice. Please try again.\n");   // Handle wrong input
        }
    } while (choice != 6);   // Loop until user chooses Save and Exit
    
    return 0;   // End program
}
