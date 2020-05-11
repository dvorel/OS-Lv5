#include <stdio.h>
#include <stdlib.h>


int main() {
	int n, i, time, vr, min=0;
	printf("Unesite broj procesa:\n");
	scanf("%d", &n);

	int done = -1;	//koristim kao boolean
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
			if (remaining[i] != 0 && arrival_times[i] <= time) {
				if (done == -1){
					done = 1;
					vr = burst_times[i];
					min = i;
				}
				else if (vr > burst_times[i]){
					min = i;
					vr = burst_times[i];
					printf("\n%d\t%d\t%d", i, vr, remaining[i]);
				}
			}
		}
		
		remaining[min] = remaining[min] - 1;

		// Provjeravamo je li proces izvršen do kraja i povecavamo count
		if (remaining[min] == 0) {
			count++;
			int end = time + 1; // Vrijeme završetka tog procesa
			completion[min] = end;
			waiting[min] = end - arrival_times[min] - burst_times[min];	// Vrijeme čekanja tog procesa
			turnaround[min] = end - arrival_times[min];	 //Vrijeme kada se proces počeo izvršavati
			done = -1;
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
