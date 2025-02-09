#include "scheduler.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <functional>
#include <vector>

//------------------------------------------------------------
// Provide definitions for missing constructors:
PreemptiveSJF::PreemptiveSJF() {}
PriorityScheduling::PriorityScheduling() {}
PreemptivePriorityScheduling::PreemptivePriorityScheduling() {}

//------------------------------------------------------------
// FCFS implementation (First-Come, First-Served)
void FCFS::schedule(std::vector<Process>& processes) {
    gantt.clear();
    int current_time = 0;
    for (auto& process : processes) {
        if (current_time < process.arrival_time)
            current_time = process.arrival_time;
        process.start_time = current_time;
        current_time += process.burst_time;
        process.finish_time = current_time;
        process.turnaround_time = process.finish_time - process.arrival_time;
        process.waiting_time = process.start_time - process.arrival_time;
        gantt.push_back(process.id);
    }
}

void FCFS::printGanttChart() {
    std::cout << "Gantt Chart: ";
    for (int id : gantt)
        std::cout << "P" << id << " ";
    std::cout << "\n";
}

void FCFS::printMetrics(std::vector<Process>& processes) {
    float total_waiting_time = 0, total_turnaround_time = 0;
    for (const auto& p : processes) {
        total_waiting_time += p.waiting_time;
        total_turnaround_time += p.turnaround_time;
    }
    std::cout << "Average Waiting Time: " 
              << total_waiting_time / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " 
              << total_turnaround_time / processes.size() << "\n";
}

//------------------------------------------------------------
// SJF implementation (Shortest Job First)
void SJF::schedule(std::vector<Process>& processes) {
    gantt.clear();
    // Sort processes by burst time
    std::sort(processes.begin(), processes.end(), [](Process& a, Process& b) {
        return a.burst_time < b.burst_time;
    });
    int current_time = 0;
    for (auto& process : processes) {
        if (current_time < process.arrival_time)
            current_time = process.arrival_time;
        process.start_time = current_time;
        current_time += process.burst_time;
        process.finish_time = current_time;
        process.turnaround_time = process.finish_time - process.arrival_time;
        process.waiting_time = process.start_time - process.arrival_time;
        gantt.push_back(process.id);
    }
}

void SJF::printGanttChart() {
    std::cout << "Gantt Chart: ";
    for (int id : gantt)
        std::cout << "P" << id << " ";
    std::cout << "\n";
}

void SJF::printMetrics(std::vector<Process>& processes) {
    float total_waiting_time = 0, total_turnaround_time = 0;
    for (const auto& p : processes) {
        total_waiting_time += p.waiting_time;
        total_turnaround_time += p.turnaround_time;
    }
    std::cout << "Average Waiting Time: " 
              << total_waiting_time / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " 
              << total_turnaround_time / processes.size() << "\n";
}

//------------------------------------------------------------
// Preemptive SJF implementation
void PreemptiveSJF::schedule(std::vector<Process>& processes) {
    gantt.clear();
    // Sort processes by arrival time
    std::sort(processes.begin(), processes.end(), [](Process& a, Process& b) {
        return a.arrival_time < b.arrival_time;
    });
    int current_time = 0;
    std::queue<Process*> ready_queue;
    size_t idx = 0;
    while (idx < processes.size() || !ready_queue.empty()) {
        while (idx < processes.size() && processes[idx].arrival_time <= current_time) {
            ready_queue.push(&processes[idx]);
            idx++;
        }
        if (!ready_queue.empty()) {
            // For simplicity, select the process with the smallest burst time from ready_queue
            std::vector<Process*> temp;
            while (!ready_queue.empty()) {
                temp.push_back(ready_queue.front());
                ready_queue.pop();
            }
            std::sort(temp.begin(), temp.end(), [](Process* a, Process* b) {
                return a->burst_time < b->burst_time;
            });
            Process* proc = temp.front();
            temp.erase(temp.begin());
            proc->start_time = current_time;
            current_time += proc->burst_time;
            proc->finish_time = current_time;
            proc->turnaround_time = proc->finish_time - proc->arrival_time;
            proc->waiting_time = proc->start_time - proc->arrival_time;
            // Record this execution segment in the Gantt chart
            gantt.push_back(proc->id);
            for (auto p : temp)
                ready_queue.push(p);
        } else {
            current_time++;
        }
    }
}

void PreemptiveSJF::printGanttChart() {
    std::cout << "Gantt Chart: ";
    for (int id : gantt)
        std::cout << "P" << id << " ";
    std::cout << "\n";
}

void PreemptiveSJF::printMetrics(std::vector<Process>& processes) {
    float total_waiting_time = 0, total_turnaround_time = 0;
    for (const auto& p : processes) {
        total_waiting_time += p.waiting_time;
        total_turnaround_time += p.turnaround_time;
    }
    std::cout << "Average Waiting Time: " 
              << total_waiting_time / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " 
              << total_turnaround_time / processes.size() << "\n";
}

