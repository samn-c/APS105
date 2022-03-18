#include <stdio.h>
#include <stdlib.h>
#include "contactList.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//struct for phone number
typedef struct numberNode {
   char* number;
   struct numberNode *next;
} Number;

//struct for person
typedef struct personNode {
   char* person;
   //includes a pointer to the linked list of phone numbers
   Number *numbers;
   struct personNode *next;
} Person;

//struct to mark the head of the linked list
typedef struct linkedList {
   Person *head;
} LL;

//to create the linked list originally as empty
void initList (LL *list) {
   list->head = NULL;
}

//to create person node
Person *createPerson (char* name, Number *phone) {
   Person *newNode = (Person *)malloc(sizeof(Person));

   //set the name, the head of the linked list of numbers
   newNode -> person = name;
   newNode -> numbers = phone;
   newNode -> next = NULL;
   
   return newNode;
}

//to create phone number node
Number *createNumber (char* phone) {
   Number *newNode = (Number *)malloc(sizeof(Number));

   //set the number
   newNode -> number = phone;
   newNode -> next = NULL;

   return newNode;
}

//to order the list lexicographically using bubble sort
void Alphabetize (LL *list) {
   //boolean to determine if there was any swapping in the loop through the contacts
   bool swap = true;
   //the four contacts required to allow the bubble sort swapping
   Person *previousP, *mainP, *nextP, *nextnextP;
   //string equality, and variable to determine if at head of list
   int equal, j;

   //continue to loop if the contacts have been swapped
   while (swap) {
      //for now, no swapping
      swap = false;
      //no previous node at the start
      previousP = NULL;
      //set the main node to the head
      mainP = list -> head;
      //if head exists, set the next node
      if (mainP != NULL) {
         nextP = mainP -> next;
      }
      //if next node exists, set the next next node
      if (nextP != NULL) {
         nextnextP = nextP -> next;
      }
      //starts at the head
      j = 0;

      //while there is still a next node
      while (nextP != NULL) {
         //determine difference in equality between main and next node
         equal = strcmp(mainP -> person, nextP -> person);
         
         //if next node is alphabetically higher
         if (equal > 0) {
            //if at head, set the head to point to the next node
            if (j == 0) {
               list -> head = nextP;
            }
            //if not at the head, set the previous ndoe to point to the next node
            else {
               previousP -> next = nextP;
            }

            //set the next node to point to the main node
            nextP -> next = mainP;
            //point the main node to the next next node
            mainP -> next = nextnextP;

            //swapping took place
            swap = true;
         }
         
         //shifts the four pointers down one to continue to swap between them
         previousP = mainP;
         mainP = nextP;
         if (mainP != NULL) {
            nextP = mainP -> next;
         }
         if (nextP != NULL) {
         nextnextP = nextP -> next;
         }

         //no longer at the head
         j++;
      }
   }
}

//show all the contacts
void ListAllContacts (LL *List) {   
   //pointer to go through the persons
   Person *tempP = List -> head;

   //while they exist
   while (tempP != NULL) {
      //print the name
      printf("Name: %s\n", tempP -> person);

      //pointer for all their numbers
      Number *tempN = tempP -> numbers;

      //print the phones
      printf("Phone(s):");

      while (tempN != NULL) {
         //print number
         printf(" %s", tempN -> number);
         //go to next number
         tempN = tempN -> next;
      }

      //new line
      printf("\n");
      //go to next person
      tempP = tempP -> next;
   }
}

/*
 * convertInputToDataStructure
 * Takes the information in contactList.h and puts it into a data
 * structure of your choosing, however: 1 mark of the lab will be
 * for using structs with pointers in your solution.
 * You might also want to consider the outputs from the program
 * (see the menu printed in printMenu) since some structures will
 * make this easier than others.
 */
