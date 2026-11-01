#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "validation.h"


void listContacts(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0) 
    {
        printf("No contacts found.\n");
        return;   // Exit if no contacts exist
    }

    printf("\n--- Contact List ---\n");
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        // Print each contact’s details
        printf("Contact %d:\n", i + 1);
        printf("  Name : %s\n", addressBook->contacts[i].name);
        printf("  Phone: %s\n", addressBook->contacts[i].phone);
        printf("  Email: %s\n", addressBook->contacts[i].email);
        printf("----------------------\n");   // Separator for readability
    }
}





void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;   // Reset contact count at program start
    loadContactsFromFile(addressBook);   // Load existing contacts from file into memory
}


void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}




void createContact(AddressBook *addressBook) {
    Contact newContact;   // Temporary contact to store user input
    int attempts = 0;     // Counter for validation attempts

    // ---------------- Name Validation ----------------
    while (attempts < 3) 
    {
        printf("Enter Name: ");
        scanf("%s", newContact.name);

        // Validate name using rules (first character must be alphabet)
        if (validateName(newContact.name)) break;

        printf("Invalid Name! First character must be an alphabet.\n");
        attempts++;
    }
    if (attempts == 3)   // Stop if maximum attempts reached
    {
        printf("Maximum attempts reached for Name.\n");
        return;
    }

    // ---------------- Phone Validation ----------------
    attempts = 0;
    while (attempts < 3) 
    {
        printf("Enter Phone: ");
        scanf("%s", newContact.phone);

        // Validate phone: must be 10 digits, start with 6–9, and unique
        if (validatePhone(addressBook, newContact.phone)) break;

        printf("Invalid Phone! Must be 10 digits, start with 6–9, and unique.\n");
        attempts++;
    }
    if (attempts == 3)   // Stop if maximum attempts reached
    {
        printf("Maximum attempts reached for Phone.\n");
        return;
    }

    // ---------------- Email Validation ----------------
    attempts = 0;
    while (attempts < 3) 
    {
        printf("Enter Email: ");
        scanf("%49s", newContact.email);

        // Validate email: must start with alphabet, contain '@', end with .com, 
        // have 5 letters between, and be unique
        if (validateEmail(addressBook, newContact.email)) break;

        printf("Invalid Email! Must start with alphabet, contain one '@', end with .com, have 5 letters between, and be unique.\n");
        attempts++;
    }
    if (attempts == 3)   // Stop if maximum attempts reached
    {
        printf("Maximum attempts reached for Email.\n");
        return;
    }

    // ---------------- Store Contact ----------------
    // If all validations pass, add contact to address book
    addressBook->contacts[addressBook->contactCount++] = newContact;
    printf("Contact added successfully!\n");
}





void searchContact(AddressBook *addressBook) {
    if (addressBook->contactCount == 0) {
        printf("No contacts available to search.\n");
        return;   // Exit if no contacts exist
    }

    int choice;
    char query[50];       // Input buffer for search query
    int attempts = 0;     // Counter for search attempts

    while (attempts < 3) {
        // -------- Search Menu --------
        printf("\nSearch by:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Exit Search\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        int found = 0; // Flag to track if any match is found

        switch (choice) {
            case 1: // -------- Search by Name --------
                printf("Enter Name to search: ");
                scanf("%49s", query);

                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].name, query) == 0) {
                        if (!found) {
                            printf("\nContacts with name '%s':\n", query);
                        }
                        printf("Name : %s | Phone: %s | Email: %s\n",
                               addressBook->contacts[i].name,
                               addressBook->contacts[i].phone,
                               addressBook->contacts[i].email);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("No contact found with that Name.\n");
                }
                break;

            case 2: // -------- Search by Phone --------
                printf("Enter Phone to search: ");
                scanf("%49s", query);

                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].phone, query) == 0) {
                        if (!found) {
                            printf("\nContacts with phone '%s':\n", query);
                        }
                        printf("Name : %s | Phone: %s | Email: %s\n",
                               addressBook->contacts[i].name,
                               addressBook->contacts[i].phone,
                               addressBook->contacts[i].email);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("No contact found with that Phone.\n");
                }
                break;

            case 3: // -------- Search by Email --------
                printf("Enter Email to search: ");
                scanf("%49s", query);

                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].email, query) == 0) {
                        if (!found) {
                            printf("\nContacts with email '%s':\n", query);
                        }
                        printf("Name : %s | Phone: %s | Email: %s\n",
                               addressBook->contacts[i].name,
                               addressBook->contacts[i].phone,
                               addressBook->contacts[i].email);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("No contact found with that Email.\n");
                }
                break;

            case 4: // -------- Exit Option --------
                printf("Exiting search...\n");
                return;

            default: // -------- Invalid Choice --------
                printf("Invalid choice. Please try again.\n");
        }

        attempts++;   // Increment attempt counter
    }

    if (attempts == 3) {
        printf("Maximum attempts reached for Search.\n");   // Stop after 3 failed attempts
    }
}





