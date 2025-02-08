#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "process.h"

class Scheduler {
public:
    virtual void schedule(std::vector<Process>& processes) = 0;
    void printGanttChart();
    void printMetrics();

protected:
    std::vector<std::pair<int, int>> gantt_chart; // {process_id, end_time}
    std::vector<int> waiting_times;
    std::vector<int> turnaround_times;
};

class FCFS : public Scheduler {
public:
    FCFS();
    void schedule(std::vector<Process>& processes) override;
};

class SJF : public Scheduler {
public:
    SJF();
    void schedule(std::vector<Process>& processes) override;
};

class RR : public Scheduler {
public:
    RR(int quantum);
    void schedule(std::vector<Process>& processes) override;

private:
    int quantum;  // Time quantum for round robin scheduling
};

#endif
