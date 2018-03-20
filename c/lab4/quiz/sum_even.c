#include <stdio.h>

int sum_even(int array[],int length);
int main(){
   int array[] = {12, 3, 51, 4, 8, 1}; // Array
    int length = 6; // Length of array
    int sum = sum_even(array, length);
    printf("The sum of the even ints in array are %d\n", sum);
    return 0;
}

int sum_even(int array[], int length){
  int i=0;
  int sum=0;
  for(i = 0;i< length;i++){
     if(array[i]%2 == 0){
      sum+=array[i];
    }
 }
  return sum;
 }
