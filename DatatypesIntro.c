#include <stdio.h>
#include <stdlib.h>
#include<math.h>
void print_binary_char(char c) {  //the negative numbers are represented in twos compliment
	int i;
	int A[8]={};
if(c<0)
  { c=128-abs(c);
    A[0]=1;
  }

for(i=7;i>0;i--)
{if(c%2==0)
    {A[i]=0;

    }else{
     A[i]=1;
    }
    c=c/2;
}
for(i=0;i<8;i++)
    printf("%d",A[i]);
}
/*
 *
 */
void question1() {
	printf("printing from -16 to 15 in binary\n");
	char c;
	for(c=-16; c<16; c++) {
		printf("%d\t", c);
		print_binary_char(c);
		printf("\n");
	}
}
/*
 *
 */
void print_binary_float(float f) {  //the computer stored the float in little endian form but it is represented to the user in big endian
	union hexa{
	    float number;
	    unsigned char representation[4];
	}flo;

	flo.number=f;
	int i;
	for(i=3;i>=0;i--)
	{printf("%02X",flo.representation[i]);
	 printf(" ");
	}
}
/*
 *
 */
void question2() {
	float numbers[] = {0.0f, 1.0f, 2.0f, 0.1f};
	int count = sizeof(numbers) / sizeof(numbers[0]);
	int i;

	for(i=0; i<count; i++) {
		printf("%.2f is represented as: ", numbers[i]);
		print_binary_float(numbers[i]);
		printf("\n");
	}
}
/*
 *
 */
float get_smallest_positive_float() {

	union flooo{
	int num;
	float smallest;
	}small;
	small.num=1;
	small.num=small.num<<23;
	return small.smallest;
}
/*
 *
 */
double get_double_epsilon() {
	union doub{
	long long  lnum;
	double rep;}num1,num2,num3;
	num1.rep=1;
	num2.lnum=1;
	num3.lnum=num1.lnum|num2.lnum;

    return num3.rep-num1.rep ;
}
/*
 *
 */
int get_longdouble_exponent_bias() {
	int z= sizeof(long double)/4;
	union longdbias{
	    int value[z];
        long double biased;
	}num;
    int i;
	int count=0;
	num.biased=1.0L;
    for(i=0;i<z;i++){
    int x=num.value[i];
    while(x!=0)
    {
        if(x%2==1)
            count++;
        x=x/2;
    }
	}
	return pow(2,count)-1;

}
/*
 *
 */
void question3() {
	printf("The smallest positive 'float' is: %e\n", get_smallest_positive_float());
	printf("Epsilon for 'double' is: %le\n", get_double_epsilon());
    printf("'long double' has a bias of %d for its exponent\n", get_longdouble_exponent_bias());
}
/*
 *
 */
int get_command() {
	int choice;
	printf("\n\n");
	printf("*********************************************\n");
	printf("* Enter 1 for Signed Integer Representation *\n");
	printf("* Enter 2 for Floating-Point Endianness     *\n");
	printf("* Enter 3 for Floating-Point Representation *\n");
	printf("* Enter anything else to exit               *\n");
	printf("*********************************************\n");
	printf("Your choice: ");
	scanf("%d", &choice);
	fseek(stdin, 0, SEEK_END);
	printf("\n");
	return choice;
}
/*
 *
 */
main() {
	int choice;
	while(1) {
		switch(get_command()) {
			case 1:
				question1();
				break;
			case 2:
				question2();
				break;
			case 3:
				question3();
				break;
			default:
				printf("Invalid Choice. Exiting...\n");
				exit(1);
		}
	}
	return 0;
}
