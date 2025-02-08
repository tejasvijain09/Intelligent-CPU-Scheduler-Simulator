// process.h

#ifndef PROCESS_H
#define PROCESS_H

class Process {
public:
    int id;
    int arrival_time;
    int burst_time;
    int priority;

    Process(int _id, int _at, int _bt, int _prio);
};

#endif
