#include "process.h"

Process::Process(int id, int arrival_time, int burst_time, int priority)
    : id(id), arrival_time(arrival_time), burst_time(burst_time), priority(priority), 
      remaining_time(burst_time), waiting_time(0), turnaround_time(0) {}

int Process::getId() const { return id; }
int Process::getArrivalTime() const { return arrival_time; }
int Process::getBurstTime() const { return burst_time; }
int Process::getPriority() const { return priority; }
int Process::getRemainingTime() const { return remaining_time; }

void Process::setRemainingTime(int time) {
    remaining_time = time;
}

void Process::setWaitingTime(int time) {
    waiting_time = time;
}

void Process::setTurnaroundTime(int time) {
    turnaround_time = time;
}

int Process::getWaitingTime() const { return waiting_time; }
int Process::getTurnaroundTime() const { return turnaround_time; }
