#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PROCESSES 100
#define TIME_QUANTUM 4  // for Round Robin

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    bool completed;
} Process;

void inputProcesses(Process processes[], int *n) {
    printf("Enter number of processes: ");
    scanf("%d", n);

    for (int i = 0; i < *n; i++) {
        processes[i].pid = i + 1;
        printf("Process %d Arrival Time: ", processes[i].pid);
        scanf("%d", &processes[i].arrival_time);
        printf("Process %d Burst Time: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].completed = false;
    }
}

void printResults(Process processes[], int n, const char* algo) {
    printf("\n--- %s Scheduling Results ---\n", algo);
    printf("PID\tAT\tBT\tWT\tTAT\n");

    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += processes[i].waiting_time;
        total_tat += processes[i].turnaround_time;
        printf("%d\t%d\t%d\t%d\t%d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].waiting_time,
               processes[i].turnaround_time);
    }

    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

void sjfPreemptive(Process processes[], int n) {
    int completed = 0, current_time = 0, prev = -1;
    printf("\nSJF Execution Order: ");

    while (completed != n) {
        int shortest = -1;
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && 
                processes[i].arrival_time <= current_time && 
                (shortest == -1 || processes[i].remaining_time < processes[shortest].remaining_time)) {
                shortest = i;
            }
        }

        if (shortest != -1) {
            printf("P%d ", processes[shortest].pid);
            processes[shortest].remaining_time--;
            current_time++;

            if (processes[shortest].remaining_time == 0) {
                processes[shortest].completed = true;
                completed++;
                int finish_time = current_time;
                processes[shortest].turnaround_time = finish_time - processes[shortest].arrival_time;
                processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].burst_time;
            }
        } else {
            current_time++;
        }
    }

    printResults(processes, n, "SJF");
}

void roundRobin(Process processes[], int n) {
    int time = 0, completed = 0;
    bool done;
    int queue[MAX_PROCESSES];
    int front = 0, rear = 0;

    printf("\nRound Robin Execution Order: ");
    for (int i = 0; i < n; i++) {
        queue[rear++] = i;  // enqueue all at start (simplified assumption)
    }

    while (completed < n) {
        int i = queue[front];
        front = (front + 1) % MAX_PROCESSES;

        if (processes[i].arrival_time > time || processes[i].completed)
            continue;

        int exec_time = (processes[i].remaining_time < TIME_QUANTUM) ? processes[i].remaining_time : TIME_QUANTUM;

        printf("P%d ", processes[i].pid);
        time += exec_time;
        processes[i].remaining_time -= exec_time;

        if (processes[i].remaining_time == 0) {
            processes[i].completed = true;
            completed++;
            processes[i].turnaround_time = time - processes[i].arrival_time;
            processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        } else {
            queue[rear] = i;
            rear = (rear + 1) % MAX_PROCESSES;
        }
    }

    printResults(processes, n, "Round Robin");
}

int main() {
    Process processes_sjf[MAX_PROCESSES], processes_rr[MAX_PROCESSES];
    int n;

    inputProcesses(processes_sjf, &n);
    memcpy(processes_rr, processes_sjf, sizeof(Process) * n);

    sjfPreemptive(processes_sjf, n);
    roundRobin(processes_rr, n);

    return 0;
}
