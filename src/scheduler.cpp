#include "scheduler.h"
#include <algorithm>
#include <iostream>

// FCFS Algorithm Implementation
void FCFS::schedule(std::vector<Process>& processes) {
    // Sort processes by arrival time
    std::sort(processes.begin(), processes.end(), 
        [](const Process& a, const Process& b) { return a.arrival_time < b.arrival_time; });

    int current_time = 0;
    for (auto& p : processes) {
        // Calculate waiting time
        int waiting_time = current_time - p.arrival_time;
        if (waiting_time < 0) waiting_time = 0; // Ensure waiting time is non-negative
        waiting_times.push_back(waiting_time);

        // Update current time (finish time of the current process)
        current_time = std::max(current_time, p.arrival_time) + p.burst_time;

        // Calculate turnaround time
        int turnaround_time = current_time - p.arrival_time;
        turnaround_times.push_back(turnaround_time);

        // Add to Gantt chart: track the start and end time for each process
        gantt_chart.push_back({p.id, current_time});
    }
}

// Print Gantt Chart
void Scheduler::printGanttChart() {
    std::cout << "\nGantt Chart:\n";
    for (size_t i = 0; i < gantt_chart.size(); i++) {
        std::cout << "P" << gantt_chart[i].first << " ";
    }
    std::cout << "\n";
}

// Print Performance Metrics
void Scheduler::printMetrics() {
    double avg_waiting_time = 0, avg_turnaround_time = 0;
    for (size_t i = 0; i < waiting_times.size(); ++i) {
        avg_waiting_time += waiting_times[i];
        avg_turnaround_time += turnaround_times[i];
    }
    avg_waiting_time /= waiting_times.size();
    avg_turnaround_time /= turnaround_times.size();

    std::cout << "\nPerformance Metrics:\n";
    std::cout << "Average Waiting Time: " << avg_waiting_time << "\n";
    std::cout << "Average Turnaround Time: " << avg_turnaround_time << "\n";
}
