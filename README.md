# Exercise on Structures in C
Specifications
C Programming Exercise: Advanced Phonebook
Objective:
Create a phonebook application in C that:

Stores multiple entries using an array of structures

Each contact contains detailed information

Ensures no duplicates (based on email or contact number)

Automatically keeps the list sorted alphabetically by name as entries are added

Checks if the email address supplied is valid.
Uses pass-by-reference to modify the data

MENU:

[1] Add Entry

[2] View Entries

[3] Edit Entry (by entry number)

[4] Delete Entry 

[5] Exit

Structure Definition:
Set Maximum Limits:

Define two constant values:

MAX_CONTACTS is set to 100, which represents the maximum number of contacts the phonebook can store.

MAX_LENGTH is also set to 100, which indicates the maximum number of characters allowed for each string field (e.g., name, address, phone number, etc.).

Create a Structure to Represent a Contact:

Define a custom data structure called Contact, which groups related information for each individual in the phonebook. Each Contact entry contains the following fields:

name: A character array (string) to store the person's full name, up to 99 characters plus the null terminator.

nickname: A string to hold an alternative or casual name.

address: A string field to store the full address of the contact.

phone: A string to hold the contact's phone number.

email: A string to hold the contact's email address.

Each field is limited to a maximum of 100 characters (as defined by MAX_LENGTH).

Functions To Implement: (Declare Function Prototypes)
void addContact(Contact contacts[], int *size);
int isUnique(Contact contacts[], int size, char *email, char *phone);
//returns 1 if found, 0 otherwise
void sortContacts(Contact contacts[], int size);
void displayContacts(Contact contacts[], int size);
int checkValidity(<provide the necessary parameters);
//returns 1 if valid, 0 otherwise
Contact Information Checking:
✅ Valid Email Format (Gmail, Yahoo, .edu.ph, and .org only)
Email Format Structure:
1. Username (local part):
Allowed characters:

Letters (a–z, A–Z)

Numbers (0–9)

Periods (.), underscores (_), and dashes (-)

Rules:

Cannot start or end with special characters

Cannot have consecutive special characters

Valid examples:

john.doe

jane_doe23

teacher-001

2. Allowed Domains:
Email Provider / Type	Allowed Domain(s)	Examples
Gmail	@gmail.com	user@gmail.com
Yahoo	@yahoo.com	user@yahoo.com
Educational (PH)	@<school>.edu.ph	student@ust.edu.ph
Organizations	@<org>.org	member@redcross.org
Invalid Examples:
admin@mycompany.com — .com domain not allowed unless it's Gmail or Yahoo

student@gmail.edu.ph — not a valid Gmail domain

john..doe@yahoo.com — double dot not allowed

@yahoo.com — username missing

Philippine Phone Number Formats:
Type	Example	Format Description
Mobile Number	09171234567	Starts with 09 + 9 digits
Landline Number	0212345678	Area code (02 or 049) + 8 digit number
