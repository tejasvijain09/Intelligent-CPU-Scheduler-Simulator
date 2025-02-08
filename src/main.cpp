#include <iostream>
#include "process.h"

int main() {
    Process p(1, 0, 5, 1);
    std::cout << "Process P" << p.id << " created with:\n";
    std::cout << "Arrival Time: " << p.arrival_time << "\n";
    std::cout << "Burst Time: " << p.burst_time << "\n";
    std::cout << "Priority: " << p.priority << "\n";
    return 0;
}