#include <iostream>
#include <vector>
#include "process.h"
#include "scheduler.h"

int main() {
    std::vector<Process> processes;
    int n, choice, quantum;

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

    // Choose scheduling algorithm
    std::cout << "\nChoose scheduling algorithm:\n";
    std::cout << "1. FCFS\n";
    std::cout << "2. SJF\n";
    std::cout << "3. Round Robin\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    // Run the selected scheduler
    if (choice == 1) {
        FCFS fcfs;
        fcfs.schedule(processes);
        fcfs.printGanttChart();
        fcfs.printMetrics();
    } else if (choice == 2) {
        SJF sjf;
        sjf.schedule(processes);
        sjf.printGanttChart();
        sjf.printMetrics();
    } else if (choice == 3) {
        std::cout << "Enter the time quantum for Round Robin: ";
        std::cin >> quantum;
        RR rr(quantum);
        rr.schedule(processes);
        rr.printGanttChart();
        rr.printMetrics();
    } else {
        std::cout << "Invalid choice!\n";
    }

    return 0;
}
