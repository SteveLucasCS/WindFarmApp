//---------------------------------------//
// Name: Steve Lucas                     //
// Class: EGNR265                        //
// Date: Spring 2017                     //
// Project: Project 3                    //
// Purpose: Database Management Tool     //
//  Compiled on: Code::Blocks            //
//---------------------------------------//

#define TERM_PC
#include "wind_support.h"  // defining structure, constants for project 3

// define screen size
#define SCREENX   80
#define SCREENY   30

// define other constants, function prototypes, and libraries here
struct Wfarms * read(char *, struct Wfarms*, struct Wfarms*); //Line 202-reads the file specified by the user
struct Wfarms * CreateNode(char *, int, int, int, char *);   //Line 272-creates a linked list Wfarms node
void DeleteList(struct Wfarms *);       //Line 416-de-allocates memory for nodes and names pointer in nodes
struct Wfarms * AddFarm();              //Line 372-allows user to add or overwrite data on farms
struct Wfarms *GetTail(struct Wfarms *);    //Line 432-find the tail of the linked list for convenience
void DisplayList(struct Wfarms *);    //Line 380-displays table of linked list
void line(int);         //Line 372-just generates a line for the table
int CompString(char *, char *);      //Line 508-checks if a string contains the user input search string
void SearchList(struct Wfarms *);   //Line 449-searches linked list for any matches to search criteria
void PrintNode(struct Wfarms *);    //Line 521-prints a single node from the list
struct Wfarms * SortList(struct Wfarms *);  //Line 578-Sorts linked list in the way requested by the user
void Header();      // Line 653-prints a header for the table
int SaveFile(struct Wfarms *); //Line 672-saves the linked list as a data file to a user specified filename
char * UPPER(char *);       //Line 717-converts a string to uppercase
int CheckList(struct Wfarms *, char *, char *, int, int, int);  //Line 737-checks for repetition

