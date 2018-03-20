ar to_upper(char s[]){
  int i;
  for(i=0;i<strlen(s);i++){
    s[i] -=32;

  }
 return *s;
}
#include <stdio.h>
#include <string.h>

char to_upper(char s[]);

int main(){
    char s[] = "hello";
    printf("s = %s\n", s);
    to_upper(s);
    printf("s = %s\n", s);
    return 0;
}

char to_upper(char s[]){
  int i;
  for(i=0;i<strlen(s);i++){
    s[i] -=32;
    
  }
 return *s;
}
