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
    void schedule(std::vector<Process>& processes) override;
};

#endif