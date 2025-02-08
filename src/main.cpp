#include <iostream>
#include <vector>
#include "process.h"
#include "scheduler.h"

int main() {
    std::vector<Process> processes;
    int n;

    // Get the number of processes from the user
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    // Input details for each process
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
    

    // Run FCFS Scheduling
    FCFS fcfs;
    fcfs.schedule(processes);

    // Display results
    fcfs.printGanttChart();
    fcfs.printMetrics();

    return 0;
}