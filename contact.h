#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100   // Maximum number of contacts allowed

// -------- Contact Structure --------
// Holds individual contact details: Name, Phone, Email
typedef struct {
    char name[50];    // Contact name
    char phone[20];   // Contact phone number
    char email[50];   // Contact email address
} Contact;

// -------- AddressBook Structure --------
// Holds an array of contacts and the total count
typedef struct {
    Contact contacts[MAX_CONTACTS];   // Array of contacts
    int contactCount;                 // Current number of contacts
} AddressBook;

// -------- Function Prototypes --------
// CRUD operations and utility functions for AddressBook
void createContact(AddressBook *addressBook);      // Add new contact
void searchContact(AddressBook *addressBook);      // Search contact by Name/Phone/Email
void editContact(AddressBook *addressBook);        // Edit existing contact
void deleteContact(AddressBook *addressBook);      // Delete contact
void listContacts(AddressBook *addressBook);       // Display all contacts
void initialize(AddressBook *addressBook);         // Initialize and load contacts from file
void saveContactsToFile(AddressBook *AddressBook); // Save contacts to file

#endif

