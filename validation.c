#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "validation.h"
#include "contact.h"





int validateName(char name[]) 
{
    int len = strlen(name);

    // Rule 1: At least 4 characters
    if (len < 4) 
    {
        printf("Error: Name must contain at least 4 characters\n");
        return 0;
    }

    // Rule 2–4: Only alphabets allowed
    for (int i = 0; i < len; i++) 
    {
        if (!isalpha(name[i])) 
        {
            printf("Error: Name should contain only alphabets (A–Z, a–z)\n");
            return 0;
        }
    }

    return 1; // valid
}







int validatePhone(AddressBook *addressBook, char phone[]) {
    // Length check
    if (strlen(phone) != 10) {
        printf("Error: Phone number must contain exactly 10 digits.\n");
        return 0;
    }

    // Digit-only check
    for (int i = 0; i < 10; i++) {
        if (!isdigit(phone[i])) {
            printf("Error: Phone number must contain only digits. Alphabets or symbols are not allowed.\n");
            return 0;
        }
    }

    // First digit check
    if (phone[0] < '6' || phone[0] > '9') {
        printf("Error: First digit must be between 6 and 9.\n");
        return 0;
    }

    // Uniqueness check
    if (!isPhoneUnique(addressBook, phone)) {
        printf("Error: Phone number must be unique.\n");
        return 0;
    }

    return 1; // valid
}





int validateEmail(AddressBook *addressBook,char *email) {
    int atCount = 0;
    int dotCount = 0;
    int len = strlen(email);

    // Rule 1: must contain exactly one '@'
    for (int i = 0; i < len; i++) {
        if (email[i] == '@') atCount++;
        if (email[i] == '.') dotCount++;
    }
    if (atCount != 1) {
        printf("Invalid Email! Must contain exactly one '@'.\n");
        return 0;
    }
    if (dotCount < 1) {
        printf("Invalid Email! Must contain at least one '.'.\n");
        return 0;
    }

    // Rule 2: '@' must come before '.'
    char *at = strchr(email, '@');
    char *dot = strrchr(email, '.'); // last dot
    if (!at || !dot || at > dot) {
        printf("Invalid Email! '.' must appear after '@'.\n");
        return 0;
    }

    // Rule 3: at least one character between '@' and '.'
    if (dot - at <= 1) {
        printf("Invalid Email! Must have characters between '@' and '.'.\n");
        return 0;
    }

    // Rule 4: after final domain (.com, .net, etc.), no extra characters
    if (strcmp(dot, ".com") != 0) {
        printf("Invalid Email! Must end with '.com'.\n");
        return 0;
    }

    // Rule 5: only '@' and '.' allowed as symbols
    for (int i = 0; i < len; i++) {
        if (!isalnum(email[i]) && email[i] != '@' && email[i] != '.') {
            printf("Invalid Email! Only '@' and '.' allowed as symbols.\n");
            return 0;
        }
    }

    // Rule 6: after '@' and after '.', only alphabets or digits allowed
    for (char *p = at + 1; p < dot; p++) {
        if (!isalnum(*p)) {
            printf("Invalid Email! Domain must contain only alphabets or digits.\n");
            return 0;
        }
    }
    for (char *p = dot + 1; p < email + len; p++) {
        if (!isalpha(*p)) {
            printf("Invalid Email! Extension must contain only alphabets.\n");
            return 0;
        }
    }

    // Rule 7: must be unique
    if (!isEmailUnique(addressBook, email)) {
        printf("Invalid Email! Email already exists.\n");
        return 0;
    }

    return 1; // valid
}






// FOR UNIQUENESS 

int isPhoneUnique(AddressBook *addressBook, char phone[]) 
{
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0) 
        {
            return 0; // duplicate found
        }
    }
    return 1; // unique
}




int isEmailUnique(AddressBook *addressBook,char email[]) 
{
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0) 
        {
            return 0; // duplicate found
        }
    }
    return 1; // unique
}