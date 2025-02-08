#include "scheduler.h"
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

// FCFS Algorithm
void FCFS::schedule(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });

    int current_time = 0;
    for (auto& process : processes) {
        process.setWaitingTime(current_time - process.getArrivalTime());
        process.setTurnaroundTime(process.getWaitingTime() + process.getBurstTime());
        current_time += process.getBurstTime();
    }
}

void FCFS::printMetrics(const vector<Process>& processes) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    for (const auto& process : processes) {
        total_waiting_time += process.getWaitingTime();
        total_turnaround_time += process.getTurnaroundTime();
    }
    cout << "FCFS - Average Waiting Time: " << total_waiting_time / processes.size() << endl;
    cout << "FCFS - Average Turnaround Time: " << total_turnaround_time / processes.size() << endl;
}

void FCFS::printGanttChart(const vector<Process>& processes) {
    for (const auto& process : processes) {
        cout << "Process ID: " << process.getId() 
             << " | Waiting Time: " << process.getWaitingTime() 
             << " | Turnaround Time: " << process.getTurnaroundTime() << endl;
    }
}

// SJF Algorithm
void SJF::schedule(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.getBurstTime() < b.getBurstTime();
    });

    int current_time = 0;
    for (auto& process : processes) {
        process.setWaitingTime(current_time - process.getArrivalTime());
        process.setTurnaroundTime(process.getWaitingTime() + process.getBurstTime());
        current_time += process.getBurstTime();
    }
}

void SJF::printMetrics(const vector<Process>& processes) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    for (const auto& process : processes) {
        total_waiting_time += process.getWaitingTime();
        total_turnaround_time += process.getTurnaroundTime();
    }
    cout << "SJF - Average Waiting Time: " << total_waiting_time / processes.size() << endl;
    cout << "SJF - Average Turnaround Time: " << total_turnaround_time / processes.size() << endl;
}

void SJF::printGanttChart(const vector<Process>& processes) {
    for (const auto& process : processes) {
        cout << "Process ID: " << process.getId() 
             << " | Waiting Time: " << process.getWaitingTime() 
             << " | Turnaround Time: " << process.getTurnaroundTime() << endl;
    }
}

// Priority Scheduling Algorithm
void PriorityScheduling::schedule(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.getPriority() < b.getPriority();
    });

    int current_time = 0;
    for (auto& process : processes) {
        process.setWaitingTime(current_time - process.getArrivalTime());
        process.setTurnaroundTime(process.getWaitingTime() + process.getBurstTime());
        current_time += process.getBurstTime();
    }
}

void PriorityScheduling::printMetrics(const vector<Process>& processes) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    for (const auto& process : processes) {
        total_waiting_time += process.getWaitingTime();
        total_turnaround_time += process.getTurnaroundTime();
    }
    cout << "Priority Scheduling - Average Waiting Time: " << total_waiting_time / processes.size() << endl;
    cout << "Priority Scheduling - Average Turnaround Time: " << total_turnaround_time / processes.size() << endl;
}

void PriorityScheduling::printGanttChart(const vector<Process>& processes) {
    for (const auto& process : processes) {
        cout << "Process ID: " << process.getId() 
             << " | Waiting Time: " << process.getWaitingTime() 
             << " | Turnaround Time: " << process.getTurnaroundTime() << endl;
    }
}

// Round Robin Scheduling Algorithm
RoundRobin::RoundRobin(int time_quantum) : time_quantum(time_quantum) {}

void RoundRobin::schedule(vector<Process>& processes) {
    queue<Process*> ready_queue;
    int current_time = 0;

    for (auto& process : processes) {
        process.setRemainingTime(process.getBurstTime());
        ready_queue.push(&process);
    }

    while (!ready_queue.empty()) {
        Process* process = ready_queue.front();
        ready_queue.pop();

        if (process->getRemainingTime() > time_quantum) {
            process->setRemainingTime(process->getRemainingTime() - time_quantum);
            current_time += time_quantum;
            ready_queue.push(process);
        } else {
            current_time += process->getRemainingTime();
            process->setWaitingTime(current_time - process->getBurstTime() - process->getArrivalTime());
            process->setTurnaroundTime(process->getWaitingTime() + process->getBurstTime());
            process->setRemainingTime(0);
        }
    }
}

void RoundRobin::printMetrics(const vector<Process>& processes) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    for (const auto& process : processes) {
        total_waiting_time += process.getWaitingTime();
        total_turnaround_time += process.getTurnaroundTime();
    }
    cout << "Round Robin - Average Waiting Time: " << total_waiting_time / processes.size() << endl;
    cout << "Round Robin - Average Turnaround Time: " << total_turnaround_time / processes.size() << endl;
}

void RoundRobin::printGanttChart(const vector<Process>& processes) {
    for (const auto& process : processes) {
        cout << "Process ID: " << process.getId() 
             << " | Waiting Time: " << process.getWaitingTime() 
             << " | Turnaround Time: " << process.getTurnaroundTime() << endl;
    }
}
