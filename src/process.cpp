#include "process.h"

// Constructor definition
Process::Process(int id, int arrival_time, int burst_time, int priority)
    : id(id), arrival_time(arrival_time), burst_time(burst_time), priority(priority) {}
