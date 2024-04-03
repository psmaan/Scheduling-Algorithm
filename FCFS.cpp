#include <iostream>
using namespace std;

struct Process {
    int id;
    int arrivaltime;
    int bursttime;
    int completiontime;
    int waitingtime;
    int turnaroundtime;
};

void customswap(Process& a, Process& b) {
    Process temp = a;
    a = b;
    b = temp;
}

void selectionSort(Process processes[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int minindex = i;
        for (int j = i + 1; j < n; ++j) {
            if (processes[j].arrivaltime < processes[minindex].arrivaltime) {
                minindex = j;
            }
        }
        if (minindex != i)
            customswap(processes[i], processes[minindex]);
    }
}

void calculateTimes(Process processes[], int n) {
    int currenttime = 0;
    int totalwaitingtime = 0;
    int totalturnaroundtime = 0;
    for (int i = 0; i < n; ++i) {
        if (currenttime < processes[i].arrivaltime)
            currenttime = processes[i].arrivaltime;

        processes[i].completiontime = currenttime + processes[i].bursttime;
        processes[i].waitingtime = currenttime - processes[i].arrivaltime;
        processes[i].turnaroundtime = currenttime - processes[i].arrivaltime + processes[i].bursttime;

        currenttime = processes[i].completiontime;
        totalwaitingtime += processes[i].waitingtime;
        totalturnaroundtime += processes[i].turnaroundtime;
    }

    float avgwaitingtime = static_cast<float>(totalwaitingtime) / n;
    float avgturnaroundtime = static_cast<float>(totalturnaroundtime) / n;

    cout << "Avg waiting time: " << avgwaitingtime << endl;
    cout << "Avg turnaround time: " << avgturnaroundtime << endl;
}

void displayProcesses(Process processes[], int n) {
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "P" << processes[i].id << "\t" << processes[i].arrivaltime << "\t\t" << processes[i].bursttime
             << "\t\t" << processes[i].completiontime << "\t\t" << processes[i].waitingtime
             << "\t\t" << processes[i].turnaroundtime << endl;
    }
}

void displayGanttChart(Process processes[], int n) {
    cout << "\nGantt Chart:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "| P" << processes[i].id << " ";
    }
    cout << "|" << endl;
    cout << "0";
    
    for (int i = 0; i < n; ++i) {
        if(processes[i].completiontime<10)
            cout << "    " << processes[i].completiontime;
        else
            cout << "   "<< processes[i].completiontime;
    }
    cout << endl;
}
 
int main() {
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    Process processes[n];
    
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrivaltime;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].bursttime;
    }

    selectionSort(processes, n);
    calculateTimes(processes, n);
    displayProcesses(processes, n);
    displayGanttChart(processes, n);
    return 0;
}
