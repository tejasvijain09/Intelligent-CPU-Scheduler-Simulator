#include "scheduler.h"
#include <iostream>
#include <algorithm>
#include <climits>  // For INT_MAX

// Constructor for FCFS
FCFS::FCFS() {
    // Initialization (if needed)
}

void Scheduler::printGanttChart() {
    std::cout << "Gantt Chart: ";
    int last_time = 0;

    for (const auto& entry : gantt_chart) {
        int process_id = entry.first;
        int end_time = entry.second;

        // Repeat the process ID for each time unit it occupies
        for (int t = last_time; t < end_time; t++) {
            std::cout << "P" << process_id << " ";
        }
        last_time = end_time;  // Update the last time point
    }

    std::cout << std::endl;
}

void Scheduler::printMetrics() {
    double total_waiting_time = 0;
    double total_turnaround_time = 0;

    for (size_t i = 0; i < waiting_times.size(); ++i) {
        total_waiting_time += waiting_times[i];
        total_turnaround_time += turnaround_times[i];
    }

    std::cout << "\nPerformance Metrics:\n";
    std::cout << "Average Waiting Time: " << (total_waiting_time / waiting_times.size()) << std::endl;
    std::cout << "Average Turnaround Time: " << (total_turnaround_time / turnaround_times.size()) << std::endl;
}

// FCFS Algorithm Implementation
void FCFS::schedule(std::vector<Process>& processes) {
    // Sort processes by arrival time
    std::sort(processes.begin(), processes.end(),
        [](const Process& a, const Process& b) { return a.arrival_time < b.arrival_time; });

    int current_time = 0;
    for (auto& process : processes) {
        // Calculate waiting time
        waiting_times.push_back(current_time - process.arrival_time);

        // Update current time
        current_time += process.burst_time;

        // Calculate turnaround time
        turnaround_times.push_back(current_time - process.arrival_time);

        // Add to Gantt chart
        gantt_chart.emplace_back(process.id, current_time);
    }
}

// Constructor for SJF
SJF::SJF() {
    // Initialization (if needed)
}

// SJF Algorithm Implementation
void SJF::schedule(std::vector<Process>& processes) {
    // Sort processes by arrival time
    std::sort(processes.begin(), processes.end(),
        [](const Process& a, const Process& b) { return a.arrival_time < b.arrival_time; });

    int current_time = 0;
    size_t completed = 0;
    std::vector<bool> executed(processes.size(), false);

    while (completed < processes.size()) {
        int shortest_index = -1;
        int shortest_burst = INT_MAX;

        // Find the process with the shortest burst time that has arrived
        for (size_t i = 0; i < processes.size(); i++) {
            if (!executed[i] && processes[i].arrival_time <= current_time && processes[i].burst_time < shortest_burst) {
                shortest_burst = processes[i].burst_time;
                shortest_index = i;
            }
        }

        if (shortest_index != -1) {
            // Execute the process
            executed[shortest_index] = true;
            completed++;

            // Calculate waiting time
            waiting_times.push_back(current_time - processes[shortest_index].arrival_time);

            // Update current time
            current_time += processes[shortest_index].burst_time;

            // Calculate turnaround time
            turnaround_times.push_back(current_time - processes[shortest_index].arrival_time);

            // Add to Gantt chart
            gantt_chart.emplace_back(processes[shortest_index].id, current_time);
        } else {
            // No process is available to execute
            current_time++;
        }
    }
}
