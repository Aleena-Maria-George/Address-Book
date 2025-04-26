#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "contact.h"
#include "file.h"
#include "populate.h"



int validate_name(char *name)
{
    // Check if the name is empty or too long
    if (strlen(name) == 0 || strlen(name) > 20)
        return 0;

    // Validate each character in the name
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ')
            return 0; // Invalid character found
    }
    return 1; // Name is valid
}

int validate_phone(char *phone)
{
    int length = strlen(phone);

    // Check if the phone number length is within the range
    if (length < 10 || length > 15)
        return 0;

    // Validate each character in the phone number
    for (int i = 0; phone[i] != '\0'; i++)
    {
        if (!isdigit(phone[i]))
            return 0; // Invalid character found
    }
    return 1; // Phone number is valid
}



int validate_email(char *email)
{
    int at_position = -1, dot_position = -1;
    int length = strlen(email);

    // Email should not be empty or too long
    if (length == 0 || length > 50)
        return 0;

    // Find positions of '@' and '.' in the email
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
            at_position = i;
        else if (email[i] == '.')
            dot_position = i;
    }

    // Check if '@' comes before '.' and both are in valid positions
    if (at_position == -1 || dot_position == -1 || at_position > dot_position || at_position == 0 || dot_position == length - 1)
        return 0;

    return 1; // Email is valid
}

int search_contact(AddressBook *addressBook, char *key, int option)
{
    int duplicate_array[MAX_CONTACTS];
    int duplicate_count = 0;

    // Search for matching contacts based on the given option
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if ((option == 1 && strcmp(addressBook->contacts[i].name, key) == 0) ||
            (option == 2 && strcmp(addressBook->contacts[i].phone, key) == 0) ||
            (option == 3 && strcmp(addressBook->contacts[i].email, key) == 0))
        {
            duplicate_array[duplicate_count++] = i; // Store the index of matching contact
        }
    }

    // Handle cases with no matches, one match, or duplicates
    if (duplicate_count == 0)
    {
        printf("No matching contact found.\n");
        return -1; // No matches found
    }
    else if (duplicate_count == 1)
    {
        return duplicate_array[0]; // Single match found, return its index
    }
    else
    {
        // Handle duplicate contacts (only for option == 1)
        if (option == 1)
        {
            char phoneNumber[20];
            printf("Multiple contacts found with the name '%s'.\n", key);
            printf("Please enter the phone number to identify the contact: ");
            scanf("%14s",phoneNumber);

            // Search among duplicates for the matching phone number
            for (int j = 0; j < duplicate_count; j++)
            {
                int index = duplicate_array[j];
                if (strcmp(addressBook->contacts[index].phone, phoneNumber) == 0)
                {
                    return index; // Return the correct contact index
                }
            }

            // If no match is found with the provided phone number
            printf("No contact found with the provided phone number.\n");
            return -1;
        }
        else
        {
            printf("Multiple matches found but no additional criteria provided for resolution.\n");
            return -1;
        }
    }
}


void edit_contact(AddressBook *addressBook, char *token, int choice)
{
    int index = search_contact(addressBook, token, choice);
    if (index == -1)
    {
        return;
    }

    char edit_value[50];
    printf("Enter new value: ");
    scanf("%[^\n]", edit_value);
    getchar();

    switch (choice)
    {
    case 1:
        if (validate_name(edit_value))
        {
            strcpy(addressBook->contacts[index].name, edit_value);
            printf("Name updated successfully.\n");
        }
        break;
    case 2:
        if (validate_phone(edit_value))
        {
            strcpy(addressBook->contacts[index].phone, edit_value);
            printf("Phone number updated successfully.\n");
        }
        break;
    case 3:
        if (validate_email(edit_value))
        {
            strcpy(addressBook->contacts[index].email, edit_value);
            printf("Email updated successfully.\n");
        }
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }
}
void deleteContactByIndex(AddressBook *addressBook, int index)
{
    for (int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;
    printf("Contact deleted successfully.\n");
}

void displayContacts(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts to display.\n");
        return;
    }

    printf("\nContacts:\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("Contact %d:\n", i + 1);
        printf("  Name: %s\n", addressBook->contacts[i].name);
        printf("  Phone: %s\n", addressBook->contacts[i].phone);
        printf("  Email: %s\n", addressBook->contacts[i].email);
    }
}
void sortByName(AddressBook *addressBook)
{
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if (strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
}
void sort_by_phone_num(AddressBook *addressBook)
{
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if (strcmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone) > 0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
}

void sort_by_email(AddressBook *addressBook)
{
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if (strcmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email) > 0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
}

void listContacts(AddressBook *addressBook, int sortCriteria)
{
    // Sort contacts based on the chosen criteria

    switch (sortCriteria)
    {
    case 1:
        sortByName(addressBook);
        printf("\nContacts sorted by name:\n");
        break;
    case 2:
        sort_by_phone_num(addressBook);
        printf("\nContacts sorted by phone number:\n");
        break;
    case 3:
        sort_by_email(addressBook);
        printf("\nContacts sorted by email:\n");
        break;
    default:
        printf("Invalid choice! Displaying unsorted contacts.\n");
        break;
    }

    displayContacts(addressBook);
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)
{
    char name[20], phone_num[15], email_id[50];

    // Get and validate name
    do
    {
        printf("Enter name: ");
        scanf(" %[^\n]", name); // Allows spaces in the name

        if (validate_name(name))
        {
            printf("Validated successfully.\n");
            break;
        }
        else
        {
            printf("Invalid input. Please try again.\n");
        }

        
    } while (1);

    // Get and validate phone number
    do
    {
        printf("Enter phone number (10-15 digits): ");
        scanf(" %14s", phone_num);

        if (validate_phone(phone_num))
        {
            printf("Validated successfully.\n");
            break;
        }
        else
        {
            printf("Invalid input. Please try again.\n");
        }

        
    } while (1);

    // Get and validate email ID
    do
    {
        printf("Enter email ID: ");
        scanf(" %49s", email_id);

        if (validate_email(email_id))
        {
            printf("Validated successfully.\n");
            break;
        }
        else
        {
            printf("Invalid input. Please try again.\n");
        }

        
    } while (1);

    // Check if address book is full
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("AddressBook is full! Cannot add more contacts.\n");
        return;
    }

    // Add contact to address book
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone_num);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email_id);

    addressBook->contactCount++; // Increment contact count
    printf("Contact added successfully!\n");
    saveContactsToFile(addressBook);
}


