#include<stdio.h>
void print(int n);
int main(){

print(10);

return 0;
}
void print(int n){
FILE *fn;
fn = fopen("test.txt","w");
int i;
for(i=1;i<=n;i++)
fprintf(fn,"%d\n",i);
close(fn);

}
