#include <stdio.h>
#include <string.h>

#define MAX_CONTACTS 100
#define MAX_LENGTH 100

typedef struct contactTag
{
    char name[MAX_LENGTH];
    char nickname[MAX_LENGTH];
    char address[MAX_LENGTH];
    char phone[MAX_LENGTH];
    char email[MAX_LENGTH];
} Contact;

void addContact(Contact contacts[], int *size);
int isUnique(Contact contacts[], int size, char *email, char *phone); //returns 1 if found, 0 otherwise
void sortContacts(Contact contacts[], int size);
void displayContacts(Contact contacts[], int size);
int checkValidity(char email[], char phone[]); //returns 1 if valid, 0 otherwise
void displayMenu();

int main()
{
    Contact contacts[MAX_CONTACTS];
    int size = 0;
    int choice;

    do
    {
        printf("Advanced Phonebook\n");
        printf("Dev-Gabb-711\n");
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: addContact(contacts, &size); break; // Add Contact
            case 2: displayContacts(contacts, size); break; // View Entries
            case 3: // Edit Entry
                    if (size == 0)
                    {
                        printf("No entries to edit.\n");
                    }
                    else
                    {
                        int entry, field, valid = 0, unique = 1;
                        char newValue[MAX_LENGTH];
                        displayContacts(contacts, size);
                        printf("Enter entry number to edit: ");
                        scanf("%d", &entry);
                        if (entry < 1 || entry > size)
                        {
                            printf("Invalid entry number.\n");
                        }
                        else
                        {
                            printf("Which information to edit?\n");
                            printf("[1] Name\n");
                            printf("[2] Nickname\n");
                            printf("[3] Address\n");
                            printf("[4] Phone\n");
                            printf("[5] Email\n");
                            printf("Enter field number: ");
                            scanf("%d", &field);
                            if (field < 1 || field > 5)
                            {
                                printf("Invalid field number.\n");
                            }
                            else
                            {
                                printf("Enter new value: ");
                                scanf("%s", newValue);
                                if (field == 4 || field == 5) // Phone or Email
                                {
                                    if (field == 4)
                                    {
                                        valid = checkValidity(contacts[entry - 1].email, newValue);
                                        // Check uniqueness for phone
                                        int i;
                                        for (i = 0; i < size; i++)
                                        {
                                            if(i != entry - 1 && strcmp(contacts[i].phone, newValue) == 0)
                                            {
                                                unique = 0;
                                            }
                                        }
                                    }
                                    else if (field == 5)
                                    {
                                        valid = checkValidity(newValue, contacts[entry - 1].phone);
                                        // Check uniqueness for email
                                        int i;
                                        for (i = 0; i < size; i++)
                                        {
                                            if (i != entry - 1 && strcmp(contacts[i].email, newValue) == 0)
                                            {
                                                unique = 0;
                                            }
                                        }   
                                    }

                                    if (!valid)
                                    {
                                        printf("Invalid email or phone format. Please try again.\n");
                                    }
                                    if (!unique && valid)
                                    {
                                        printf("Duplicate email or phone found. Please try again.\n");
                                    }
                                    if(valid && unique)
                                    {
                                        if (field == 4)
                                        {
                                            strcpy(contacts[entry-1].phone, newValue);
                                        }
                                        if (field == 5)
                                        {
                                            strcpy(contacts[entry-1].email, newValue);
                                        }
                                        printf("Contact updated successfully.\n");
                                    }
                                }
                                else // Name, Nickname, Address
                                {
                                    if (field == 1)
                                    {
                                        strcpy(contacts[entry-1].name, newValue);
                                    }
                                    if (field == 2)
                                    {
                                        strcpy(contacts[entry-1].nickname, newValue);
                                    }
                                    if (field == 3)
                                    {
                                        strcpy(contacts[entry-1].address, newValue);
                                    }
                                    printf("Contact updated successfully.\n");
                                }
                                sortContacts(contacts, size);
                            }
                        }
                    }
                    break;
            case 4: // Delete Entry
                    if (size == 0)
                    {
                        printf("No entries to delete.\n");
                    }
                    else
                    {
                        int entry;
                        displayContacts(contacts, size);
                        printf("Enter entry number to delete: ");
                        scanf("%d", &entry);
                        if (entry < 1 || entry > size)
                        {
                            printf("Invalid entry number.\n");
                        }
                        else
                        {
                            int i;
                            for (i = entry - 1; i < size - 1; i++)
                            {
                                contacts[i] = contacts[i + 1];
                            }
                            size--;
                            printf("Contact deleted successfully.\n");
                        }
                    }
                    break;
            case 5: printf("Thank you for using Advanced Phonebook!\n"); break; // Exit
            default: printf("Invalid choice. Please try again.\n");
        }

        printf("\n");
        
    } while(choice != 5);

}

