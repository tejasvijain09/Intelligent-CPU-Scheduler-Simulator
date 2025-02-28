#include "scheduler.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <iomanip>

//------------------------------------------------------------
// Helper Function to Print Gantt Chart
void SchedulingAlgorithm::printGanttChart() {
    std::cout << "\nGantt Chart:\n";
    std::cout << "--------------------------------------------------\n";
    int time = 0;
    for (const auto& segment : gantt_chart) {
        std::cout << "| P" << segment.first << " ";
        time += segment.second;
    }
    std::cout << "|\n--------------------------------------------------\n";

    time = 0;
    for (const auto& segment : gantt_chart) {
        std::cout << time << "\t";
        time += segment.second;
    }
    std::cout << time << "\n";
}

//------------------------------------------------------------
// Helper Function to Plot Gantt Chart
void SchedulingAlgorithm::plotGanttChart() {
    std::vector<double> x;
    std::vector<double> y;
    std::vector<std::string> labels;

    double time = 0;
    for (const auto& segment : gantt_chart) {
        x.push_back(time);
        y.push_back(segment.first);
        labels.push_back("P" + std::to_string(segment.first));
        time += segment.second;
    }

    plt::bar(x, y);
    plt::xticks(x, labels);
    plt::title("Gantt Chart Visualization");
    plt::xlabel("Time");
    plt::ylabel("Process ID");
    plt::show();
} 
//------------------------------------------------------------
// Helper Function to Print Metrics
void SchedulingAlgorithm::printMetrics(const std::vector<Process>& processes) {
    std::cout << "\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (const auto& process : processes) {
        std::cout << "P" << process.getId() << "\t"
                  << process.getArrivalTime() << "\t\t"
                  << process.getBurstTime() << "\t\t"
                  << process.getWaitingTime() << "\t\t"
                  << process.getTurnaroundTime() << "\n";
    }
}

//------------------------------------------------------------
// FCFS Implementation
void FCFS::schedule(std::vector<Process>& processes) {
    gantt_chart.clear();
    int current_time = 0;

    for (auto& process : processes) {
        if (current_time < process.getArrivalTime())
            current_time = process.getArrivalTime();

        process.setStartTime(current_time);
        current_time += process.getBurstTime();
        process.setFinishTime(current_time);
        process.setTurnaroundTime(process.getFinishTime() - process.getArrivalTime());
        process.setWaitingTime(process.getStartTime() - process.getArrivalTime());

        gantt_chart.push_back({process.getId(), process.getBurstTime()});
    }
}

//------------------------------------------------------------
// Shortest Job First (Non-Preemptive)
void SJF::schedule(std::vector<Process>& processes) {
    gantt_chart.clear();
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.getBurstTime() < b.getBurstTime();
    });

    int current_time = 0;
    for (auto& process : processes) {
        if (current_time < process.getArrivalTime())
            current_time = process.getArrivalTime();

        process.setStartTime(current_time);
        current_time += process.getBurstTime();
        process.setFinishTime(current_time);
        process.setTurnaroundTime(process.getFinishTime() - process.getArrivalTime());
        process.setWaitingTime(process.getStartTime() - process.getArrivalTime());

        gantt_chart.push_back({process.getId(), process.getBurstTime()});
    }
}

//------------------------------------------------------------
// Preemptive Shortest Job First (SJF)
void PreemptiveSJF::schedule(std::vector<Process>& processes) {
    gantt_chart.clear();
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });

    auto cmp = [](Process* a, Process* b) { return a->getRemainingTime() > b->getRemainingTime(); };
    std::priority_queue<Process*, std::vector<Process*>, decltype(cmp)> ready_queue(cmp);

    int current_time = 0, completed = 0;
    size_t idx = 0;

    while (completed < processes.size()) {
        while (idx < processes.size() && processes[idx].getArrivalTime() <= current_time) {
            ready_queue.push(&processes[idx]);
            idx++;
        }

        if (!ready_queue.empty()) {
            Process* proc = ready_queue.top();
            ready_queue.pop();
            proc->setRemainingTime(proc->getRemainingTime() - 1);
            gantt_chart.push_back({proc->getId(), 1});
            current_time++;

            if (proc->getRemainingTime() == 0) {
                proc->setFinishTime(current_time);
                proc->setTurnaroundTime(proc->getFinishTime() - proc->getArrivalTime());
                proc->setWaitingTime(proc->getTurnaroundTime() - proc->getBurstTime());
                completed++;
            } else {
                ready_queue.push(proc);
            }
        } else {
            current_time++;
        }
    }
}

//------------------------------------------------------------
// Priority Scheduling (Non-Preemptive)
void PriorityScheduling::schedule(std::vector<Process>& processes) {
    gantt_chart.clear();
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.getPriority() < b.getPriority();
    });

    int current_time = 0;
    for (auto& process : processes) {
        if (current_time < process.getArrivalTime())
            current_time = process.getArrivalTime();

        process.setStartTime(current_time);
        current_time += process.getBurstTime();
        process.setFinishTime(current_time);
        process.setTurnaroundTime(process.getFinishTime() - process.getArrivalTime());
        process.setWaitingTime(process.getStartTime() - process.getArrivalTime());

        gantt_chart.push_back({process.getId(), process.getBurstTime()});
    }
}

