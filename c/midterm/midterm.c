/*
    In main function
    1. Read the contents of the file into a string.
    2. Convert all chars in string to lower case.
    3. Capitalize the first char in the string and
        the first non-space char after every period
        and newline.
    4. Write the processed string to a new file.

    Necessary functions
    1. Function to read a file and return an allocated string
    to main.
    2. Function to convert a string to lower case. (Hint: chars
    between A and Z)
    3. Function to convert the first char in every sentence to
    upper case. (Hint: use an int to keep track of when to
    convert the next lower case to upper case. Once at the
    beginning and after every period and after every newline.)
    4. Function to write the string to file.

    Read the pseudo-code below for more hints.
*/
#include <stdio.h>

// Includes and prototypes
char *read_file(char filename[50]);
void to_lower(char *str);
void to_sent_cap(char *str);
void write(char *str);

// Main function
int main(){
    // Declare string pointer and call read
      char *read;      
    // Print string to screen to test program so far
      char f[50] = "DecIndCaps.txt";
      read = read_file(f);
    // Convert string to all lower case
      to_lower(read);
     
    // Print string to screen to test program so far
     /*Only uncomment if you want to see a wall of text
      printf("%s\n",read);
      printf("-----------------\n");*/
    // Convert string to have a capital letter at
    // the beginning of every sentence.
      to_sent_cap(read);
    // Print string to screen to test program so far
     // printf("%s\n",read); Wall of Text 2
    // Print string to file
      write(read);
      printf("Wrote file\n");

}

// read_file function :Read a string from file
char *read_file(char filename[50]){
    // Declare iterator
    int i=0;
    // Declare length of file int
    int len = 0;
    // Declare input data pointer
    // Open file to read
    FILE *fn = fopen(filename,"r");
    // Check that file is open
    if(fn == NULL){
    printf("%s is not open",filename);
    exit(1);
    }
    // Get length of file
    int temp;
    while(temp != EOF){
     i++;
     temp = getc(fn);
    } 
    // Allocate memory for read string in input string
    char *string = (char*)malloc(i);
    // Check for memory allocation success
    if(string == NULL){
     printf("Malloc error");
     exit(1);
    }
    // Rewind file to beginning
    rewind(fn);
    // Loop to read all bytes from file
    int j = 0;
    while(j<i){
        // Get 1 char at a time
        string[j] = getc(fn);
        j++;
    }
    // Put null at end of input string
    string[i] = '\n'; 
    // Close file
    fclose(fn);
    // Return input to calling function
    return string;
}

// to_lower function: Accepts a string and converts
// all chars between A and Z to lower case
void to_lower(char *str){
    // Declare iterator
    int i = 0;
    // Loop through string
    while(str[i] != EOF){
        // If char is between A and Z
        if(str[i] >= 'A' && str[i] <= 'Z'){
            // Convert to lower case
            str[i] += 32;
        }
        i++;
    }
}

// to_sent_cap function: Accepts a string and converts the first char in
// each sentence to upper case
void to_sent_cap(char *str){
    // Int to keep track of when to convert the next int and set to 1
    int convert = 1;
    // Declare iterator
    int i = 0;
    // Loop through string
    while(str[i] != EOF){
       // If this char is a . or newline set period int to 1
      if(str[i] == '.' || str[i] == '\n'){
         convert = 1;
       }
       // If char is between a and z and last char was a . or newline
         if(str[i] >= 'a' && str[i] <= 'z' && convert == 1){
       // Convert to upper case
           str[i] -=32;
       // Set period/newline int to 0
           convert = 0;
       }
     i++; 
    } 
}

// write_file function: Write a string to file
void write(char *str){
    // Declare iterator
    int i = 0;
    // Declare length and get length of string
    int len = 0;
    while(str[len] != EOF)
      len++;
    // Open file to write
    FILE *fn = fopen("output.txt","w");
    // Check that file is open
    if(fn == NULL)
      printf("Couldn't open file");
    // Loop to write all bytes to file
    while(i<len){
        // Write 1 char at a time
      putc(str[i],fn);
      i++;
    }
    // Close file
      fclose(fn);

}

