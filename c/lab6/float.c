#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define NORM 0
#define DNORM 1
#define SPEC 2
#define BIAS 127
//note to self when compiling add -lm at end

typedef struct{
int sign;
int exponent;
float mantissa;
int mode;

}flt;


int get_flt_bits_int(float n){
 int x = *(int*)&n;
 return x;
}

char *get_flt_sign_char(float n){
 char sign[2];
 if( n > 0)
  sign[0] = '0';
 else
  sign[0] = '1';
 sign[1] = '\0';
 char *str = (char*)malloc(2*sizeof(char));
 strcpy(str,sign);
 return str;
}

int get_flt_sign_val(float n){
 int x = get_flt_bits_int(n);
 if( n < 0)
  return -1;
 else
  return 1;
}
//created this function to get binary of float whenever needed
char *get_flt_bin(float n){
//make n positive
 char integral[50];
 if(n<0)
   n = n * -1;
 //integer
 int num = (int)n;
 //get binary representation of the integer value
 int i = 0;
 while(num>0){
  if(num%2 == 1)
   integral[i] = '1';
  else
   integral[i] = '0';
  num = num/2;
  i+=1;
 }
 //decimal
 float dec = n - (int)n;
 integral[i] = '.';
 i+=1;
 //get binary representation of decimal
 while(dec!=0){
  float temp = dec * 2;
  if(temp>=1){
   integral[i] = '1';
   dec = temp - 1;
  }
  else{
   integral[i] = '0';
   dec = temp;
  }
  i += 1;
 }
 integral[i] = '\0';
 char *str = (char*)malloc(10*sizeof(char));
 strcpy(str,integral);
 return str;
}
char *get_flt_exp_str(float n){
 char exp[8];
 char *str = (char*)malloc(8*sizeof(char));
 //special
 if(n > UINT_MAX){
   int k = 0;
   for(k;k<8;k++)
    exp[7-k] = '1';
  exp[8] = '\0';
  strcpy(str,exp);
  return str;
  }
 //get binary of float
 char *c = get_flt_bin(n);
 int i;
 int len = strlen(c)-1;
 //find the decimal to move it
 for(i=0;i<len;i++){
  if(c[i] == '.'){
   break;
  }
 }
 //shift amount to change the value
  i -= 1;
 //calculate exponent
 int xp;
 xp = pow(2.0,len)-1;
 //value of the exponent in decimal (shift + amount after decimal)
 xp += i;
 //denormalized
 if(n < 1 && n > -1){
  int k = 0;
  for(k;k<8;k++){
   exp[7-k] = '0';
  }
 exp[8] = '\0';
 }
 //normalized
 else{
 //get binary of exp
  int j = 0;
  while(xp>0){
   if(xp%2 == 1)
    exp[7-j] = '1';
   else
    exp[7-j] = '0';
    xp = xp/2;
    j = j+1;
  }
   exp[j] = '\0';
 }
 //return value
 strcpy(str,exp); 
 return str;
}
int get_flt_exp_val(float n){
 //integer
 char *c = get_flt_exp_str(n);
 int len = strlen(c) - 1;
 int i = 0;
 int sum = 0;
 for(i;i<=len;i++){
  if(c[i] == '1')
   sum+= pow(2,len-i);
 }
 //take off BIAS
 sum -= 127;
 if(n < 1 && n > -1)
  sum = -126;
 return sum;
}

int get_flt_exp_mode(float n){
 int mode = 0;
 char *str = get_flt_exp_str(n);
 //check if exponent has all 1's
 int i;
 //count number of 0's and 1's
 int zero = 0;
 int one = 0;
 for(i=0;i<strlen(str);i++){
  if(str[i] == '0')
	zero++;
  else if(str[i] == '1')
	one++;
 }
 if(one == strlen(str))//all 1's in exp makes special
   mode = 2;
 else if(zero == strlen(str))//all 0's in exp makes denormalized
  mode = 1;
 else // all else normalized
  mode = 0;

 return mode;

}