//begin main
int main(int Argc, char **Argv)
{
    /* main program - menu for functions with using database */
    // add variables

    int run = 1, menu = 0, input = -1;   //run is program on or off,
    //menu determines the menu loop being used, input is used for user input within a menu
    char filename[FILENAME_MAX];
    struct Wfarms *head = NULL, *tail = NULL;

    /* begin the main program */
    Set_Screen_Size(SCREENX,SCREENY);  // set console size
    Set_Screen_Title("Go Green! Wind farm database tool");

//Add main code here
    while (run == 1)    //while program is running this menu loop continues
    {
    ////Main menu
        if (menu == 0)   //main menu loop. Displays all options for the user and asks for user input.
        {
            Clear_Screen();
            //prints menu option
            Movetoxy(55,28);
            Set_Color(13);
            printf("Created by Steve Lucas");
            Movetoxy(0,0);
            Set_Color(10);
            printf("\n\t\t\t    Wind Farm Database Tool\n\t\t\t  The Future is Bright Green!");
            Set_Color(15);
            printf("\n\n\t\t1. Load wind farms list from text file\n\t\t");
            printf("2. Add new wind farms list\n\t\t3. Display list in console window\n\t\t");
            printf("4. Sort list\n\t\t5. Search list for any match\n\t\t6. Save list to file\n\t\t7. Exit");
            Set_Color(11);
            printf("\n\n\tSelect an option: ");
            Set_Color(15);

            while ((input < 1) || (input > 7))
            {
                fflush(stdin);
                scanf("%d", &input);
                if ((input<1) || (input>7))
                    printf("\n\n\tError. Input a number corresponding to a listed function above.\n");
                //user input to select menu function.
            }

            //Exit
            if (input == 7)      //exits program after clearing linked list memory
            {
                DeleteList(head);   //frees allocated memory from the structure
                Set_Color(14);
                printf("\n\n\t\tBooyah! It's Summertime!\n\n\t");
                Set_Color(10);
                run = 0;
                return (OK);
            }

            menu = input;   //goes to a new menu
            input = -1;
        }

        //Add farms from file function
        while (menu == 1)
        {
            Clear_Screen();
            Set_Color(11);
            printf("\n\n\tEnter file name to read: ");
            Set_Color(15);
            fflush(stdin);
            gets(filename);
            tail = GetTail(head);
            head = read(filename, head, tail);  //reads file and compiles list
            if (head != NULL)
            {
                Set_Color(10);
                //file read successfully and  stored to linked list
                printf("\n\n\t\tComplete! Data loaded.\n\n\t\t");
                Set_Color(15);
                Wait_For_Enter();
                menu = 0;
                break;
            }
            else
            {
                Set_Color(12);
                //file was opened, but could not read the data. file may be corrupted.
                printf("\n\n\t\t\tError loading data.\n\t\t\t");
                Set_Color(15);
                Wait_For_Enter();
                menu = 0;
                break;
            }
        }

        //Add Farm function
        while (menu == 2)       //this loop allows user to input a new wind farm location's information
        {
            input = -1;
            Clear_Screen();
            Set_Color(15);
            head = AddFarm(head);       //Adds information user put in to the linked list
            Set_Color(10);
            printf("\n\n\t\t\tData stored.\n\t");
            Set_Color(15);
            Wait_For_Enter();
            while (input != 0 && input != 1)     //verify user input
            {
                Set_Color(11);
                printf("\n\n\tWould you like to enter another? (0=No, 1=Yes): "); //Immediately continue if user wants to
                fflush(stdin);
                scanf("%d", &input);
                if (input != 0 && input != 1)
                {
                    printf("\n\tPlease enter 1 for YES or 0 for NO: ");
                    fflush(stdin);
                    scanf("%d", &input);
                }
            }
            Set_Color(15);
            if (input == 1) //if they select 1, loop begins again from the top
                continue;
            else
                menu = 0;       //returns to main menu when user inputs anything but 1 for yes
        }

        //Display List function
        if (menu == 3)       //displays list
        {
            Clear_Screen();
            Set_Color(15);
            DisplayList(head);  //prints entire list to CONSOLE
            Set_Color(15);
            Wait_For_Enter();
            menu = 0;   //returns to main menu
        }

        //Sort List function
        if (menu == 4)
        {
            Clear_Screen();
            if (head == NULL)
            {
                printf("/n/tNo data in list. Please load or sort a list.\n\t");
                Wait_For_Enter();
                menu = 0;   //returns to main menu
                break;
            }
            head = SortList(head);  //sorts the list
            Set_Color(10);
            printf("\n\n\t\tList Sorted!\n\t");
            Set_Color(15);
            Wait_For_Enter();
            menu = 0;   //returns to main menu
        }

        //Search List function
        if (menu == 5)
        {
            Clear_Screen();
            Set_Color(15);
            SearchList(head);   //searches the list based on user input and prints matches
            Set_Color(15);
            Wait_For_Enter();
            menu = 0;   //returns main menu
        }

        //Save to File Function
        if (menu == 6)
        {
            SaveFile(head); //saves entire list to a CSV format file
            menu = 0;   //returns to main menu
        }
    }
  return (OK);
} /* main() */

// Add your functions below

    //reads a CSV file input by the user. If data is within parameters, saves it as a node in linked list.
    //accepts user input filename, head pointer, and tail pointer of Wfarms structure. Returns head ptr
struct Wfarms * read(char *filename, struct Wfarms *head, struct Wfarms *tail)
{
    char name[MAX_STR_LEN], offs[MAX_LOC_LEN], country[MAX_LOC_LEN], str[MAX_STR_LEN];
    //these arrays correspond to strings read in file, NOT the structure data

    int power, turbines, offshore, val=0, replace=0, L=0;
    //correspond to read data, NOT structure data. val is how many strings read by sscanf
    //works as a boolean operator to determine if data should be saved as a node
    //L keeps track of lines read

    FILE *fpin;     //input file pointer
    struct Wfarms *current = NULL;      //initialize pointers to linked list

