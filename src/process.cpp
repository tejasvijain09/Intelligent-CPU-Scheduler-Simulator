#include "process.h"

Process::Process(int id, int arrival, int burst, int prio)
    : id(id), arrival_time(arrival), burst_time(burst), priority(prio), 
      remaining_time(burst), start_time(-1), finish_time(-1), 
      waiting_time(-1), turnaround_time(-1) {}
