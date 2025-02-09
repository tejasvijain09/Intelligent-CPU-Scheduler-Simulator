#ifndef PROCESS_H
#define PROCESS_H

class Process {
public:
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;  // For preemptive algorithms
    int start_time;      
    int finish_time;     
    int waiting_time;    
    int turnaround_time; 

    Process(int id, int arrival, int burst, int prio);
};

#endif