    fpin = fopen(filename, "r");        //opens file for read only
    if (fpin == NULL)                   //verify that file opened
    {
        Set_Color(12);
        printf("\n\n\t\t\tError. Could not open file.");       //Error opening file reported to user
        return(head);   //aborts this function and returns to main
    }
    else
        printf("\n\n\tFile '%s' opened successfully.", filename);

     //reads input file using gets with a buffer size of MAX_STR_LEN (80) until pointer str == NULL
    while ((fgets(str, 200, fpin)) != NULL) //200 will be safe buffer assuming all values are maximum length
    {

        L++;    //keeps track of what line has been read for error reporting
        val = sscanf(str, "%[^,],%d,%d,%[^,],%[^\n]", name, &power, &turbines, offs, country);

        if (strcmp(offs, "No") == 0)    //converts 'yes' or 'no' to integer type stored in node
            offshore = 0;
        if (strcmp(offs, "Yes") == 0)
            offshore = 1;

        //Check that there are no errors in the input file. If there are, warn user and exit read function
        if (((strcmp(offs, "No") != 0) && (strcmp(offs, "Yes") != 0))
            || (power > MAX_POWER) || (power < 0) || (turbines > MAX_TURBINES) || (val != 5))
            {
                Set_Color(12);
                printf("\n  DATA CORRUPTED. Error in file '%s', line: %d", filename, L);
                fclose(fpin);   //closes input file
                Set_Color(15);
                return(head);   //aborts read function and returns to main
            }
        //Checks that node reads correctly
        if (((strcmp(offs, "No") == 0) || (strcmp(offs, "Yes") == 0))
            && ((power <= MAX_POWER) && (turbines <= MAX_TURBINES)) && (val == 5))  //validates data that has been read
            {
                //checks if the windfarm already exists in the database
                replace = CheckList(head, name, country, offshore, turbines, power);
            }

        if (replace==0) //if windfarm does NOT already exist
        {
            current = CreateNode(name, power, turbines, offshore, country);     //creates node
            if (head == NULL)   //if it is the first node in list, it becomes head ptr
                head = current;
            else
                tail->next_ptr = current;  //else, tail now points to current
            tail = current;     //current becomes new tail
        }
    }
    fclose(fpin);   //close input file
    return (head);    //return head pointer of struct Wfarms
}

//Accepts variables corresponding to data read from input file or user input data. Returns current ptr
struct Wfarms * CreateNode(char *name, int power, int turbines, int offshore, char *country)
{
    struct Wfarms *current = NULL;

    current = (struct Wfarms *)malloc(sizeof(struct Wfarms));       //allocates memory for the node structure
    if (current == NULL)
        exit(GEN_ERROR);  //memory could not be allocated, exits with error

    current->next_ptr = NULL;
    current->name = (char *)malloc(strlen(name)+1);     //allocates memory for the name pointer in the node
    if (current->name == NULL)
        exit(GEN_ERROR);    //exits if memory could not be allocated
    //data accepted by the function is assigned to struct Wfarms variables
    strcpy(current->name, name);
    current->power = power;
    current->turbines = turbines;
    current->offshore = offshore;
    strcpy(current->country, country);

    return (current);   //returns current
}

//User inputs wind farm data into console and it may be added to linked list
struct Wfarms * AddFarm(struct Wfarms *head)
{
    struct Wfarms *current = NULL, *tail = NULL;
    char name[MAX_STR_LEN], country[MAX_LOC_LEN], countryIN[MAX_LOC_LEN], nameIN[MAX_LOC_LEN];   //user input strings of size 80
    int power = -1, turbines = -1, offshore = -1, replace=0;   //user input integers. Replace is a boolean (0 means no errors)
    tail = GetTail(head);   //runs a function to find the tail of the linked list
    printf("\n\n\t\tAdding a New Wind Farm: ");
    printf("\n\n\tEnter name of farm: ");
    fflush(stdin);
    fgets(nameIN, MAX_STR_LEN, stdin);   //gets name until new line is entered
    sscanf(nameIN, "%[^\n]", name);
    printf("\n\tEnter country abbreviation: ");
    fflush(stdin);
    fgets(countryIN, MAX_LOC_LEN, stdin);
    sscanf(countryIN, "%[A-Z,a-z]", country);    //accepts only letters for country  abbreviation
    strcpy(country, UPPER(country));    //country becomes upper case

