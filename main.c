#include <stdio.h>
#include "contact.h"

int main() 
{
    int choice;    
    // Create addressbook Structure
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    // Display menu until user selects Exit
    do 
    {
        // Display Address Book menu 
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");

        // Read user's choice
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) 
        {
            // Create a new contact
            case 1:
                createContact(&addressBook);
                break;

            // Search for a contact
            case 2:
                searchContact(&addressBook);
                break;

            // Edit an existing contact
            case 3:
                editContact(&addressBook);
                break;

            // Delete a contact
            case 4:
                deleteContact(&addressBook);
                break;

            // Display all contacts
            case 5:

                // First display all contacts
                listContacts(&addressBook);
                break;

            // Save contacts
            case 6:
                printf("Saving and Exiting...\n");

                // Save contacts to file
                // saveContactsToFile(&addressBook);
                break;

            // Exit the Address Book
            case 7:
                printf("Exiting AddressBook\n");
                return 0;

            // Handle invalid choice
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
    
    return 0;
}
