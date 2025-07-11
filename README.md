# 📱 C Programming Exercise: Advanced Phonebook
## 🎯 Objective
- Create a phonebook application in C that:
- Stores multiple entries using an array of structures
- Each contact contains detailed information
- Ensures no duplicates (based on email or contact number)
- Automatically sorts entries alphabetically by name as they are added
- Validates the email address supplied
- Uses pass-by-reference to modify the data

## 📋 MENU
`[1] Add Entry`

`[2] View Entries`

`[3] Edit Entry (by entry number)`

`[4] Delete Entry` 

`[5] Exit`  

## 🧱 Structure Definition
### 🔢 Set Maximum Limits
Define two constants:

`MAX_CONTACTS = 100` — max number of contacts

`MAX_LENGTH = 100` — max characters per string field

### 📦 Contact Structure
`typedef struct {`

    `char name[MAX_LENGTH];`
    
    `char nickname[MAX_LENGTH];`
    
    `char address[MAX_LENGTH];`
    
    `char phone[MAX_LENGTH];`
    
    `char email[MAX_LENGTH];`
    
`} Contact;`

## 🧠 Functions to Implement 
Declare these function prototypes:

`void addContact(Contact contacts[], int *size);`

`int isUnique(Contact contacts[], int size, char *email, char *phone); // returns 1 if found, 0 otherwise`

`void sortContacts(Contact contacts[], int size);`

`void displayContacts(Contact contacts[], int size);`

`int checkValidity(/* provide necessary parameters */); // returns 1 if valid, 0 otherwise`

## ✅ Contact Information Checking
### 📧 Valid Email Format
Only the following email domains are allowed:

`@gmail.com`

`@yahoo.com`

`@<school>.edu.ph`

`@<org>.org`

Username Rules (local part):

Allowed characters:
- Letters (a–z, A–Z)
- Numbers (0–9)
- Special characters: . (dot), _ (underscore), - (dash)

Rules:
- Cannot start or end with special characters
- Cannot have consecutive special characters

### ✅ Valid Examples:
`john.doe@gmail.com`

`jane_doe23@yahoo.com`

`teacher-001@ust.edu.ph`

### ❌ Invalid Examples:
`admin@mycompany.com → .com not allowed unless Gmail/Yahoo`

`student@gmail.edu.ph → invalid Gmail domain`

`john..doe@yahoo.com → double dot`

`@yahoo.com → missing username`

### ☎ Philippine Phone Number Formats

**Type	     Example	     Format Description**

Mobile     Number	       09171234567	Starts with 09 + 9 digits

Landline   Number	       0212345678	Area code (02 or 049) + 8-digit number