    //validation loops until valid value is entered.
    while ((power > MAX_POWER) || (power < 0))
    {
        printf("\n\tEnter generation capacity (kW), or 0 for unknown: ");
        fflush(stdin);
        scanf("%d", &power);
        if ((power > MAX_POWER) || (power < 0))
        {
            Set_Color(12);
            printf("\n\tInvalid entry. Try again: ");
            Set_Color(15);
        }
    }

    while ((turbines > MAX_TURBINES) || (turbines < 0))
    {
        printf("\n\tEnter number of turbines on farm: ");
        fflush(stdin);
        scanf("%d", &turbines);
        if ((turbines > MAX_TURBINES) || (turbines < 0))
        {
           Set_Color(12);
        printf("\nInvalid entry. Try again: ");
        Set_Color(15);
        }
    }

    while ((offshore != 1) && (offshore != 0))
    {
        printf("\n\tIs the farm offshore? (0=No, 1=Yes): ");
        fflush(stdin);
        scanf("%d", &offshore);
        if ((offshore != 1) && (offshore != 0))

        {
            Set_Color(12);
            printf("\nError. Invalid value. Enter 0 or 1: ");
            Set_Color(15);
        }
    }

    //checks if there are any nodes already matching the given name and country
    replace = CheckList(head, name, country, offshore, turbines, power);

    if (replace==0) //replace 0 means no matches were found. CheckLIst updated node if replace was 1
    {
        //uses CreateNode function to create a new node
        current = CreateNode(name, power, turbines, offshore, country);
        if (head == NULL)
            head = current;
        else
            tail->next_ptr = current;   //inserts the node at the end of the linked list
        tail = current;

    }
    return (head); //returns head pointer
}

//Creates a line for table
void line(int c)
{
    int i;
    for (i = 0; i < c; i++)
        printf("%c", 196);
    printf("%c", 179);
}

//accepts node head pointer and prints the entire list
void DisplayList(struct Wfarms *head)
{
    struct Wfarms *current = head;
    int a=0, printed=0;
    char input='0';

    Clear_Screen();
    Header();   //prints header for table

    while (current != NULL) //loops until it reaches end of list
    {
        a++;
        printed++;
        PrintNode(current);
        if (a == 20)    //prints 20 lines then goes to a new screen
        {
            Set_Color(11);
            printf("\nPress anything to continue or 1 to return to main menu...\n");
            Set_Color(7);
            input = getch();
            if (input == '1')
            {
                Set_Color(10);
                return;
            }
            Clear_Screen();
            Header();   //prints header again on new screen
            a = 0;
        }
        current = current->next_ptr;    //increments current pointer to next
    }
    printf("\n\nDisplayed %d wind farms.\n", printed);   //displays how many lines were printed
}

//accepts head pointer of linked list and clears all memory
void DeleteList(struct Wfarms *head)
{
    struct Wfarms *current, *temp;
    current = head;
    while (current != NULL)
    {
        temp = current;
        current = current->next_ptr;
        free((void *)temp->name);   //frees memory for name variable of node
        free((void *)temp);         //frees memory for pointer to node

    }

}

//accepts the head of the linked list and returns the tail pointer
struct Wfarms *GetTail(struct Wfarms *head)
{
    struct Wfarms *current = NULL;

    if (head == NULL)   //no nodes in list
        return (NULL);

    current = head; //current set to head pointer
    while (current != NULL)   //
    {
        if (current->next_ptr == NULL)
            return (current);
        current = current->next_ptr;
    }
    return (current);
}

