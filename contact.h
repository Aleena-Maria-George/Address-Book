#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
int validate_name(char *name);
int validate_phone(char *phone_num);
int validate_email(char *email_id);
int search_contact(AddressBook *addressBook, char *key, int option);
void edit_contact(AddressBook *addressBook, char *token, int choice);
void deleteContactByIndex(AddressBook *addressBook, int index);
//void delete_contact(AddressBook *addressBook, char *name);
void displayContacts(AddressBook *addressBook);
void sortByName(AddressBook *addressBook);
void sort_by_phone_num(AddressBook *addressBook);
void sort_by_email(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);
void saveContactsToFile(AddressBook *addressBook);




#endif