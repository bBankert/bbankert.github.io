#include<stdio.h>
#include<ctype.h>

void dec_to_bin(int n);
void dec_to_hex(int n);
void dec_to_oct(int n);
void hex_letters(int n);
int main(){
 //read in for test
 printf("Enter the decimal you want to translate==>");
 int d;
 scanf("%d",&d);
 
 dec_to_bin(d);
 dec_to_hex(d);
 dec_to_oct(d);
 
 return 0;
}
//translate decimal to binary
void dec_to_bin(int n){
 int bin[50];
 int i=0;
 printf("%d in binary is ",n);
 while(n>0){
  bin[i] = n%2;
  n/=2;  
  i+=1;
 }
 //prints binary by reading list backwards
 for(i;i>0;i--)
  printf("%d",bin[i-1]);

 printf("\n");
}
//translate decimal to hex
void dec_to_hex(int n){
 int hex[50];
 int i = 0;
 printf("%d in Hexcidemal is ",n);
 while(n>0){
  hex[i] = n%16;
  n/=16;
  i+=1;
 }
 //reads the list backwards and outputs the correct hex
 printf("0x");
 for(i;i>0;i--){
  if(hex[i-1] > 9){
   hex_letters(hex[i-1]);
  }
  else{
   printf("%d",hex[i-1]);
  }
 }
 printf("\n");
}

//translate decimal to octal
void dec_to_oct(int n){
 int oct[50];
 int i = 0;
 printf("%d in octal is ",n);
 while(n>0){
  oct[i] = n%8;
  n/=8;
  i+=1;
 }
 for(i;i>0;i--)
  printf("%d",oct[i-1]);
printf("\n");
}
//translates decimal numbers to char(hex) equivalent
void hex_letters(int n){
 switch(n){
  case 10:
   printf("A");
   break;
  case 11:
   printf("B");
   break;
  case 12:
   printf("C");
   break;
  case 13:
   printf("D");
   break;
  case 14:
   printf("E");
   break;
  case 15:
   printf("F");
   break;
 }
}