//------------------------------------------------------------
// Priority Scheduling implementation (Non-preemptive)
void PriorityScheduling::schedule(std::vector<Process>& processes) {
    gantt.clear();
    // Lower numeric value means higher priority.
    std::sort(processes.begin(), processes.end(), [](Process& a, Process& b) {
        return a.priority < b.priority;
    });
    int current_time = 0;
    for (auto& process : processes) {
        if (current_time < process.arrival_time)
            current_time = process.arrival_time;
        process.start_time = current_time;
        current_time += process.burst_time;
        process.finish_time = current_time;
        process.turnaround_time = process.finish_time - process.arrival_time;
        process.waiting_time = process.start_time - process.arrival_time;
        gantt.push_back(process.id);
    }
}

void PriorityScheduling::printGanttChart() {
    std::cout << "Gantt Chart: ";
    for (int id : gantt)
        std::cout << "P" << id << " ";
    std::cout << "\n";
}

void PriorityScheduling::printMetrics(std::vector<Process>& processes) {
    float total_waiting_time = 0, total_turnaround_time = 0;
    for (const auto& p : processes) {
        total_waiting_time += p.waiting_time;
        total_turnaround_time += p.turnaround_time;
    }
    std::cout << "Average Waiting Time: " 
              << total_waiting_time / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " 
              << total_turnaround_time / processes.size() << "\n";
}

//------------------------------------------------------------
// Preemptive Priority Scheduling implementation
void PreemptivePriorityScheduling::schedule(std::vector<Process>& processes) {
    gantt.clear();
    // Sort by arrival time
    std::sort(processes.begin(), processes.end(), [](Process& a, Process& b) {
        return a.arrival_time < b.arrival_time;
    });
    int current_time = 0;
    std::priority_queue<Process*, std::vector<Process*>, std::function<bool(Process*, Process*)>> ready_queue(
        [](Process* a, Process* b) { return a->priority > b->priority; }
    );
    size_t idx = 0;
    while (idx < processes.size() || !ready_queue.empty()) {
        while (idx < processes.size() && processes[idx].arrival_time <= current_time) {
            ready_queue.push(&processes[idx]);
            idx++;
        }
        if (!ready_queue.empty()) {
            Process* proc = ready_queue.top();
            ready_queue.pop();
            proc->start_time = current_time;
            current_time += proc->burst_time;
            proc->finish_time = current_time;
            proc->turnaround_time = proc->finish_time - proc->arrival_time;
            proc->waiting_time = proc->start_time - proc->arrival_time;
            gantt.push_back(proc->id);
        } else {
            current_time++;
        }
    }
}

void PreemptivePriorityScheduling::printGanttChart() {
    std::cout << "Gantt Chart: ";
    for (int id : gantt)
        std::cout << "P" << id << " ";
    std::cout << "\n";
}

void PreemptivePriorityScheduling::printMetrics(std::vector<Process>& processes) {
    float total_waiting_time = 0, total_turnaround_time = 0;
    for (const auto& p : processes) {
        total_waiting_time += p.waiting_time;
        total_turnaround_time += p.turnaround_time;
    }
    std::cout << "Average Waiting Time: " 
              << total_waiting_time / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " 
              << total_turnaround_time / processes.size() << "\n";
}

//------------------------------------------------------------
// Round Robin implementation
void RoundRobin::schedule(std::vector<Process>& processes) {
    gantt.clear();
    int current_time = 0;
    std::queue<Process*> ready_queue;
    
    // Initialize remaining_time for each process
    for (auto& process : processes) {
        process.remaining_time = process.burst_time;
    }
    
    // Continue until all processes are finished
    while (true) {
        bool all_done = true;
        // Add processes that have arrived to the ready queue
        for (auto& process : processes) {
            if (process.arrival_time <= current_time && process.remaining_time > 0)
                ready_queue.push(&process);
            if (process.remaining_time > 0)
                all_done = false;
        }
        if (all_done)
            break;
        if (ready_queue.empty()) {
            current_time++;
            continue;
        }
        Process* proc = ready_queue.front();
        ready_queue.pop();
        int exec_time = (proc->remaining_time > time_quantum) ? time_quantum : proc->remaining_time;
        // Record execution segment in the Gantt chart for each time slice executed.
        gantt.push_back(proc->id);
        current_time += exec_time;
        proc->remaining_time -= exec_time;
        if (proc->remaining_time == 0) {
            proc->finish_time = current_time;
            proc->turnaround_time = proc->finish_time - proc->arrival_time;
            proc->waiting_time = proc->turnaround_time - proc->burst_time;
        }
    }
}

void RoundRobin::printGanttChart() {
    std::cout << "Gantt Chart: ";
    for (int id : gantt)
        std::cout << "P" << id << " ";
    std::cout << "\n";
}

void RoundRobin::printMetrics(std::vector<Process>& processes) {
    float total_waiting_time = 0, total_turnaround_time = 0;
    for (const auto& p : processes) {
        total_waiting_time += p.waiting_time;
        total_turnaround_time += p.turnaround_time;
    }
    std::cout << "Average Waiting Time: " 
              << total_waiting_time / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " 
              << total_turnaround_time / processes.size() << "\n";
}