void editContact(AddressBook *addressBook) {
    if (addressBook->contactCount == 0) {
        printf("No contacts available to edit.\n");
        return;   // Exit if no contacts exist
    }

    int choice;
    char query[50];
    printf("\nEdit by:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Exit Edit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    int foundIndex = -1;   // Index of contact to edit

    switch (choice) {
        case 1: { // -------- Edit by Name --------
            printf("Enter Name to edit: ");
            scanf("%49s", query);

            int matches[50], matchCount = 0;   // Track duplicate matches
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].name, query) == 0) {
                    matches[matchCount++] = i;
                }
            }

            if (matchCount == 0) {
                printf("No contact found with that Name.\n");
                return;
            }

            // Show all matches for duplicate names
            printf("\nContacts with name '%s':\n", query);
            for (int j = 0; j < matchCount; j++) {
                int idx = matches[j];
                printf("[%d] Name : %s | Phone: %s | Email: %s\n",
                       idx, addressBook->contacts[idx].name,
                       addressBook->contacts[idx].phone,
                       addressBook->contacts[idx].email);
            }

            // Pick index to edit
            printf("Enter index of contact to edit: ");
            scanf("%d", &foundIndex);

            if (foundIndex < 0 || foundIndex >= addressBook->contactCount) {
                printf("Invalid index.\n");
                return;
            }

            // Update only the name field
            char newName[50];
            int attempts = 0;
            while (attempts < 3) {
                printf("Enter new Name: ");
                scanf("%49s", newName);

                if (validateName(newName)) {
                    strcpy(addressBook->contacts[foundIndex].name, newName);
                    printf("Name updated successfully!\n");
                    return;   // Exit after successful update
                } else {
                    attempts++;
                }
            }

            printf("Maximum attempts reached. Name not updated.\n");
            return;
        }

        case 2: { // -------- Edit by Phone --------
            printf("Enter Phone to edit: ");
            scanf("%49s", query);

            int matches[50], matchCount = 0;   // Track duplicate matches
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].phone, query) == 0) {
                    matches[matchCount++] = i;
                }
            }

            if (matchCount == 0) {
                printf("No contact found with that Phone.\n");
                return;
            }

            // Show all matches for duplicate phones
            printf("\nContacts with phone '%s':\n", query);
            for (int j = 0; j < matchCount; j++) {
                int idx = matches[j];
                printf("[%d] Name : %s | Phone: %s | Email: %s\n",
                       idx, addressBook->contacts[idx].name,
                       addressBook->contacts[idx].phone,
                       addressBook->contacts[idx].email);
            }

            // Pick index to edit
            printf("Enter index of contact to edit: ");
            scanf("%d", &foundIndex);

            if (foundIndex < 0 || foundIndex >= addressBook->contactCount) {
                printf("Invalid index.\n");
                return;
            }

            // Update only the phone field
            char newPhone[50];
            int attempts = 0;
            while (attempts < 3) {
                printf("Enter new Phone: ");
                scanf("%49s", newPhone);

                if (validatePhone(addressBook, newPhone)) {
                    strcpy(addressBook->contacts[foundIndex].phone, newPhone);
                    printf("Phone updated successfully!\n");
                    return;   // Exit after successful update
                } else {
                    attempts++;
                }
            }

            printf("Maximum attempts reached. Phone not updated.\n");
            return;
        }

        case 3: { // -------- Edit by Email --------
            printf("Enter Email to edit: ");
            scanf("%49s", query);

            int matches[50], matchCount = 0;   // Track duplicate matches
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].email, query) == 0) {
                    matches[matchCount++] = i;
                }
            }

            if (matchCount == 0) {
                printf("No contact found with that Email.\n");
                return;
            }

            // Show all matches for duplicate emails
            printf("\nContacts with email '%s':\n", query);
            for (int j = 0; j < matchCount; j++) {
                int idx = matches[j];
                printf("[%d] Name : %s | Phone: %s | Email: %s\n",
                       idx, addressBook->contacts[idx].name,
                       addressBook->contacts[idx].phone,
                       addressBook->contacts[idx].email);
            }

            // Pick index to edit
            printf("Enter index of contact to edit: ");
            scanf("%d", &foundIndex);

            if (foundIndex < 0 || foundIndex >= addressBook->contactCount) {
                printf("Invalid index.\n");
                return;
            }

            // Update only the email field
            char newEmail[50];
            int attempts = 0;
            while (attempts < 3) {
                printf("Enter new Email: ");
                scanf("%49s", newEmail);

                if (validateEmail(addressBook, newEmail)) {
                    strcpy(addressBook->contacts[foundIndex].email, newEmail);
                    printf("Email updated successfully!\n");
                    return;   // Exit after successful update
                } else {
                    attempts++;
                }
            }

            printf("Maximum attempts reached. Email not updated.\n");
            return;
        }

        case 4: // -------- Exit Option --------
            printf("Exiting edit...\n");
            return;

        default: // -------- Invalid Choice --------
            printf("Invalid choice.\n");
            return;
    }
}





