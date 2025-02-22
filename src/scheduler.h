#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "process.h"
#include <SFML/Graphics.hpp>

class Scheduler {
public:
    virtual void schedule(std::vector<Process>& processes) = 0;
    virtual void printMetrics(const std::vector<Process>& processes) = 0;
    virtual void visualizeGanttChart(const std::vector<Process>& processes, const std::string& title) = 0;
    virtual ~Scheduler() = default;
};

// FCFS Scheduling Algorithm
class FCFS : public Scheduler {
public:
    void schedule(std::vector<Process>& processes) override;
    void printMetrics(const std::vector<Process>& processes) override;
    void visualizeGanttChart(const std::vector<Process>& processes, const std::string& title) override;
};

// SJF Scheduling Algorithm
class SJF : public Scheduler {
public:
    void schedule(std::vector<Process>& processes) override;
    void printMetrics(const std::vector<Process>& processes) override;
    void visualizeGanttChart(const std::vector<Process>& processes, const std::string& title) override;
};

// Priority Scheduling Algorithm
class PriorityScheduling : public Scheduler {
public:
    void schedule(std::vector<Process>& processes) override;
    void printMetrics(const std::vector<Process>& processes) override;
    void visualizeGanttChart(const std::vector<Process>& processes, const std::string& title) override;
};

// Round Robin Scheduling Algorithm
class RoundRobin : public Scheduler {
public:
    RoundRobin(int time_quantum);
    void schedule(std::vector<Process>& processes) override;
    void printMetrics(const std::vector<Process>& processes) override;
    void visualizeGanttChart(const std::vector<Process>& processes, const std::string& title) override;

private:
    int time_quantum;
};

#endif // SCHEDULER_H