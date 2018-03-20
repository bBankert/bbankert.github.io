#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *read_file(int *length, char filename[50]);
void write_file(int length, char filename[50],char *string);
void make_rand_key(int length, char *key);
void encrypt(char clear[50],char random[50],char cipher[50]);
void decrypt(char random[50],char cipher[50],char message[50]);


int main(){
 //take in choice
 int choice;
 while(choice != 3){
  printf("Do you want to:\n");
  printf("Encrypt a file:\t1\n");
  printf("Decrypt a file:\t2\n");
  printf("Exit:\t\t3\n");
  printf("Please enter your choice's corresponding number=>");
  scanf("%d",&choice);
  char fin[50];
  switch(choice){
   //encrypt
   case 1:
    printf("Enter the message file: ");
    scanf("%s",fin);
    encrypt(fin,"random","cipher");
    break;
   //decrypt 
   case 2:
    decrypt("random","cipher","message");
    break;
   }
  
 }
 return(0);
}

char *read_file(int *length,char filename[50]){
 printf("Reading %s\n",filename);

 //open file for reading
 FILE *fp;
 fp = fopen(filename, "r");
 int size = 0;
 if(*length == 0){
  //measure length
  int i=0;
  while(i != EOF){
   i = getc(fp);
   size++;
  }
 }
 //allocate memory
 char *string=(char*)malloc(size);

 //rewind file
 rewind(fp);

 //holds all the strings, because fgets "updates" string every time
  char *text=malloc(size*sizeof(char));

 //read file into allocated string
 if(*length != 0){
  fgets(string, size, fp);
  strcat(text,string);
 }
 else{
  while(fgets(string, size, fp)){
   strcat(text,string);
  }
 }
 *length = size;
 //close file
 fclose(fp);
 
 return text;
}

void write_file(int length, char filename[50],char *string){
  //initialize file for writing
  FILE *fp;
  fp = fopen(filename, "w");

  //write string to file
  //if the length is 0, write to first endline
  int i =0;
  if(length == 0){
   while(string[i] != '\0'){
    putc(string[i], fp);
   }
  }
  //if length isn't 0, write characters until reach length
  else{
   for(i=0;i<length;i++){
    putc(string[i], fp);
   }
  }

  //close file
  fclose(fp);

}

//changes characters to random characters
void make_rand_key(int length, char *key){
  //seed random
  char r_key[length];
  srand(time(NULL));
  int i;
  for(i=0;i<length;i++){
   //change character to character from 0-255 in ascii table
   if(key[i] == EOF)
    r_key[i] = (char)(i-1);
   else if(key[i] == 0)
    r_key[i] = (char)(1);
   else
    r_key[i] = (char)(rand()%(255 - 0 + 1) + 0);
  }
  write_file(length,"random",r_key);
}

void encrypt(char clear[50],char random[50], char cipher[50]){
  int len=0;
  
  //read in original text
  char *text = read_file(&len,clear);

  //generate random key
  make_rand_key(len,text);
  len = 0;
  char *key = read_file(&len, random);
  //store random key for xor
  //reset  length so reads in entire file
  int i = 0;
  char xor[len];
  for(i=0;i<len;i++){
    
    xor[i] = (text[i]) ^ (key[i]);
  }
  write_file(len,cipher,xor);

}
void decrypt(char random[50],char cipher[50],char message[50]){
 int len = 0;
 //read random_key file
 char *key = read_file(&len, random);
 
 //read cipher file
 FILE *fp;
 int i;
 char c_text[len];
 int l;
 fp = fopen(cipher, "r");
 for(i=0;i<len;i++){
  l = fgetc(fp);
  c_text[i] = l;
 }
 
 char xor[len];
 for(i=0;i<len;i++)
  xor[i] = key[i] ^ c_text[i];

 write_file(len,message,xor);
 printf("The message you encrypted was: %s\n",xor);
}
