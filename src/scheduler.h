#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "process.h"

class Scheduler {
public:
    virtual void schedule(std::vector<Process>& processes) = 0;

    // These need to be defined in the cpp file
    void printGanttChart();
    void printMetrics();

protected:
    std::vector<std::pair<int, int>> gantt_chart; // {process_id, end_time}
    std::vector<int> waiting_times;
    std::vector<int> turnaround_times;
};

class FCFS : public Scheduler {
public:
    FCFS();  // Constructor declaration
    void schedule(std::vector<Process>& processes) override;
};

class SJF : public Scheduler {
public:
    SJF();  // Constructor declaration for SJF
    void schedule(std::vector<Process>& processes) override;
};

#endif
