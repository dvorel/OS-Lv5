#include <stdio.h>
#include <stdlib.h>


int main() {
	int n, i, time, min=0, x, ss = 0;
	int vr=0, temp;
	printf("Unesite broj procesa:\n");
	scanf("%d", &n);

	int done = -1;	//koristim kao boolean
	int* schedule = (int*)calloc(n, sizeof(int));
	int* added = (int*)calloc(n, sizeof(int));

	int* arrival_times = (int*)calloc(n, sizeof(int));
	int* burst_times = (int*)calloc(n, sizeof(int));
	int* waiting = (int*)calloc(n, sizeof(int));
	int* turnaround = (int*)calloc(n, sizeof(int));
	int* completion = (int*)calloc(n, sizeof(int));

	for (i = 0; i < n; i++)
		scanf("%d", &arrival_times[i]);

	for (i = 0; i < n; i++)
		scanf("%d", &burst_times[i]);

	int count = 0; // Broj izvršenih procesa

	//Kopiranje burst_times u novo polje remaining
	int* remaining = (int*)calloc(n, sizeof(int));
	for (i = 0; i < n; i++)
		remaining[i] = burst_times[i];


	for (time = 0; count != n; time++) {
		for (i = 0; i < n; i++) {
			if (remaining[i] != 0 && arrival_times[i] <= time && added[i] != 1) {
				added[i] = 1;	//zapamtim koji su dodani na popis
				schedule[ss] = i;	//dodam na popis
				ss++;
			}
		}		

		min = schedule[0];

		printf("\n%d, %d, %d", schedule[0], schedule[1], schedule[2]);
		remaining[min] = remaining[min] - 1;
		vr++;
		

		// Provjeravamo je li proces izvršen do kraja i povecavamo count
		if (remaining[min] == 0) {
			count++;
			int end = time + 1; // Vrijeme završetka tog procesa
			completion[min] = end;
			waiting[min] = end - arrival_times[min] - burst_times[min];	// Vrijeme čekanja tog procesa
			turnaround[min] = end - arrival_times[min];	 //Vrijeme kada se proces počeo izvršavati
		}

		if (vr > 1 || remaining[min] == 0) {
			vr = 0;

			temp = schedule[0];
			for (x = 0; x < ss-1; x++) {
				schedule[x] = schedule[x + 1];
			}

			if (remaining[min] != 0) {
				schedule[ss-1] = temp;
			}
			else {
				ss--;
			}
		}
	}

	double waiting_time = 0, turnaround_time = 0;

	printf("pid \t burst \t arrival \twaiting \tturnaround \tcompletion");
	for (i = 0; i < n; i++) {
		printf(" \n %d \t   %d \t %d\t\t%d\t\t%d\t\t%d ", i + 1, burst_times[i], arrival_times[i], waiting[i], turnaround[i], completion[i]);

		waiting_time = waiting_time + waiting[i];
		turnaround_time = turnaround_time + turnaround[i];
	}
	printf("\n Total waiting time: %lf\n", waiting_time);
	printf("Total turnaround time: %lf\n", turnaround_time);

	printf("Average waiting time: %lf\n", waiting_time / n);
	printf("Average turnaround time: %lf\n", turnaround_time / n);


	return 0;
}
