#ifndef FILE_H
#define FILE_H

#include "contact.h"   // Include AddressBook and Contact structures

// -------- Function Prototypes --------
// Handles saving and loading contacts to/from file
void saveContactsToFile(AddressBook *addressBook);   // Save all contacts to "contact.txt"
void loadContactsFromFile(AddressBook *addressBook); // Load contacts from "contact.txt"

#endif
