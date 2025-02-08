#ifndef PROCESS_H
#define PROCESS_H

class Process {
public:
    Process(int id, int arrival_time, int burst_time, int priority);
    
    int getId() const;
    int getArrivalTime() const;
    int getBurstTime() const;
    int getPriority() const;
    int getRemainingTime() const;
    void setRemainingTime(int time);
    void setWaitingTime(int time);
    void setTurnaroundTime(int time);
    int getWaitingTime() const;
    int getTurnaroundTime() const;

private:
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

#endif // PROCESS_H
