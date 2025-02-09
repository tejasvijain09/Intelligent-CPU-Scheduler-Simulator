#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "process.h"

// Abstract base class for scheduling algorithms
class SchedulingAlgorithm {
public:
    virtual void schedule(std::vector<Process>& processes) = 0;
    virtual void printGanttChart() = 0;
    virtual void printMetrics(std::vector<Process>& processes) = 0;
    virtual ~SchedulingAlgorithm() = default; // Virtual destructor for cleanup

protected:
    // This vector will store the execution sequence (process IDs)
    std::vector<int> gantt;
};

class FCFS : public SchedulingAlgorithm {
public:
    void schedule(std::vector<Process>& processes) override;
    void printGanttChart() override;
    void printMetrics(std::vector<Process>& processes) override;
};

class SJF : public SchedulingAlgorithm {
public:
    void schedule(std::vector<Process>& processes) override;
    void printGanttChart() override;
    void printMetrics(std::vector<Process>& processes) override;
};

class PreemptiveSJF : public SchedulingAlgorithm {
public:
    PreemptiveSJF();  // Constructor declaration
    void schedule(std::vector<Process>& processes) override;
    void printGanttChart() override;
    void printMetrics(std::vector<Process>& processes) override;
};

class PriorityScheduling : public SchedulingAlgorithm {
public:
    PriorityScheduling();  // Constructor declaration
    void schedule(std::vector<Process>& processes) override;
    void printGanttChart() override;
    void printMetrics(std::vector<Process>& processes) override;
};

class PreemptivePriorityScheduling : public SchedulingAlgorithm {
public:
    PreemptivePriorityScheduling();  // Constructor declaration
    void schedule(std::vector<Process>& processes) override;
    void printGanttChart() override;
    void printMetrics(std::vector<Process>& processes) override;
};

class RoundRobin : public SchedulingAlgorithm {
private:
    int time_quantum;  // Member variable to store the time quantum

public:
    RoundRobin(int tq) : time_quantum(tq) {}  // Constructor to initialize time_quantum
    void schedule(std::vector<Process>& processes) override;
    void printGanttChart() override;
    void printMetrics(std::vector<Process>& processes) override;
};

#endif // SCHEDULER_H
