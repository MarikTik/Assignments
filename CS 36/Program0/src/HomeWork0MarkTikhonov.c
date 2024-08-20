#include <stdio.h>

int main() {
	puts("My name is Mark, I'm in course CS36 #60140.\nThis is my first official course");
	
	float x, y;
	printf("Give me a number : ");
	scanf("%f", &x);
	printf("Give me a second number : ");
	scanf("%f", &y);

	printf("The sum is %.2f\n", x + y);
	printf("The difference is %.2f\n", x - y);
	printf("The product is %.2f\n", x * y);
	printf("The quotient is %.2f\n", x / y);
}
 