//------------------------------------------------------------
// Preemptive Priority Scheduling
void PreemptivePriorityScheduling::schedule(std::vector<Process>& processes) {
    gantt_chart.clear();
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });

    auto cmp = [](Process* a, Process* b) { return a->getPriority() > b->getPriority(); };
    std::priority_queue<Process*, std::vector<Process*>, decltype(cmp)> ready_queue(cmp);

    int current_time = 0, completed = 0;
    size_t idx = 0;

    while (completed < processes.size()) {
        while (idx < processes.size() && processes[idx].getArrivalTime() <= current_time) {
            ready_queue.push(&processes[idx]);
            idx++;
        }

        if (!ready_queue.empty()) {
            Process* proc = ready_queue.top();
            ready_queue.pop();
            proc->setRemainingTime(proc->getRemainingTime() - 1);
            gantt_chart.push_back({proc->getId(), 1});
            current_time++;

            if (proc->getRemainingTime() == 0) {
                proc->setFinishTime(current_time);
                proc->setTurnaroundTime(proc->getFinishTime() - proc->getArrivalTime());
                proc->setWaitingTime(proc->getTurnaroundTime() - proc->getBurstTime());
                completed++;
            } else {
                ready_queue.push(proc);
            }
        } else {
            current_time++;
        }
    }
}

//------------------------------------------------------------
// Round Robin Scheduling
void RoundRobin::schedule(std::vector<Process>& processes) {
    gantt_chart.clear();
    std::queue<Process*> ready_queue;
    int current_time = 0;

    for (auto& process : processes) {
        process.setRemainingTime(process.getBurstTime());
    }

    size_t idx = 0;
    while (idx < processes.size() || !ready_queue.empty()) {
        while (idx < processes.size() && processes[idx].getArrivalTime() <= current_time) {
            ready_queue.push(&processes[idx]);
            idx++;
        }

        if (!ready_queue.empty()) {
            Process* proc = ready_queue.front();
            ready_queue.pop();
            int exec_time = std::min(time_quantum, proc->getRemainingTime());
            gantt_chart.push_back({proc->getId(), exec_time});
            current_time += exec_time;
            proc->setRemainingTime(proc->getRemainingTime() - exec_time);

            if (proc->getRemainingTime() > 0) {
                ready_queue.push(proc);
            }
        } else {
            current_time++;
        }
    }
}
void RoundRobin::plotGanttChart() {
    SchedulingAlgorithm::plotGanttChart();  // Call base class function
}
void RoundRobin::printGanttChart() {
    SchedulingAlgorithm::printGanttChart();  // Call base class function
}
void PreemptiveSJF::printMetrics(const std::vector<Process>& processes) {
    SchedulingAlgorithm::printMetrics(processes);  // Call base class function
}
void PreemptiveSJF::plotGanttChart() {
    SchedulingAlgorithm::plotGanttChart();  // Call base class function
}
void PreemptiveSJF::printGanttChart() {
    SchedulingAlgorithm::printGanttChart();  // Call base class function
}
void PriorityScheduling::printMetrics(const std::vector<Process>& processes) {
    SchedulingAlgorithm::printMetrics(processes);  // Call base class function
}
void PriorityScheduling::plotGanttChart() {
    SchedulingAlgorithm::plotGanttChart();  // Call base class function
}
void PriorityScheduling::printGanttChart() {
    SchedulingAlgorithm::printGanttChart();  // Call base class function
}
void PreemptivePriorityScheduling::printGanttChart() {
    SchedulingAlgorithm::printGanttChart();  // Use base class function
}
void PreemptivePriorityScheduling::plotGanttChart() {
    SchedulingAlgorithm::plotGanttChart();  // Use base class function
}
void PreemptivePriorityScheduling::printMetrics(const std::vector<Process>& processes) {
    SchedulingAlgorithm::printMetrics(processes);  // Use base class function
}
void SJF::printGanttChart() {
    SchedulingAlgorithm::printGanttChart();  // Use base class function
}
void SJF::plotGanttChart() {
    SchedulingAlgorithm::plotGanttChart();  // Use base class function
}
void SJF::printMetrics(const std::vector<Process>& processes) {
    SchedulingAlgorithm::printMetrics(processes);  // Use base class function
}
void FCFS::printGanttChart() {
    SchedulingAlgorithm::printGanttChart();  // Use base class function
}
void FCFS::plotGanttChart() {
    SchedulingAlgorithm::plotGanttChart();  // Use base class function
}
void FCFS::printMetrics(const std::vector<Process>& processes) {
    SchedulingAlgorithm::printMetrics(processes);  // Use base class function
}