void convertInputToDataStructure (LL *List) {
   //creates an empty list to start with
   initList(List);
   
   //person and numbers pointers
   //temp is to go through each person/contact, listN marks the head of every linked list of phone numbers
   Person *tempP;
   Number *listN, *tempN;

   //length of the entire list
   int length = sizeof(contactList)/sizeof(void *) + 1;

   if (length > 0) {
      //variables to go through indices of the contacts
      int i = 0;
      //j for numbers
      int j = i + 1;
      
      //goes up to the index of the next contact
      for (j; j < length && contactList[j][0] < 'A'; j++){ }

      //stores next contact index
      int next = j;
      //decreases by one to get index of current contact's last number
      j--;
      
      //creates the start of the number linked list
      listN = createNumber(contactList[j]);
      //temporary variable to go through and create the following numbers
      tempN = listN;

      //for the rest of the numbers for this contact
      for (j--; j > i; j--) {
         //link the new phone node
         tempN -> next = createNumber(contactList[j]);
         //go to next phone node
         tempN = tempN -> next;
      }

      //mark the start of the linked list with the first contact and their numbers
      List -> head = createPerson(contactList[i], listN);
      //temporary variable to go through the next contacts
      tempP = List -> head;

      //until the end of the contact list
      for (i = next; i < length; i = next) {
         //next number
         int j = i + 1;
         
         //goes up to the index of the next contact
         for (j; j < length && contactList[j][0] < 'A'; j++) { }

         //next contact index
         next = j;
         //current contact last number index
         j--;

         //head of number linked list
         listN = createNumber(contactList[j]);
         //temporary pointer for the rest of the numbers
         tempN = listN;
         
         //for the rest of the numbers for this contact
         for (j--; j > i; j--) {
            //link the new phone node
            tempN -> next = createNumber(contactList[j]);
            //go to the next phone node
            tempN = tempN -> next;
         }

         //link the new person node
         tempP -> next = createPerson(contactList[i], listN);;
         //go to the next person node
         tempP = tempP -> next;
      }
      
      //alphabetically order the contacts
      Alphabetize(List);
   }
}

/*
 * printMenu - Prints out the user menu
 */
void printMenu() {
   printf("\n\nEnter a command by number\n");
   printf("1. List all contacts in alphabetical order\n");
   printf("2. Print phone(s) for a contact\n");
   printf("3. Find duplicate entries\n");
   printf("4. Delete contact\n");
   printf("5. Exit the program\n");
   printf("Your input: ");
}

//eliminate trailing \n
char* rtrim (char* str)
{
   int i;
   for (i = strlen(str) - 1; i >= 0 && str[i] == '\n'; i--)
      str[i] = '\0';
   return str;
}

//output the contact
void PrintContact (LL *List) {
   //get user input
   printf("Enter name: ");
   char userChoice[100];
   char* s = fgets(userChoice, sizeof(userChoice), stdin);
   
   //remove new line character by placing null terminator
   userChoice[strlen(userChoice) - 1] = '\0';
   
   //person pointer to search for person
   Person *tempP;
   //string equality
   int equal = 1;

   //for every person
   for (tempP = List -> head; tempP != NULL; tempP = tempP -> next) {
      //as long as persons exist
      if (tempP -> person != NULL) {
         //store equality of string
         equal = strcmp(userChoice, tempP -> person);
      }
      //if strings are equal
      if (equal == 0) {
         break;
      }
   }
 
   if (equal == 0) {
      //output contact info of the user
      printf("Name: %s", tempP -> person);
      printf("\nPhone(s):");

      Number *tempN = tempP -> numbers;

      //until there are no numbers
      while (tempN != NULL) {
         //print on same line
         printf(" %s", tempN -> number);
         tempN = tempN -> next;
      }

      printf("\n");
   }
   else {
      printf("Contact not found\n");
   }
}

/*
 * DeleteContact deletes a contact from the list
 * The user must enter the name of the contact to delete
 * 
 */
