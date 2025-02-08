#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "process.h"

class Scheduler {
public:
    virtual void schedule(std::vector<Process>& processes) = 0;
    virtual void printMetrics(const std::vector<Process>& processes) = 0;
    virtual void printGanttChart(const std::vector<Process>& processes) = 0;
    virtual ~Scheduler() = default;
};

// FCFS Scheduling Algorithm
class FCFS : public Scheduler {
public:
    void schedule(std::vector<Process>& processes) override;
    void printMetrics(const std::vector<Process>& processes) override;
    void printGanttChart(const std::vector<Process>& processes) override;
};

// SJF Scheduling Algorithm
class SJF : public Scheduler {
public:
    void schedule(std::vector<Process>& processes) override;
    void printMetrics(const std::vector<Process>& processes) override;
    void printGanttChart(const std::vector<Process>& processes) override;
};

// Priority Scheduling Algorithm
class PriorityScheduling : public Scheduler {
public:
    void schedule(std::vector<Process>& processes) override;
    void printMetrics(const std::vector<Process>& processes) override;
    void printGanttChart(const std::vector<Process>& processes) override;
};

// Round Robin Scheduling Algorithm
class RoundRobin : public Scheduler {
public:
    RoundRobin(int time_quantum);
    void schedule(std::vector<Process>& processes) override;
    void printMetrics(const std::vector<Process>& processes) override;
    void printGanttChart(const std::vector<Process>& processes) override;

private:
    int time_quantum;
};

#endif // SCHEDULER_H
