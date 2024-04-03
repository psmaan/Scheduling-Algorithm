#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10

// Structure to represent a process
struct Process {
    int id;            // Process ID
    int arrival_time;  // Arrival time of the process
    int burst_time;    // Burst time of the process
    int remaining_time; // Remaining time of the process
};

// Function to find the process with the shortest remaining time
int findShortestJob(struct Process processes[], int n, int current_time) {
    int shortest_job_index = -1;
    int shortest_burst = __INT_MAX__;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && processes[i].remaining_time < shortest_burst && processes[i].remaining_time > 0) {
            shortest_job_index = i;
            shortest_burst = processes[i].remaining_time;
        }
    }

    return shortest_job_index;
}

// Function to simulate the Shortest Remaining Time First (SRTF) scheduling algorithm
void srtf(struct Process processes[], int n) {
    int total_remaining = n;
    int current_time = 0;
    int waiting_time[MAX_PROCESSES] = {0};
    int turnaround_time[MAX_PROCESSES] = {0};
    bool completed[MAX_PROCESSES] = {false};

    while (total_remaining > 0) {
        int shortest_job_index = findShortestJob(processes, n, current_time);

        if (shortest_job_index == -1) {
            current_time++;
            continue;
        }

        // Reduce remaining time of the selected process
        processes[shortest_job_index].remaining_time--;

        // Update current time
        current_time++;

        // If process is completed
        if (processes[shortest_job_index].remaining_time == 0) {
            total_remaining--;

            // Calculate waiting time
            waiting_time[shortest_job_index] = current_time - processes[shortest_job_index].arrival_time - processes[shortest_job_index].burst_time;

            // Calculate turnaround time
            turnaround_time[shortest_job_index] = current_time - processes[shortest_job_index].arrival_time;
            
            // Mark the process as completed
            completed[shortest_job_index] = true;
        }
    }

    // Print processes along with their waiting time and turnaround time
    printf("Process\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", processes[i].id, waiting_time[i], turnaround_time[i]);
    }

    // Calculate and print average waiting time and average turnaround time
    float total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }
    printf("Average waiting time: %.2f\n", total_waiting_time / n);
    printf("Average turnaround time: %.2f\n", total_turnaround_time / n);
}

int main() {
    // Example processes
    struct Process processes[] = { {1, 0, 6, 6},
                                    {2, 1, 8, 8},
                                    {3, 2, 7, 7},
                                    {4, 3, 3, 3} };
    int n = sizeof(processes) / sizeof(processes[0]);

    // Apply SRTF scheduling algorithm
    srtf(processes, n);

    return 0;
}
