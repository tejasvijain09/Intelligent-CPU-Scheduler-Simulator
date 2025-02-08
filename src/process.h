#ifndef PROCESS_H
#define PROCESS_H

class Process {
public:
    int id;
    int arrival_time;
    int burst_time;
    int priority;

    // Constructor
    Process(int _id, int _at, int _bt, int _prio)
        : id(_id), arrival_time(_at), burst_time(_bt), priority(_prio) {}
};

#endif