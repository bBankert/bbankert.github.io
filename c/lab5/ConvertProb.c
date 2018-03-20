/*

    Number converter

    Menu
    Convert between integer, binary, octal and hexadecimal

    This program should accept numeric values in hexadecimal,
    decimal, octal and binary formats as:

        Hex 0x0 to 0xFFFFFFFF
        Dec 0 to 4294967295
        Oct o0 to o37777777777
        Bin b0 to b11111111111111111111111111111111

    After a value is input the code in main will interpret the
    data types above an process the conversion to an unsigned
    int.  The unsigned int will be used to convert the input to
    strings containing hexadecimal, octal and binary strings.

*/

#include <stdio.h>
#include <string.h>
#include <math.h>


//int input_to_decimal(char *input);
unsigned int bin_to_uint(char *input);
unsigned int oct_to_uint(char *input);
unsigned int hex_to_uint(char *input);
unsigned int dec_to_uint(char *input);
void uint_to_hex(unsigned int n, char *output);
void uint_to_oct(unsigned int n, char *output);
void uint_to_bin(unsigned int n, char *output);


int error = 0;


int main(){

    char input[50];
    unsigned int n = 0;
    char output[50];

    // Write code here to test your functions
    // Uncomment code below when done

    printf("Enter a binary (b#), octal(o#), decimal(#) or hexadecimal number(0x#)\n");
    printf("convert > ");
    gets(input);

    // Detect input data type
    // Hexadecimal
    if(input[0] == '0' && input[1] == 'x'){
        n = hex_to_uint(input);
    }
    // Decimal
    else if(input[0] >= '0' && input[0] <= '9'){
        n = dec_to_uint(input);
    }
    // Octal
    else if(input[0] == 'o'){
        n = oct_to_uint(input);
    }
    // Binary
    else if(input[0] == 'b'){
        n = bin_to_uint(input);
    }
    // Unknown
    else{
        printf("ERROR: Unknown data type: %s\n", input);
    }

    // Print results
    printf("The decimal value of %s is %u\n", input, n);
    uint_to_hex(n, output);
    printf("The hexadecimal value of %s is %s\n", input, output);
    uint_to_oct(n, output);
    printf("The octal value of %s is %s\n", input, output);
    uint_to_bin(n, output);
    printf("The binary value of %s is %s\n", input, output);


    return 0;
}


/*
    This function converts the value part of the hex
    string to an unsigned integer value.  The first
    two chars are 0x, which tells that the string is
    in hex.  Start processing the value at index 2 until
    the null, calculating the int value as you would on
    paper.  Try on paper first.
*/
// Convert a hexadecimal char array to uint
unsigned int hex_to_uint(char *input){
    // Declare result and set to zero
    unsigned int res = 0;
    // Declare and set multiplier to 1
    int mult = strlen(input)-3;
    // Declare iterator
    int i = 2;
    // Loop through value part of input string
        for(i;i<strlen(input);i++){
        // If between 0 and 9 add 0 to 9 to res with multiplier
         if(input[i] >= '0' && input[i] <= '9'){
           res += ((input[i] - '0') * pow(16,mult));
         }
        // If between A and F add 10 to 15 to res with multiplier
	 if(input[i] >= 'A' && input[i] <= 'F'){
           res += ((input[i] - 55) * pow(16,mult));
         }
        
        // Error - exit

        // Advance multiplier to next position value
         mult-=1;
       }
    return res;
}


/*
    Copy hex_to_uint() and modify for decimal input.
*/
// Convert a unsigned integer char array to uint
unsigned int dec_to_uint(char *input){
    // Declare result and set to zero
    unsigned int res = 0;
    int i=0;
    //10 to the power of pos minus 1 so it doesn't multiply again after the end by 10
    int mult = strlen(input)-1;
    for(i;i<strlen(input);i++){
     res += ((input[i] - '0') * pow(10,mult));
     mult -=1;
    }
    return res;
}


/*
    Copy dec_to_uint() and modify for octal input.
*/
// Convert a octal char array to uint
unsigned int oct_to_uint(char *input){
    // Declare result and set to zero
    unsigned int res = 0;
    //ignore o
    int i=1;
    //8 to the power of the length minus the o and one more for true position
    int mult = strlen(input)-2;
    for(i;i<strlen(input);i++){
    res += ((input[i] - '0') * pow(8,mult));
    mult-=1;
    }
    return res;
}


/*
    Copy oct_to_uint() and modify for binary input.
*/
// Convert a binary char array to unsigned int
unsigned int bin_to_uint(char *input){
    // Declare result and set to zero
    unsigned int res = 0;
    //ignore b
    int i=1;
    //ignore b and don't do extra 2 multiplation
    int mult = strlen(input)-2;
    for(i;i<strlen(input);i++){
    res += ((input[i] - '0') * pow(2,mult));
    mult -=1;
    }
    return res;
}


/*
    This function converts from unsigned int to a hex
    char array.  Try this on paper before coding.
*/
// Convert a unsigned integer char array to hexadecimal
void uint_to_hex(unsigned int n, char *output){
    // Declare a uint for remainder
    unsigned int rem = 0;
    // Declare an int for division
    // Declare a char array buffer
    char buf[50];
    // Use a loop to generate a hex string - string will be reverse
    int i = 0;
    while(n > 0){
     rem = n%16;
     if(rem >= 0 && rem <= 9){
      buf[i] = rem + '0';
     }
     else if(rem >= 10 && rem <= 15){
      buf[i] = (rem + 55);
     }
     n/=16;
     i+=1;
    }
    
    // Get last hex char
    // Put null at end of buffer
    
    // Copy 0x to output string
    strcat(output,"0x");
    char temp[50];
    int j=0;
    // Copy chars from buffer in reverse order to output string
    for(i;i>=0;i--){
     temp[j] = buf[i-1];
     j +=1;
    }
    strcat(output,temp);
}


/*
    Copy uint_to_hex() and modify for octal
*/
// Convert a unsigned integer char array to octal
void uint_to_oct(unsigned int n, char *output){
    unsigned int rem = 0;
    char buf[50];
    int i = 0;
    while(n > 0){
     rem = n%8;
     buf[i] = rem + '0';
     n/=8;
     i+=1;
    }
    
     
    char temp[50];
    int j=0;
    
    for(i;i>=0;i--){
     temp[j] = buf[i-1];
     j +=1;
    }
    strcpy(output,temp);    
}


/*
    Copy uint_to_oct() and modify for binary
*/
// Convert a unsigned integer char array to binary
void uint_to_bin(unsigned int n, char *output){
    unsigned int rem = 0;
    char buf[50];
    int i = 0;
    while(n > 0){
     rem = n%2;
     buf[i] = rem + '0';
     n/=2;
     i+=1;
    }
    
     
    char temp[50];
    int j=0;
    
    for(i;i>=0;i--){
     temp[j] = buf[i-1];
     j +=1;
    }
    strcpy(output,temp); 
}