void DeleteContact (LL *List) {
   //get user input
   printf("Enter name: ");
   char userChoice[100];
   char* s = fgets(userChoice, sizeof(userChoice), stdin);
   //place a null terminator where the new line character is
   userChoice[strlen(userChoice) - 1] = '\0';
   //persons in the list
   Person *tempP, *previousP;
   //string equality 
   int equal = 1;
   //variable for if at the head of the list
   int j = 0;

   //for every person, store the previous person as well
   for(tempP = List -> head; tempP != NULL; previousP = tempP, tempP = tempP -> next, j++) {
      //if the list isnt empty
      if (tempP -> person != NULL) {
         equal = strcmp(userChoice, tempP -> person);
      }
      //if user choice is matching a person, break out
      if (equal == 0) {
         break;
      }
   }
   
   //if any contact was matching input
   if (equal == 0) {
      //if at head, set the head of the list to the next
      if (j == 0) {
         List -> head = List -> head -> next;
      }
      //otherwise just connect the previous node to the one after the deletion node
      else {
         previousP -> next = tempP -> next;
      }
      
      //CLEAR THE DELETED USER
      
      //number clearer
      Number *tempN = tempP -> numbers;
      //while numbers of the contact arent clear
      while (tempN != NULL) {
         //temporary next number pointer
         Number *next = tempN -> next;
         //free memory of number
         free(tempN);
         //go to next number
         tempN = next;
      }

      //free memory of person
      free(tempP);
   }
   else {
      printf("Contact not found\n");
   }
}

/*
 * findDuplicates finds the names of contacts with 
 * a phone number in common
 */
void FindDuplicates (LL *List) {
   //variable to store equality of the strings
   int equal;
   bool dupes = false;

   //each main person
   for (Person *mainP = List -> head; mainP != NULL; mainP = mainP -> next) {
      //each of the main person's numbers
      for (Number *mainN = mainP -> numbers; mainN != NULL; mainN = mainN -> next) {
         //each person to compare to 
         for (Person *compareP = mainP -> next; compareP != NULL; compareP = compareP -> next) {
            equal = 1;

            //each of the comparing person's numbers
            for(Number *compareN = compareP -> numbers; compareN != NULL; compareN = compareN -> next) {
               //compare numbers
               equal = strcmp(mainN -> number, compareN -> number);
               
               //if equal, output that they are (List already alphabetized on creation)
               if (equal == 0) {
                  printf("%s and %s have a phone number in common\n", mainP -> person, compareP -> person);
                  dupes = true;
                  break;
               }
            }

            if (equal == 0) {
               break;
            }
         }
      }
   } 

   if (!dupes) {
      printf("No duplicates found\n");
   }
}

int main() {
   //creates a variable for the linked list
   LL List;
   // first move data from contactList.h to a data structure
   convertInputToDataStructure(&List);

   char notDone = 1;
   while (notDone) {
      printMenu();
      char userChoice[100];
      char* s = fgets(userChoice, sizeof(userChoice), stdin);
      if (!s)
      {
         printf("Wrong input\n");
         continue;
      }
      s = rtrim(s); /* eliminate trailing \n */
      //printf("selection = %s\n", s);
      int userSelection = atoi(s);

      switch (userSelection) {
         case 1: ListAllContacts(&List); break;
         case 2: PrintContact(&List); break;
         case 3: FindDuplicates(&List); break;
         case 4: DeleteContact(&List); break;
         case 5: notDone = 0; break;
         default: printf("Bad command...\n"); break;
         }
     
   }
   
   //CODE TO FREE UP DYNAMIC MEMORY
   
   //Pointer to go through the linked list
   LL *clear = &List;
   
   //person clearer variable
   Person *clearerP = clear -> head;

   //until the end of the person list
   while (clearerP != NULL) {
      //number clearer variable
      Number *clearerN = clearerP -> numbers;

      //until the end of the number list
      while (clearerN != NULL) {
         //temporary next number pointer
         Number *nextN = clearerN -> next;
         //free current number memory
         free(clearerN);
         //set the clearer to the next number
         clearerN = nextN;
      }

      //temporary next person pointer
      Person *nextP = clearerP -> next;
      //free current person memory
      free(clearerP);
      //set the clearer to the next number
      clearerP = nextP;
   } 

   return 0;
}