void searchContact(AddressBook *addressBook)
{
    char name_check[20], phone_num_check[20], email_id_check[50];
    int ret1, ret2, ret3;
    int choice;
    printf("Choose the attribute by which you want to search:\n");
    printf("1.By Name\n");
    printf("2.By Phone Number\n");
    printf("3.By Email Id\n");
    printf("4.Exit\n");
    printf("Enter choice:");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
    case 1:
        printf("Enter name:");
        scanf(" %[^\n]", name_check);
        getchar();
        if (validate_name(name_check))
        {
            ret1 = search_contact(addressBook, name_check, choice);
            if (ret1 == -1)
            {
                printf("No contact found with the given details.\n");
                return;
            }

            printf("Contact Found: Name: %s, Phone: %s, Email: %s\n",
                   addressBook->contacts[ret1].name,
                   addressBook->contacts[ret1].phone,
                   addressBook->contacts[ret1].email);
            break;
        }

    case 2:
        printf("Enter phone number:");
        scanf(" %[^\n]", phone_num_check);
        getchar();
        validate_phone(phone_num_check);
        ret2 = search_contact(addressBook, phone_num_check, choice);
        if (ret2 == -1)
        {
            printf("No contact found with the given details.\n");
            return;
        }

        printf("Contact Found: Name: %s, Phone: %s, Email: %s\n",
               addressBook->contacts[ret2].name,
               addressBook->contacts[ret2].phone,
               addressBook->contacts[ret2].email);
        break;

    case 3:
        printf("Enter phone number:");
        scanf(" %[^\n]", email_id_check);
        getchar();
        validate_email(email_id_check);
        ret3 = search_contact(addressBook, email_id_check, choice);
        if (ret3 == -1)
        {
            printf("No contact found with the given details.\n");
            return;
        }

        printf("Contact Found: Name: %s, Phone: %s, Email: %s\n",
               addressBook->contacts[ret3].name,
               addressBook->contacts[ret3].phone,
               addressBook->contacts[ret3].email);
        break;

    case 4:
        printf("Exiting...");
        break;

    default:
        printf("Enter valid choice");
    }
}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
    char name_check[20], phone_num_check[20], email_id_check[50];
    int choice;
    printf("Choose the attribute you want to edit:\n");
    printf("1.By Name\n");
    printf("2.By Phone Number\n");
    printf("3.By Email Id\n");
    printf("4.Exit\n");
    printf("Enter choice:");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
    case 1:
        printf("Enter name:");
        scanf("%[^\n]", name_check);
        getchar();
        validate_name(name_check);
        edit_contact(addressBook, name_check, choice);
        break;

    case 2:
        printf("Enter phone number:");
        scanf("%[^\n]", phone_num_check);
        getchar();
        validate_phone(phone_num_check);
        edit_contact(addressBook, phone_num_check, choice);
        break;

    case 3:
        printf("Enter email id:");
        scanf("%[^\n]", email_id_check);
        getchar();
        validate_email(email_id_check);
        edit_contact(addressBook, email_id_check, choice);
        break;

    case 4:
        printf("Exiting...");
        break;

    default:
        printf("Enter valid choice");
    }
    saveContactsToFile(addressBook);
}

void deleteContact(AddressBook *addressBook)
{
    char name[50];
    do
    {
    
    printf("Enter the contact name to delete: ");
    scanf(" %49[^\n]", name);
    getchar();
    
    validate_name(name);
    } while (!validate_name(name));
    
    //getchar();

    int index = search_contact(addressBook, name, 1);
    if (index != -1)
    {
        deleteContactByIndex(addressBook, index);
    }
    saveContactsToFile(addressBook);
}