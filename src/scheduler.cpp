#include "scheduler.h"
#include <iostream>
#include <algorithm>
#include <climits>  // For INT_MAX
#include <queue>    // For queue in RR

// FCFS constructor
FCFS::FCFS() {}

// FCFS scheduling algorithm
void FCFS::schedule(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(),
              [](const Process& a, const Process& b) { return a.arrival_time < b.arrival_time; });

    int current_time = 0;
    for (auto& process : processes) {
        waiting_times.push_back(current_time - process.arrival_time);
        current_time += process.burst_time;
        turnaround_times.push_back(current_time - process.arrival_time);
        gantt_chart.emplace_back(process.id, current_time);
    }
}

// SJF constructor
SJF::SJF() {}

// SJF scheduling algorithm
void SJF::schedule(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(),
              [](const Process& a, const Process& b) { return a.arrival_time < b.arrival_time; });

    int current_time = 0;
    size_t completed = 0;
    std::vector<bool> executed(processes.size(), false);

    while (completed < processes.size()) {
        int shortest_index = -1;
        int shortest_burst = INT_MAX;

        for (size_t i = 0; i < processes.size(); i++) {
            if (!executed[i] && processes[i].arrival_time <= current_time && processes[i].burst_time < shortest_burst) {
                shortest_burst = processes[i].burst_time;
                shortest_index = i;
            }
        }

        if (shortest_index != -1) {
            executed[shortest_index] = true;
            completed++;
            waiting_times.push_back(current_time - processes[shortest_index].arrival_time);
            current_time += processes[shortest_index].burst_time;
            turnaround_times.push_back(current_time - processes[shortest_index].arrival_time);
            gantt_chart.emplace_back(processes[shortest_index].id, current_time);
        } else {
            current_time++;
        }
    }
}

// RR constructor
RR::RR(int quantum) : quantum(quantum) {}

// Round Robin scheduling algorithm
void RR::schedule(std::vector<Process>& processes) {
    std::queue<Process*> ready_queue;
    int current_time = 0;
    size_t completed = 0;

    std::vector<bool> executed(processes.size(), false);
    std::vector<int> remaining_burst(processes.size());

    // Copy burst time for each process as remaining burst time
    for (size_t i = 0; i < processes.size(); i++) {
        remaining_burst[i] = processes[i].burst_time;
    }

    // Main Round Robin loop
    while (completed < processes.size()) {
        for (size_t i = 0; i < processes.size(); i++) {
            if (processes[i].arrival_time <= current_time && !executed[i]) {
                ready_queue.push(&processes[i]);
            }
        }

        if (!ready_queue.empty()) {
            Process* current_process = ready_queue.front();
            ready_queue.pop();

            // If the remaining burst time of this process is less than or equal to quantum, it completes
            int execution_time = std::min(quantum, remaining_burst[current_process->id - 1]);
            remaining_burst[current_process->id - 1] -= execution_time;
            current_time += execution_time;

            // Add to Gantt chart
            gantt_chart.emplace_back(current_process->id, current_time);

            // If process is completed, record its waiting and turnaround times
            if (remaining_burst[current_process->id - 1] == 0) {
                executed[current_process->id - 1] = true;
                completed++;
                waiting_times.push_back(current_time - current_process->arrival_time - current_process->burst_time);
                turnaround_times.push_back(current_time - current_process->arrival_time);
            }

            // If the process still has burst time left, add it back to the queue
            if (remaining_burst[current_process->id - 1] > 0) {
                ready_queue.push(current_process);
            }
        } else {
            // No process available, increment time
            current_time++;
        }
    }
}

// Print Gantt Chart
void Scheduler::printGanttChart() {
    std::cout << "\nGantt Chart:\n";
    for (const auto& entry : gantt_chart) {
        std::cout << "P" << entry.first << " ";
    }
    std::cout << "\n";
}

// Print Metrics (Average Waiting Time and Turnaround Time)
void Scheduler::printMetrics() {
    double avg_waiting_time = 0.0;
    double avg_turnaround_time = 0.0;

    for (size_t i = 0; i < waiting_times.size(); i++) {
        avg_waiting_time += waiting_times[i];
        avg_turnaround_time += turnaround_times[i];
    }

    avg_waiting_time /= waiting_times.size();
    avg_turnaround_time /= turnaround_times.size();

    std::cout << "Average Waiting Time: " << avg_waiting_time << "\n";
    std::cout << "Average Turnaround Time: " << avg_turnaround_time << "\n";
}
