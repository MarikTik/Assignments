#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

unsigned max_name_size = 10;
unsigned iterations = 5;


const double normal_max_work_hours = 40;
const double overime_rate_coefficient = 1.5;
const double tax_percent = 0.2;

typedef struct {
	double gross_pay;
	double tax_pay;
	double net_pay;
	double base_pay;
	double overime_pay;
} payment_info;

typedef struct {
	char* name;
	double hours_worked;
	double rate;
	payment_info payment;

} worker_info; 

void set_payment_info(worker_info* worker) {
	payment_info* payment = &worker->payment;
	double overtime = worker->hours_worked - normal_max_work_hours;

	if (overtime > 0) {
		payment->overime_pay = overtime * worker->rate * overime_rate_coefficient;
		payment->base_pay = normal_max_work_hours * worker->rate;
	}
	else {
		payment->overime_pay = 0;
		payment->base_pay = worker->hours_worked * worker->rate;
	}
	payment->gross_pay = payment->base_pay + payment->overime_pay;
	payment->tax_pay = payment->gross_pay * tax_percent;
	payment->net_pay = payment->gross_pay - payment->tax_pay;
}


input_worker_info(worker_info* worker, bool* stop) { // I know it is ugly but I didn't come up with something better
	printf("Enter name: ");
	scanf("%s", worker->name, max_name_size);
	if (!strcmp(worker->name,"-1")) {
		*stop = true;
		free(worker->name);
		return;
	}
	printf("Enter hourly rate: ");
	scanf("%lf", &worker->rate);
	if (worker->rate == -1) {
		*stop = true;
		return;
	}
	printf("Enter hours worked: ");
	scanf("%lf", &worker->hours_worked);
	if (worker->hours_worked == -1)
		*stop = true;
}

void print_worker_info(worker_info* worker) {
	printf("\nPay to:\t%s\n", worker->name);
	printf("Hours worked:\t%.2lf\n", worker->hours_worked);
	printf("Hourly rate:\t%.2lf$\n", worker->rate);

	payment_info* info = &worker->payment;

	printf("Gross pay:\t%.2lf$\n", info->gross_pay);
	printf("Base pay:\t%.2lf$\n", info->base_pay);
	printf("Overtime pay:\t%.2lf$\n", info->overime_pay);
	printf("Tax paid:\t%.2lf$\n", info->tax_pay);
	printf("Net pay:\t%.2lf$\n\n", info->net_pay);
}
 
int main(int argc, char* argv[]) {
	if (argc > 1)
		max_name_size = atoi(argv[1]) + 1; 

	if (argc == 3)
		iterations = atoi(argv[2]);

	worker_info* workers = (worker_info*)calloc(iterations, sizeof(worker_info));
	bool stop = false;

	for (unsigned i = 0; i < iterations; i++) {
		worker_info* worker = &workers[i];
		worker->name = (char*)malloc(max_name_size);
		input_worker_info(worker, &stop);
		if (stop) {
			iterations = i;
			break;
		}
		set_payment_info(worker);
		puts("");
	}
	 
	for (unsigned i = 0; i < iterations; i++) {
		print_worker_info(&workers[i]);
	}

	//cleaning

	for (unsigned i = 0; i < iterations; i++) {
		free(workers[i].name);
	}
	free(workers);
}
  

//Notes:

//Left 2 command line arguments for changing the maximum size of the names(first argument)
//and setting the amount of iterations(second argument)

//while the second argument wasn't necessary, the first was required since
//the problem didn't specify it as a constraint, hence I transfer 
//this responsibility to the user.
