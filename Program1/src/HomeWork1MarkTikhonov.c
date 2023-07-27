#include <stdio.h>
#include <stdlib.h>
 
 
unsigned max_name_size = 10;
unsigned iterations = 5;


const double normal_max_work_hours = 40;
const double overime_rate_coefficient = 1.5;
const double tax_percent = 0.2;

double get_gross_pay(double hours_worked, double rate) {
	double overtime = hours_worked - normal_max_work_hours;

	if (overtime > 0)
		return rate * (normal_max_work_hours + overtime * overime_rate_coefficient);
	return hours_worked * rate;
}

double get_tax(double gross_pay) {
	return gross_pay * tax_percent;
}

void loop(char* name) {
	 
	double hours_worked, rate;
	 

	printf("Enter name: ");
	scanf("%s", name, max_name_size);
	printf("Enter hourly rate: ");
	scanf("%lf", &rate);
	printf("Enter hours worked: ");
	scanf("%lf", &hours_worked);

	double gross_pay = get_gross_pay(hours_worked, rate);
	double tax = get_tax(gross_pay);
	double taxed_pay = gross_pay - tax;

	printf("\nPay to: %s\n", name);
	printf("Hourly rate: %.2lf$\n", rate);
	printf("Hours worked: %.2lf\n", hours_worked);
	printf("Gross paid: %.2lf$\n", gross_pay);
	printf("Taxes paid: %.2lf$\n", tax);
	printf("Take home: %.2lf\n\n", taxed_pay);
}

 
int main(int argc, char* argv[]) {
	 
	if(argc > 1)
		max_name_size = atoi(argv[1]);
	 
	if (argc == 3) 
		iterations = atoi(argv[2]);

	char* name_buffer = (char*)(malloc(++max_name_size)); // ++ for null termination character \0
	 
	for (unsigned i = 0; i < iterations; i++) 
		loop(name_buffer);

	free(name_buffer); 
}

//Notes:

//Left 2 command line arguments for changing the maximum size of the names(first argument)
//and setting the amount of iterations(second argument)

//while the second argument wasn't necessary, the first was required since
//the problem didn't specify it as a constraint, hence I transfer 
//this responsibility to the user.

//if there is a way to get the full line of input in C I would be curious to know about it.