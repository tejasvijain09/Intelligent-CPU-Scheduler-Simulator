#include <iostream>
#include <vector>
#include "process.h"

// Function to input process details
void inputProcesses(std::vector<Process>& processes, int n) {
    for (int i = 0; i < n; i++) {
        int at, bt, prio;
        std::cout << "\nEnter details for process " << i + 1 << ":\n";
        std::cout << "Arrival Time: ";
        std::cin >> at;
        std::cout << "Burst Time: ";
        std::cin >> bt;
        std::cout << "Priority: ";
        std::cin >> prio;

        // Create a Process object and add it to the vector
        processes.emplace_back(i + 1, at, bt, prio);
    }
}

// Function to display process details
void displayProcesses(const std::vector<Process>& processes) {
    std::cout << "\nEntered Processes:\n";
    for (const auto& p : processes) {
        std::cout << "P" << p.id << " (AT: " << p.arrival_time << ", BT: " << p.burst_time << ", Priority: " << p.priority << ")\n";
    }
}

// FCFS Scheduling function
void fcfsScheduler(const std::vector<Process>& processes) {
    int n = processes.size();
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Variables to track the end time of the last process
    int current_time = 0;

    std::cout << "\nGantt Chart (FCFS):\n";
    for (int i = 0; i < n; i++) {
        // Calculate waiting time
        int waiting_time = current_time - processes[i].arrival_time;
        total_waiting_time += waiting_time;

        // Calculate turnaround time
        int turnaround_time = waiting_time + processes[i].burst_time;
        total_turnaround_time += turnaround_time;

        // Print Gantt chart details
        std::cout << "P" << processes[i].id << " [" << current_time << " - " << current_time + processes[i].burst_time << "] ";

        // Update the current time
        current_time += processes[i].burst_time;
    }
    std::cout << "\n";

    // Display performance metrics
    std::cout << "\nAverage Waiting Time: " << (float)total_waiting_time / n << std::endl;
    std::cout << "Average Turnaround Time: " << (float)total_turnaround_time / n << std::endl;
}

int main() {
    std::vector<Process> processes;
    int n;

    // Get the number of processes from the user
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    // Input process details
    inputProcesses(processes, n);

    // Display the entered processes
    displayProcesses(processes);

    // Call FCFS Scheduler to run and display results
    fcfsScheduler(processes);

    return 0;
}
