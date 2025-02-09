#include <iostream>
#include <vector>
#include "process.h"
#include "scheduler.h"

int main() {
    int num_processes;
    std::cout << "Enter the number of processes: ";
    std::cin >> num_processes;

    std::vector<Process> processes;
    for (int i = 0; i < num_processes; ++i) {
        int arrival, burst, prio;
        std::cout << "Process " << i + 1 << ":\n";
        std::cout << "Arrival Time: "; std::cin >> arrival;
        std::cout << "Burst Time: "; std::cin >> burst;
        std::cout << "Priority: "; std::cin >> prio;
        processes.emplace_back(i + 1, arrival, burst, prio);
    }

    std::cout << "Choose algorithm:\n";
    std::cout << "1. FCFS\n2. SJF\n3. Preemptive SJF\n4. Priority\n5. Preemptive Priority\n6. Round Robin\n";
    int choice;
    std::cin >> choice;

    SchedulingAlgorithm* scheduler = nullptr;
    if (choice == 1) {
        scheduler = new FCFS();
    } else if (choice == 2) {
        scheduler = new SJF();
    } else if (choice == 3) {
        scheduler = new PreemptiveSJF();
    } else if (choice == 4) {
        scheduler = new PriorityScheduling();
    } else if (choice == 5) {
        scheduler = new PreemptivePriorityScheduling();
    } else if (choice == 6) {
        int tq;
        std::cout << "Enter time quantum: ";
        std::cin >> tq;
        scheduler = new RoundRobin(tq);
    }

    scheduler->schedule(processes);
    scheduler->printGanttChart();
    scheduler->printMetrics(processes);

    delete scheduler; // Don't forget to delete to avoid memory leaks.
}