//accepts head pointer. Searches list for user input strings
void SearchList(struct Wfarms *head)
{
    char name[MAX_STR_LEN], country[MAX_LOC_LEN], input = '0';
    int minimum, maximum, a=0, printed=0;
    struct Wfarms *current = NULL;

    printf("\n\tSearch for a wind farm");
    printf("\n\t\tEnter part of name: ");
    fflush(stdin);
    gets(name);
    printf("\n\t\tEnter part of country abbreviation: ");
    fflush(stdin);
    gets(country);
    printf("\n\t\tEnter energy generation capacity <kW> (0 for unspecified)...");
    printf("\n\t\t\tEnter minimum capacity: ");
    while ((minimum < 0) || (minimum > MAX_POWER))
    {
        fflush(stdin);
        scanf("%d",&minimum);
        if ((minimum < 0) || (minimum > MAX_POWER))
        {
            Set_Color(12);
            printf("\n\tInvalid entry. Try again: ");
            Set_Color(15);
        }
    }

    printf("\n\t\t\tEnter maximum capacity: ");
    while ((maximum < 0) || (maximum > MAX_POWER))
    {
        fflush(stdin);
        scanf("%d",&maximum);
        if ((maximum < 0) || (maximum > MAX_POWER))
        {
            Set_Color(12);
            printf("\n\tInvalid entry. Try again: ");
            Set_Color(15);
        }
    }
    printf("\n\tFetching results...\n\t");

    if (maximum==0) //if maximum power is "undecided" it is set to MAX
        maximum = MAX_POWER;
    Set_Color(11);
    Wait_For_Enter();
    Set_Color(7);
    Clear_Screen();
    current = head;
    while (current != NULL)
    {   //checks for matches in list and search string with CompString function
        if ((CompString(name, current->name) == 1) && (CompString(country, current->country) == 1)
            && (current->power >= minimum) && (current->power <= maximum))
        {
            if (a==0)
                Header();
            a++;
            printed++;
            PrintNode(current);
            if (a == 20)    //prints 20 lines then goes to a new screen
            {
                Set_Color(11);
                printf("\nPress anything to continue or 1 to return to main menu...\n");
                Set_Color(7);
                input = getch();
                if (input == '1')
                {
                    Set_Color(10);
                    return;
                }
                Clear_Screen();
                Header();   //prints header again on new screen
                a = 0;
            }
        }
        current = current->next_ptr;
    }
    printf("\n\t%d matches found.\n", printed);   //displays how many lines were printed
}

//accepts a search string and a string from current node. returns 1 if there is a match
int CompString(char *search, char *temp)
{
    int match=0;
    strcpy(temp, UPPER(temp));  //temp is capitalized
    strcpy(search, UPPER(search));  //search is capitalized
    if (strstr(temp, search) != NULL)   //if node strong contains search string, match = 1, it is a match
        match = 1;

    return (match); //returns match. if 1, match, if 0, no match.
}


//accepts a Wfarms pointer and prints the data from that node TO CONSOLE.
void PrintNode(struct Wfarms *current)
{
    char offs[MAX_LOC_LEN]; //string based on offshore boolean

    if (current->offshore == 1)
        strcpy(offs, "Offshore");
    else
        strcpy(offs, "On Land");

    printf(" %-35.35s",current->name);  //prints name, truncated at 35 spaces
    if (strcmp(current->country, "USA") == 0)
    {
        Set_Color(9);
        printf("  U");
        Set_Color(12);
        printf("S");
        Set_Color(15);
        printf("A");
        Set_Color(7);
        //'merica
    }
    else if (strcmp(current->country, "CAN") == 0)
    {
        Set_Color(12);
        printf("  C");
        Set_Color(15);
        printf("A");
        Set_Color(12);
        printf("N");
        Set_Color(7);
        //Oh Canada
    }
    else if (strcmp(current->country, "MEX") == 0)
    {
        Set_Color(2);
        printf("  M");
        Set_Color(15);
        printf("E");
        Set_Color(12);
        printf("X");
        Set_Color(7);
        //Viva Mexico!
    }

    else if ((strcmp(current->country, "CAN") != 0) && (strcmp(current->country, "USA") != 0)
            && (strcmp(current->country, "MEX") != 0))
            printf("%5s", current->country);        //if country is anything else it will print normally

    printf("%12d%6d%8d%10s\n", current->power, current->turbines
        ,(current->power)/(current->turbines), offs);    //prints the remaining values to console


}