char *get_flt_man_str(float n){
 //hold chars and return pointer
  char man[23];
  char *str = (char*)malloc(23*sizeof(char));
  //special case
  if(n > UINT_MAX){
   int k = 0;
   for(k;k<23;k++)
	man[k] = '0';
   man[23] = '\0';
   strcpy(str,man);
   return str;
  }

 //normalized and denormalized
 char *c = get_flt_bin(n);
 int len = strlen(c);
 int i; 
 //find the decimal
 for(i=0;i<len;i++){
  if(c[i] == '.')
   break;
 }
 //swap decimal until only one digit is before the decimal
 while(i>1){
  char temp = c[i-1];
  c[i-1] = c[i];
  c[i] = temp;
  i-=1;
 }
 //mantissa
 int j = 0;
 //move iterator past decimal
 i+=1;
 while(i<len){
  man[j] = c[i];
  j+=1;
  i+=1;
 }
 //fill empty mantissa spaces with zeroes
 for(;j<23;j++)
  man[j] = '0';
 man[j] = '\0';

 strcpy(str,man);
 return str;
}

float get_flt_man_val(float n){
 char *c = get_flt_man_str(n); 
 int i = 0;
 float man = 0.0;
 for(i;i<strlen(c);i++){
  //printf("%c\n",c[i]);
  if(c[i] == '1'){
  //printf("|1/(2^%d)= %f|\n",i,(1/(pow(2,i))));
   man += 1/(pow(2,i+1));
  }
 }
 //printf("man: %f\n",man);
 return man;
}


char *get_flt_bits_str(float n){
 //call other functions
 char *sign = get_flt_sign_char(n);
 char *exp = get_flt_exp_str(n);
 char *man = get_flt_man_str(n);
 //return string
 char *str = (char*)malloc(35*sizeof(char));
 //put together
 //sign
 strcpy(str,sign);
 strcat(str," ");
 //exponent
 strcat(str,exp);
 strcat(str," ");
 //mantissa
 strcat(str,man);
 return str; 
}

flt get_flt_val_flt(float n){
 int x = get_flt_sign_val(n);
 int mode = get_flt_exp_mode(n);
 int exp = get_flt_exp_val(n);
 float f = get_flt_man_val(n); 

 flt a;
 a.sign = x;
 a.exponent = exp;
 a.mantissa = f;
 a.mode = mode;
 if(a.mode == DNORM)
	a.exponent = -126;

return a;
}

void print_flt(float n){
 flt a = get_flt_val_flt(n);
 char c[10];
 if(a.mode == 0)
   strcpy(c,"NORM");
 else if(a.mode == 1)
   strcpy(c,"DNORM");
 else
   strcpy(c,"SPECIAL");
 printf("sign: %d\n",a.sign);
 printf("exp: %d\n",a.exponent);
 printf("man: %f\n",a.mantissa);
 printf("mode: %s\n",c);
}

float get_flt_bits_val(float n){
 flt a = get_flt_val_flt(n);
 float org;
 int integral;
 float decimal;
 float temp;
 //normalized
 if(a.mode == NORM){
  printf("man: %f\n",a.mantissa);
  printf("sign: %d\n", a.sign);
  printf("exp: %f\n",a.exponent);
 //add sign bit if negative
  org = pow(2,a.exponent) * a.mantissa * a.sign;
  if(n<0)
   org += -pow(2,a.exponent);
  else
   org += pow(2,a.exponent);
   //printf("%f\n",org);
  }
 else if(a.mode == DNORM){
  //original float is mantissa, since there is no shift
  org = a.mantissa;
 }


 return org;

}

void print_all(float f){
 printf("f = %f\n",f);
 char *c = get_flt_sign_char(f);
 printf("sig = %s\n",c);
 int x = get_flt_sign_val(f);
 printf("s = %d\n",x);
 char *d = get_flt_exp_str(f);
 printf("exp = %s\n",d);
 x = get_flt_exp_val(f);
 printf("e = %d\n",x);
 char *e = get_flt_man_str(f);
 printf("man = %s\n",e);
 float g = get_flt_man_val(f);
 printf("m = %f\n",g);
 char *h = get_flt_bits_str(f);
 printf("bits = %s\n",h);
 flt num = get_flt_val_flt(f);
 print_flt(f);
 float i = get_flt_bits_val(f);
 printf("ff: %f\n",i);
}
int main(){
 //normalized
 //float f = -15.375;
 //denormalized
 //float f = 0.1875;
 //special
 float f = INFINITY;
 print_all(f);
 return 0;
}