void deleteContact(AddressBook *addressBook) {
    if (addressBook->contactCount == 0) {
        printf("No contacts available to delete.\n");
        return;   // Exit if no contacts exist
    }

    int choice;
    char query[50];
    printf("\nDelete by:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Exit Delete\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    int matches[50], matchCount = 0, foundIndex = -1;   // Track duplicates and selected index

    switch (choice) {
        case 1: // -------- Delete by Name --------
            printf("Enter Name to delete: ");
            scanf("%49s", query);
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].name, query) == 0) {
                    matches[matchCount++] = i;   // Store matching indices
                }
            }
            break;

        case 2: // -------- Delete by Phone --------
            printf("Enter Phone to delete: ");
            scanf("%49s", query);
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].phone, query) == 0) {
                    matches[matchCount++] = i;
                }
            }
            break;

        case 3: // -------- Delete by Email --------
            printf("Enter Email to delete: ");
            scanf("%49s", query);
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].email, query) == 0) {
                    matches[matchCount++] = i;
                }
            }
            break;

        case 4: // -------- Exit Option --------
            printf("Exiting delete...\n");
            return;

        default: // -------- Invalid Choice --------
            printf("Invalid choice.\n");
            return;
    }

    if (matchCount == 0) {
        printf("No contact found with that detail.\n");
        return;   // Exit if no matches found
    }

    // -------- Show Matching Contacts --------
    printf("\nMatching contacts:\n");
    for (int j = 0; j < matchCount; j++) {
        int idx = matches[j];
        printf("[%d] Name: %s | Phone: %s | Email: %s\n",
               idx, addressBook->contacts[idx].name,
               addressBook->contacts[idx].phone,
               addressBook->contacts[idx].email);
    }

    // -------- Pick Index to Delete --------
    printf("Enter index of contact to delete: ");
    scanf("%d", &foundIndex);

    if (foundIndex < 0 || foundIndex >= addressBook->contactCount) {
        printf("Invalid index.\n");
        return;
    }

    // -------- Confirm Deletion --------
    char confirm;
    printf("Are you sure you want to delete this contact? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        // Shift array to remove contact
        for (int i = foundIndex; i < addressBook->contactCount - 1; i++) {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }
        addressBook->contactCount--;   // Reduce count after deletion
        printf("Contact deleted successfully!\n");
    } else {
        printf("Deletion cancelled.\n");
    }
}