//BUBBLE SORT. Accepts head pointer and prompts user to enter field and ascending/descending order.
//Dr. Jone's code used with permission
struct Wfarms * SortList(struct Wfarms *head_ptr)
{
    int out;	// control of outer iteration
    int in; 	// control of inner loop (swap point)
    struct Wfarms **array;   //array of arrays
    struct Wfarms *cur_ptr;
    struct Wfarms *temp_ptr;
    int length = 0, count = 0, dir = 1, field = -1, per = 0, nxt_per = 0;

    while (((field > 5) || (field < 0)) || ((dir != 1) && (dir != -1)))  //prompt for field loop with validation.
    {
        Clear_Screen();
        printf("\n\tSort By:\n\n\t1. Name\n\t2. Location\n\t3. Total Power Capacity\n\t");
        printf("4. Number of Turbines\n\t5. Power per Turbine\n\n\t0. Return to menu\n\n\t\t");
        Set_Color(11);
        printf("Enter Selection: ");
        while ((field > 5) || (field < 0))
        {
            fflush(stdin);
            scanf("%d",&field);
            if ((field > 5) || (field < 0))
                 printf("\n\tInvalid. Enter any integer 0-5: ");
        }
        if (field == 0)
            return (head_ptr);

        printf("\n\tDescending(0) or Ascending(1): ");
        while ((dir!=0) && (dir!=1))
        {
            fflush(stdin);
            scanf("%d",&dir);
            if ((dir!=0) && (dir!=1))
                printf("\n\tInvalid. Enter 1 or 2: ");
        }


        if (dir == 0)   //direction = -1
            dir = DECENDING;
    }

    // find length of linked list
    for (cur_ptr=head_ptr; cur_ptr != NULL; cur_ptr = cur_ptr->next_ptr)
        length++;

    // allocate for an array of pointers of needed size
    array = (struct Wfarms **)malloc(length*sizeof(struct Wfarms *));
    if (array == NULL)
        exit(GEN_ERROR);

    // get pointer array to point to each node in the linked list (in order)
    for (cur_ptr=head_ptr; cur_ptr != NULL; cur_ptr = cur_ptr->next_ptr)
        *(array+count++) = cur_ptr;

    for (out=length-1; out>0; out--)    // for each element
    {
        for (in=0; in<out; in++)         //  look at those lower
        {
            per = (((*(array+in))->power) / ((*(array+in))->turbines));
            nxt_per = (((*(array+in+1))->power) / ((*(array+in+1))->turbines));

            //checks the field requested to sort by and if it is out of order
            if ((((((dir)* ((*(array+in))->power)) - ((dir)*((*(array+in+1))->power))) > 0) && (field==3))
                || (((((dir)* ((*(array+in))->turbines)) - ((dir)*((*(array+in+1))->turbines))) > 0) && (field==4))
                || (((((dir)* (per)) - ((dir)*(nxt_per))) > 0) && (field==5))
                || ((((dir)* (strcmp((UPPER(((*(array+in))->name))), (UPPER(((*(array+in+1))->name)))))) > 0) && (field==1))
                || ((((dir)* (strcmp((UPPER(((*(array+in))->country))),
                    (UPPER(((*(array+in+1))->country))))))  > 0) && (field==2)))

            {
                temp_ptr = *(array+in);
                *(array+in) = *(array+in+1);
                *(array+in+1) = temp_ptr;
            }
         }
    }

    // update the link list pointers based on results of sorted array of pointers
    for (out=0; out<length-1; out++)    // for each element
        (*(array+out))->next_ptr = *(array+out+1);
    (*(array+out))->next_ptr = NULL;
    temp_ptr = *array;

