#include <stdio.h>

int main(){
	//compare signed to unsigned
	int s = -1;
	unsigned int u = 1;
	if(s > u)
		printf("(signed) %d is greater than (unsigned)%u\n",s,u);
	else
		printf("(signed)%d is less than (unsigned)%u\n",s,u);

	//integer promotion
	short a = 10;
	int b = 9;
	if(a > b)
		printf("%d (short) is greater than %d (integer)\n",a,b);
	else
		printf("%d (short) is less than %d (integer)\n",a,b);

	//floats
	float f1 = 0.1,f2 = 0.2;
	if(f1 == 0.1)
		printf("%.10f is equal to 0.1\n",f1);
	else
		printf("%.10f is not equal to 0.1\n",f1);

	//sum of floats
	float sum;
	sum = f1 + f2;
	printf("%0.10f + %0.10f = %0.10f\n",f1,f2,sum);

	return 0;
}
