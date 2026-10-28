
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

// Display all contacts

void listContacts(AddressBook *addressBook)
{
    printf("%-25s %-15s %-35s\n", "NAME", "PHONE", "EMAIL");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-25s %-15s %-35s\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
}


// Initialize the AddressBook
void initialize(AddressBook *addressBook)
{
    // Initially set contact count to zero
    addressBook->contactCount = 0;

    // Add default contacts
    //populateAddressBook(addressBook);

    // Load contacts from file during initialization
    loadContactsFromFile(addressBook);
}

// Save contacts and exit the program
void saveAndExit(AddressBook *addressBook)
{
    // Save all contacts into file
    saveContactsToFile(addressBook);

    // Exit the program successfully
    exit(EXIT_SUCCESS);
}

// Create a new contact
void createContact(AddressBook *addressBook)
{
    char name[50];
    char phone[20];
    char email[50];

    // Read contact name
    printf("Enter name: ");
    scanf(" %[^\n]", name);

    // Read phone number
    printf("Enter phone number: ");
    scanf(" %[^\n]", phone);

    // Read email address
    printf("Enter email: ");
    scanf(" %[^\n]", email);

    // Store name in AddressBook
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);

    // Store phone number in AddressBook
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);

    // Store email in AddressBook
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);

    // Increase contact count
    addressBook->contactCount++;

    // Display success message
    printf("Contact created successfully.\n");
}


// Search for a contact
void searchContact(AddressBook *addressBook)
{
    int choice;
    int found = 0;

    // Display search options
    printf("Search by:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");

    // Read search choice
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Select search method
    switch (choice)
    {
        case 1:
        {
            char name[50];

            // Read name to search
            printf("Enter name to search: ");
            scanf(" %[^\n]", name);

            // Search name in all contacts
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strstr(addressBook->contacts[i].name, name) != NULL)
                {
                    // Display matching contact
                    printf("Contact found at index %d : %s, %s, %s\n",
                           i,
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);

                    // Contact found
                    found = 1;
                }
            }

            break;
        }

        case 2:
        {
            char phone[20];

            // Read phone number to search
            printf("Enter phone number to search: ");
            scanf(" %[^\n]", phone);

            // Search phone number in all contacts
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strstr(addressBook->contacts[i].phone, phone) != NULL)
                {
                    // Display matching contact
                    printf("Contact found at index %d : %s, %s, %s\n",
                           i,
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);

                    // Contact found
                    found = 1;
                }
            }

            break;
        }

        case 3:
        {
            char email[50];

            // Read email to search
            printf("Enter email to search: ");
            scanf(" %[^\n]", email);

            // Search email in all contacts
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strstr(addressBook->contacts[i].email, email) != NULL)
                {
                    // Display matching contact
                    printf("Contact found at index %d : %s, %s, %s\n",
                           i,
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);

                    // Contact found
                    found = 1;
                }
            }

            break;
        }

        default:
            // Invalid search choice
            printf("Invalid choice.\n");
            return;
    }

    // If no contact was found
    if (found == 0)
    {
        printf("Contact not found.\n");
        return;
    }
}


// Edit an existing contact
void editContact(AddressBook *addressBook)
{
    // Search for the contact first
    searchContact(addressBook);

    // Read index of contact to edit
    printf("Enter the index of the contact to edit: ");
    int index;
    scanf("%d", &index);

    // Check whether index is valid
    if (index < 0 || index >= addressBook->contactCount)
    {
        printf("Invalid index.\n");
        return;
    }

    int choice;

    // Display edit options
    printf("\nEdit by:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");

    // Read edit choice
    printf("Enter your choice: ");
    scanf("%d", &choice);

    char str[100];

    // Select field to edit
    switch (choice)
    {
        case 1:
            // Read new name
            printf("Enter new name: ");
            scanf(" %[^\n]", str);

            // Update name
            strcpy(addressBook->contacts[index].name, str);

            // Display updated contact
            printf("Contact successfully updated at index %d : %s, %s, %s\n",
                   index,
                   addressBook->contacts[index].name,
                   addressBook->contacts[index].phone,
                   addressBook->contacts[index].email);

            break;

        case 2:
        {
            int valid = 0;

            // Repeat until valid phone number is entered
            while (valid == 0)
            {
                // Read new phone number
                printf("Enter new phone number: ");
                scanf(" %[^\n]", str);

                // Check phone number length
                if (strlen(str) == 10)
                {
                    valid = 1;

                    // Check every character is a digit
                    for (int i = 0; i < 10; i++)
                    {
                        if (str[i] < '0' || str[i] > '9')
                        {
                            valid = 0;
                            break;
                        }
                    }
                }

                // Display error for invalid phone number
                if (valid == 0)
                {
                    printf("Invalid phone number. Enter 10 digit number.\n");
                }
            }

            // Update phone number
            strcpy(addressBook->contacts[index].phone, str);

            // Display updated contact
            printf("Contact successfully updated at index %d : %s, %s, %s\n",
                   index,
                   addressBook->contacts[index].name,
                   addressBook->contacts[index].phone,
                   addressBook->contacts[index].email);

            break;
        }

        case 3:
        {
            int valid = 0;

            // Repeat until valid email is entered
            while (valid == 0)
            {
                // Read new email
                printf("Enter new email: ");
                scanf(" %[^\n]", str);

                // Check whether email contains @ and .
                if (strchr(str, '@') != NULL &&
                    strchr(str, '.') != NULL)
                {
                    valid = 1;
                }
                else
                {
                    // Display error for invalid email
                    printf("Invalid email. Enter valid email.\n");
                }
            }

            // Update email
            strcpy(addressBook->contacts[index].email, str);

            // Display updated contact
            printf("Contact successfully updated at index %d : %s, %s, %s\n",
                   index,
                   addressBook->contacts[index].name,
                   addressBook->contacts[index].phone,
                   addressBook->contacts[index].email);

            break;
        }

        default:
            // Invalid edit choice
            printf("Invalid choice.\n");
    }
}


// Delete a contact
void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for delete contact */

    // Search for the contact first
    searchContact(addressBook);

    // Read index of contact to delete
    printf("Enter the index of the contact to delete: ");
    int index;
    scanf("%d", &index);

    // Check whether index is valid
    if (index < 0 || index >= addressBook->contactCount)
    {
        printf("Invalid index.\n");
        return;
    }

    // Ask for delete confirmation
    printf("Are you sure you want to delete the contact at index %d : %s, %s, %s? (y/n): ",
           index,
           addressBook->contacts[index].name,
           addressBook->contacts[index].phone,
           addressBook->contacts[index].email);

    char confirm;
    scanf(" %c", &confirm);

    // Check user's confirmation
    if (confirm == 'y' || confirm == 'Y')
    {
        // Shift all contacts after deleted contact one position left
        for (int i = index; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] =
                addressBook->contacts[i + 1];
        }

        // Decrease contact count
        addressBook->contactCount--;

        // Display success message
        printf("Contact at index %d deleted successfully.\n", index);
    }
    else
    {
        // Cancel delete operation
        printf("Delete operation cancelled.\n");
    }
}
