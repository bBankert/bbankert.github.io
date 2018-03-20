#include <stdio.h>

char *read_file(char filename[50]);
void write_file(char filename[50],char *string);

int main(){
  //takes in filename of file to be read
  char read[50];
  printf("Enter the name of the file you want to read:");
  scanf("%s",read);
  char *file_text=read_file(read);
  printf("The file contains\n");
  printf("%s",file_text);
  

  //writes file
  char write[50];
  printf("Enter the name of the file you want to write:");
  scanf("%s",write);
  printf("Writing to %s\n",write);
  write_file(write, file_text);  

  return(0);
}

char *read_file(char filename[50]){
 printf("Reading %s\n",filename);

 //open file for reading
 FILE *fp;
 fp = fopen(filename, "r");
 
 //measure length
 int size = 0;
 int i;
 while(i != EOF){
 i = getc(fp);
 size++;
 }
 
 //allocate memory
 char *string=(char*)malloc(size);
 
 //rewind file
 rewind(fp);

 //holds all the strings, because fgets "updates" string every time
  char *text=malloc(size*sizeof(char));
  
 //read file into allocated string
 while(fgets(string, size, fp)){
  strcat(text,string);
 }
  free(string);


 //close file
 fclose(fp);
 return text;
}

void write_file(char filename[50],char *string){
  //initialize file for writing
  FILE *fp;
  fp = fopen(filename, "w");

  //write string to file
  fputs(string, fp);

  //close file
  fclose(fp);

}

