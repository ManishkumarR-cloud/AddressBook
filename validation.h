#ifndef VALIDATION_H
#define VALIDATION_H

#include "contact.h"   // Include AddressBook and Contact structures

// -------- Validation Function Prototypes --------
// Each function checks input validity before storing in AddressBook

int validateName(char name[]);                          // Validate name (first character must be alphabet)
int validatePhone(AddressBook *addressBook, char phone[]); // Validate phone (10 digits, starts with 6–9, unique)
int validateEmail(AddressBook *addressBook, char email[]); // Validate email (format rules + uniqueness)
int isPhoneUnique(AddressBook *addressBook, char phone[]); // Check if phone number is unique
int isEmailUnique(AddressBook *addressBook, char email[]); // Check if email is unique

#endif
