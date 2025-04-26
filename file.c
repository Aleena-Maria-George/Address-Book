#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *file = fopen("contacts.csv", "w"); // Open file in write mode
    if (file == NULL)
    {
        printf("Error: Could not open file for saving.\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        // Save each contact as a CSV line
        fprintf(file, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(file); // Close the file
    printf("Contacts saved successfully to file.\n");
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *file = fopen("contacts.csv", "r"); // Open file in read mode
    if (file == NULL)
    {
        printf("No contact file found. Starting with an empty address book.\n");
        return; // If file doesn't exist, return early
    }

    char name[100], phone[20], email[100];
    int count = 0;

    while (fscanf(file, " %99[^,],%19[^,],%99[^\n]",
                  name, phone, email) == 3) // Ensure all 3 fields are read successfully
    {
        if (count < MAX_CONTACTS) // Check array bounds
        {
            strcpy(addressBook->contacts[count].name, name);
            strcpy(addressBook->contacts[count].phone, phone);
            strcpy(addressBook->contacts[count].email, email);
            count++;
        }
        else
        {
            printf("Warning: Maximum contact limit reached. Some contacts were not loaded.\n");
            break;
        }
    }

    addressBook->contactCount = count; // Update contact count
    fclose(file);
    printf("Contacts loaded from file successfully.\n");
}
