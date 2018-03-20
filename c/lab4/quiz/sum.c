#include <stdio.h>

int main(){
 int n = 5;
 int sum = sum_even(5);
 printf("The sum of the first %d even integers is %d\n",n,sum);
 return 0;
}

int sum_even(int n){
 int i;
 int sum=0;
 for(i=0;i<=n*2;i++){
  if((i%2) == 0)
    sum += i;
 }
 return sum;
}
