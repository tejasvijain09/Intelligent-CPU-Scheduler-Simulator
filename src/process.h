#ifndef PROCESS_H
#define PROCESS_H

#include <SFML/Graphics.hpp>  // Include SFML for color support

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

    sf::Color getColor() const;  // Get the unique color for this process

private:
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    sf::Color color;  // Unique color for visualization
};

#endif // PROCESS_H