   // deallocate the temporary array of pointers
    free((void *)array);

    return temp_ptr;    //returns the new pointer
}

//prints header for table
void Header()
{
    int i=0;
    Set_Color(15);
    printf(" %-35s%-8s%-10s%-6s%-9s%s\n","Name","Country","Total(kW)","Units","Per(kW)","Location");
    line(35);
    line(7);
    line(9);
    line(5);
    line(7);

    for (i = 0; i < 10; i++)
        printf("%c", 196);
    printf("\n");
    Set_Color(7);
}

//saves data as a CSV format file to user specified file
int SaveFile(struct Wfarms *head)
{
    struct Wfarms *current = NULL;
    FILE *fpout = NULL;
    char location [MAX_LOC_LEN], filename[FILENAME_MAX];

    Clear_Screen();
    Set_Color(15);
    printf("\n\n\n\n\t\tEnter filename: ");    //ask user for the name of a file they would like to open.
    fflush(stdin);
    gets(filename);

    //appends to a file. Creates file if it does not exist already
    fpout = fopen(filename, "a");
    if (fpout == NULL)
    {
        Set_Color(12);
        printf("\n\nError creating file. Try enhancing read/write permissions for this application.\n\t");
        Wait_For_Enter();
        Set_Color(15);
        return (OPEN_WRITE_ERR);
    }
    else
    {
        current = head; //current set to beginning of list
        while (current != NULL) //loops until current reaches end of list
        {
            if (current->offshore == 1) //converts boolean offshore to string type
                strcpy(location, "Yes");
            if (current->offshore == 0)
                strcpy(location, "No");

            //prints the current node to the file
            fprintf(fpout, "%s,%d,%d,%s,%s\n", current->name, current->power, current->turbines, location, current->country);

            current = current->next_ptr;    //increments current to current->next
        }
        Set_Color(10);
        printf("\n\n\t\t\tDone!\n\t\t");
        Set_Color(15);
        Wait_For_Enter();
    }
    return (OK);
}

//accepts a string and converts it to upper case, then returns it as output
char * UPPER(char *input)
{
    char *output;
    int a;

    output = (char *)malloc(strlen(input)+1);
    if (output == NULL)
    {
        Set_Color(12);
        printf("\n\tCould not allocate memory.");
        exit(GEN_ERROR);
    }
    for (a=0; a<strlen(input); a++)
        output[a] = toupper(input[a]);
    //output is freed after it is returned
    return (output);    //returns capitalized string
}


//Checks list for any existing entries matching potential new entry
//accepts variables corresponding to new data from read() or AddFarm()
int CheckList(struct Wfarms *head, char *name, char *country, int offshore, int turbines, int power)
{
    struct Wfarms *current;
    int replace=0;  //boolean. if there is a match, it will become 1
    char *in_country, *in_name, *cur_name, *cur_country;
    current = head;

    //in_ corresponds to data passed to the function. it is used to convert to uppercase temporarily
    in_name = UPPER(name);      //Memory allocated in UPPER() function.
    in_country = UPPER(country);

    while (current != NULL)  //checks all nodes for a name and location matching what the user input
    {
        //cur_ corresponds to data in the current node. it is used to convert to uppercase temporarily
        cur_name = UPPER(current->name);    //
        cur_country = UPPER(current->country);

        if (strcmp(cur_name, in_name) == 0) //name matches
        {
            if (strcmp(cur_country, in_country) == 0)  //country also matches, so replace with new data.
            {
                current->power = power;
                current->turbines = turbines;
                current->offshore = offshore;
                replace = 1;    //replace becomes 1 to indicate that data was replaced
                break;
            }
        }
        current = current->next_ptr;    //current increments to next in list
    }
    //temporary char arrays' memory is freed.
    free(in_name);
    free(in_country);
    free(cur_name);
    free(cur_country);

    return (replace);   //returns int replace as boolean
}
