#include <iostream>
#include <vector>
#include "process.h"
#include "scheduler.h"

using namespace std;

void getProcessesFromUser(vector<Process>& processes) {
    int num_processes;
    cout << "Enter the number of processes: ";
    cin >> num_processes;

    for (int i = 0; i < num_processes; ++i) {
        int arrival_time, burst_time, priority;
        cout << "Enter Arrival Time, Burst Time, and Priority (for Process " << i + 1 << "): ";
        cin >> arrival_time >> burst_time >> priority;
        processes.push_back(Process(i + 1, arrival_time, burst_time, priority));
    }
}

int main() {
    vector<Process> processes;
    getProcessesFromUser(processes);

    int choice;
    cout << "Choose a Scheduling Algorithm:\n";
    cout << "1. FCFS\n";
    cout << "2. SJF\n";
    cout << "3. Priority Scheduling\n";
    cout << "4. Round Robin\n";
    cout << "Enter your choice (1-4): ";
    cin >> choice;

    Scheduler* scheduler = nullptr;

    switch (choice) {
        case 1:
            scheduler = new FCFS();
            break;
        case 2:
            scheduler = new SJF();
            break;
        case 3:
            scheduler = new PriorityScheduling();
            break;
        case 4:
            int time_quantum;
            cout << "Enter the Time Quantum for Round Robin: ";
            cin >> time_quantum;
            scheduler = new RoundRobin(time_quantum);
            break;
        default:
            cout << "Invalid choice! Exiting...\n";
            return 1;
    }

    // Schedule processes and print metrics
    scheduler->schedule(processes);
    scheduler->printMetrics(processes);

    // Visualize the Gantt chart
    scheduler->visualizeGanttChart(processes, "Gantt Chart");

    delete scheduler;  // Clean up memory
    return 0;
}