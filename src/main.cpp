#include <iostream>
#include <vector>
#include <memory>
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

    std::cout << "Choose scheduling algorithm:\n";
    std::cout << "1. FCFS\n2. SJF\n3. Preemptive SJF\n4. Priority Scheduling\n5. Preemptive Priority Scheduling\n6. Round Robin\n";
    
    int choice;
    std::cin >> choice;

    std::unique_ptr<SchedulingAlgorithm> scheduler;

    switch (choice) {
        case 1: scheduler = std::make_unique<FCFS>(); break;
        case 2: scheduler = std::make_unique<SJF>(); break;
        case 3: scheduler = std::make_unique<PreemptiveSJF>(); break;
        case 4: scheduler = std::make_unique<PriorityScheduling>(); break;
        case 5: scheduler = std::make_unique<PreemptivePriorityScheduling>(); break;
        case 6: {
            int tq;
            std::cout << "Enter time quantum: ";
            std::cin >> tq;
            scheduler = std::make_unique<RoundRobin>(tq);
            break;
        }
        default:
            std::cerr << "Invalid choice! Exiting...\n";
            return 1;
    }

    scheduler->schedule(processes);
    scheduler->printGanttChart();
    scheduler->plotGanttChart(); // New visualization
    scheduler->printMetrics(processes);

    return 0;
}
