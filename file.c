
#include <stdio.h>
#include "file.h"

// Save all contacts from AddressBook to contacts.csv file
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp;

    // Open contacts.csv file in write mode
    fp = fopen("contacts.txt", "w");

    // Check if file opened successfully
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    // Loop through all contacts
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        // Write name, phone and email into file
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    // Close the file
    fclose(fp);
}


// Load contacts from contacts.csv file into AddressBook
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.txt", "r");
    char line[150];

    if (fp == NULL)
    {
        printf("Error opening contacts.txt\n");
        return;
    }

    addressBook->contactCount = 0;

    while (addressBook->contactCount < MAX_CONTACTS &&
           fgets(line, sizeof(line), fp) != NULL)
    {
        Contact *c = &addressBook->contacts[addressBook->contactCount];

        if (sscanf(line, "%49[^,],%19[^,],%49[^\n]",
                   c->name, c->phone, c->email) == 3)
        {
            addressBook->contactCount++;
        }
    }

    fclose(fp);
}
