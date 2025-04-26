#include <stdio.h>
#include "contact.h"

int main()
{
    char choice;
    AddressBook addressBook;
    addressBook.contactCount = 0;
    initialize(&addressBook); // Initialize the address book. We dont need it as of now

    do
    {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf(" %[^\n]", &choice);
        getchar();

        switch (choice)
        {
        case '1':
            createContact(&addressBook);
            break;
        case '2':
            searchContact(&addressBook);
            break;
        case '3':
            editContact(&addressBook);
            break;
        case '4':
            deleteContact(&addressBook);
            break;
        case '5':
            printf("Select sort criteria:\n");
            printf("1. Sort by name\n");
            printf("2. Sort by phone\n");
            printf("3. Sort by email\n");
            printf("Enter your choice: ");
            int sortChoice;
            scanf("%d", &sortChoice);
            listContacts(&addressBook, sortChoice);
            break;
        case '6':
            printf("Saving and Exiting...\n");
            saveContactsToFile(&addressBook);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != '6');

    return 0;
}