void addContact(Contact contacts[], int *size)
{
    Contact temp;
    int valid = 0;
    int unique = 0;

    printf("Enter name: ");
    scanf("%s", temp.name);
    printf("Enter nickname: ");
    scanf("%s", temp.nickname);
    printf("Enter address: ");
    scanf("%s", temp.address);
    printf("Enter phone: ");
    scanf("%s", temp.phone);
    printf("Enter email: ");
    scanf("%s", temp.email);

    valid = checkValidity(temp.email, temp.phone);
    if (!valid) 
    {
        printf("Invalid email or phone format. Please try again.\n");
    }

    if (valid)
    {
        unique = isUnique(contacts, *size, temp.email, temp.phone);
        if (!unique)
        {
            printf("Email or phone already exists. Please try again.\n");
        }
    }
    if (valid && unique)
    {
        
        int idx = *size;
        strcpy(contacts[idx].name, temp.name);
        strcpy(contacts[idx].nickname, temp.nickname);
        strcpy(contacts[idx].address, temp.address);
        strcpy(contacts[idx].phone, temp.phone);
        strcpy(contacts[idx].email, temp.email);
        (*size)++;
        sortContacts(contacts, *size);
        printf("Contact added successfully.\n");
    }
}

int checkValidity(char email[], char phone[])
{
    int i, atIdx = -1;
    int lenEmail = strlen(email);
    
    // Find '@' in email
    for (i = 0; i < lenEmail; i++)
    {
        if (atIdx == -1 && email[i] == '@')
        {
            atIdx = i;
        }
    }

    if (atIdx <= 0 || atIdx >= lenEmail - 1)
    {
        return 0; // Invalid email format
    }

    // Extract username and domain from email
    char username[MAX_LENGTH], domain[MAX_LENGTH];
    
    int u = 0;
    for (i = 0; i < atIdx; i++)
    {
        username[u] = email[i];
        u++;
    }
    username[u] = '\0';

    int d = 0;
    for (i = atIdx; i < lenEmail; i++)
    {
        domain[d] = email[i];
        d++;
    }
    domain[d] = '\0';

    // Username validation
    if (username[0] == '-' || username[0] == '.' || username[0] == '_')
    {
        return 0; // Invalid start character
    }

    if (username[strlen(username) - 1] == '-' || 
        username[strlen(username) - 1] == '.' || 
        username[strlen(username) - 1] == '_')
    {
        return 0; // Invalid end character
    }

    int lastSpecialFlag = 0;
    for (i = 0; i < strlen(username); i++)
    {
        char ch = username[i];
        int isLetterBool = (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
        int isDigitBool = (ch >= '0' && ch <= '9');
        int isSpecialBool = (ch == '-' || ch == '.' || ch == '_');

        if (!(isLetterBool || isDigitBool || isSpecialBool))
        {
            return 0; // Invalid character in username
        }

        if (isSpecialBool)
        {
            if (lastSpecialFlag == 1)
            {
                return 0; // Two consecutive special characters
            }
            lastSpecialFlag = 1; // Set flag for special character
        }
        else
        {
            lastSpecialFlag = 0; // Reset flag for letter or digit
        }
    }

    // Domain validation
    int isValidDomain = 0;
    int len = strlen(domain);

    if (strcmp(domain, "@gmail.com") == 0 || strcmp(domain, "@yahoo.com") == 0)
    {
        isValidDomain = 1; // Valid domain
    }
    else
    {
        if (len >= 7 && strcmp(domain + len - 7, ".edu.ph") == 0)
        {
            isValidDomain = 1; // Valid .edu.ph domain
        }
        if (len >= 4 && strcmp(domain + len - 4, ".org") == 0)
        {
            isValidDomain = 1; // Valid .org domain
        }
    }

    if (isValidDomain == 0)
    {
        return 0; // Invalid domain
    }

    // Phone validation
    int lenPhone = strlen(phone);
    int isValidPhone = 0;

    // Mobile Numbers: "09" + 9 digits
    if (lenPhone == 11 && phone[0] == '0' && phone[1] == '9')
    {
        int allDigits = 1;
        for (i = 2; i < 11; i++)
        {
            if (phone[i] < '0' || phone[i] > '9')
            {
                allDigits = 0;
            }
        }
        if (allDigits == 1)
        {
            isValidPhone = 1; // Valid mobile number
        }
    }

    // Landline Numbers: "02" + 8 digits
    if (lenPhone == 10 && phone[0] == '0' && phone[1] == '2')
    {
        int allDigits = 1;
        for (i = 2; i < 10; i++)
        {
            if (phone[i] < '0' || phone[i] > '9')
            {
                allDigits = 0;
            }
        }
        if (allDigits == 1)
        {
            isValidPhone = 1; // Valid landline number
        }
    }

    // Landline Numbers: "049" + 8 digits
    if (lenPhone == 11 && phone[0] == '0' && phone[1] == '4' && phone[2] == '9')
    {
        int allDigits = 1;
        for (i = 3; i < 11; i++)
        {
            if (phone[i] < '0' || phone[i] > '9')
            {
                allDigits = 0;
            }
        }
        if (allDigits == 1)
        {
            isValidPhone = 1; // Valid landline number
        }
    }

    if (isValidPhone == 0)
    {
        return 0; // Invalid phone number
    }

    return 1; // Valid email and phone
}

int isUnique(Contact contacts[], int size, char *email, char *phone)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (strcmp(contacts[i].email, email) == 0 || strcmp(contacts[i].phone, phone) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void sortContacts(Contact contacts[], int size)
{
    int i, j;
    for (i = 0; i < size - 1; i++)
    {
        for (j = i + 1; j < size; j++)
        {
            if (strcmp(contacts[i].name, contacts[j].name) > 0)
            {
                Contact temp = contacts[i];
                contacts[i] = contacts[j];
                contacts[j] = temp;
            }
        }
    }
}

void displayContacts(Contact *contacts, int size)
{
    if (size == 0)
    {
        printf("No contacts in phonebook. Add contacts first.\n");
    }
    else
    {
        int i;
        printf("%-5s %-20s %-15s %-20s %-15s %-30s\n", "No. ", "Name", "Nickname", "Address", "Phone", "Email");
        
        for (i = 0; i < size; i++)
        {
            printf("%-5d %-20s %-15s %-20s %-15s %-30s\n", i + 1, contacts[i].name, contacts[i].nickname, contacts[i].address, contacts[i].phone, contacts[i].email);
        }
    }
}

void displayMenu()
{
    printf("\n");
    printf("[1] Add Entry\n");
    printf("[2] View Entries\n");
    printf("[3] Edit Entry (by entry number)\n");
    printf("[4] Delete Entry\n");
    printf("[5] Exit\n");
    printf("\n");
}
