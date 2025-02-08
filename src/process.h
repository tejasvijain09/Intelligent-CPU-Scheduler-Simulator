#ifndef PROCESS_H
#define PROCESS_H

class Process {
public:
    int id;
    int arrival_time;
    int burst_time;
    int priority;

    // Constructor declaration (not definition)
    Process(int id, int arrival_time, int burst_time, int priority);
};

#endif
