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
char *get_flt_exp_str(float n){
 char exp[9];
 char *str = (char*)malloc(8*sizeof(char));
 int x = get_flt_bits_int(n);
 //shift off sign bit
 x <<= 1;
 int i = 0;
 //shift off right
 for(i;i<8;i++){
 //if right most bit 1 add 1 to string
  if(x & INT_MIN){
	exp[i] = '1';
	x<<=1;
  }
  //if right most bit 0 add 0 to string
  else{
	exp[i] = '0';
	x<<=1;
  }	
 }
 exp[8] = '\0';
 strcpy(str,exp);
 return str;
}
int get_flt_exp_val(float n){
 //integer
 char *c = get_flt_exp_str(n);
 int i = 0;
 int sum = 0;
 int len = strlen(c);
 for(i;i<=len;i++){
  if(c[i] == '1'){
   sum+= pow(2,(7-i));
  }
 }
 //take off BIAS
 sum -= BIAS;
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
  int x = get_flt_bits_int(n);
  //shift off sign and exponent
  x <<= 9;
  char man[24];
  char *str = (char*)malloc(23*sizeof(char));
  //special case
  if(n > UINT_MAX){
   int k = 0;
   for(k;k<23;k++){
	 man[k] = '0';
    }
   strcpy(str,man);
   return str;
   }
   //normal and denormal
	int k = 0;
	for(k;k<23;k++){
	 if(x & INT_MIN){
		man[k] = '1';
		x<<=1;
	 }
	 else{
		man[k] = '0';
		x<<=1;
	 }
   }
   man[23] = '\0';
   strcpy(str,man);
   return str;
}

float get_flt_man_val(float n){
 char *c = get_flt_man_str(n); 
 int i = 0;
 float man = 0.0;
 for(i;i<strlen(c);i++){
  if(c[i] == '1'){
   man += 1/(pow(2,i+1));
  }
 }
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
 //aelse if(a.mode == DNORM){
  //original float is mantissa, since there is no shift
 

 
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
 //smallest denormalized number
 float f = (1.4 * pow(10,-45));
 //float f = 0.1875;
 //special
 //float f = INFINITY;
 print_all(f);
 return 0;
}
