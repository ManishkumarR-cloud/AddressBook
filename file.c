#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fp = fopen("contact.txt", "w");   // Open file in write mode
    if (fp == NULL) {
        printf("Error: Could not open file for saving.\n");
        return;   // Exit if file cannot be opened
    }

    // Write each contact to file
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fp, "%s %s %s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp);   // Close file after writing
    printf("Contacts saved successfully!\n");
}






void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp = fopen("contact.txt", "r");   // Open file in read mode
    if (fp == NULL) {
        // File may not exist yet, so just return without error
        return;
    }

    addressBook->contactCount = 0;   // Reset count before loading
    // Read contacts line by line until EOF
    while (fscanf(fp, "%49s %49s %49s",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3) {
        addressBook->contactCount++;   // Increment count for each valid contact
    }

    fclose(fp);   // Close file after reading
    printf("Contacts loaded successfully!\n");
}
