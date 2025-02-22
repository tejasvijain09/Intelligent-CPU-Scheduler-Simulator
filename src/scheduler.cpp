#include "scheduler.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <queue>
#include <optional>

using namespace std;

// Helper function to visualize Gantt chart
void visualizeGanttChart(const vector<Process>& processes, const string& title) {
    // Create window with SFML 3.0-compatible VideoMode
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 200)), title);
    window.setFramerateLimit(60);

    // Load font
    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        cerr << "Error loading font!" << endl;
        return;
    }

    // Calculate total simulation time
    int total_time = 0;
    for (const auto& process : processes) {
        total_time = max(total_time, process.getTurnaroundTime());
    }

    // Define parameters for Gantt chart
    const float bar_height = 30.0f;
    const float bar_spacing = 10.0f;
    const float margin = 50.0f;
    const float time_scale = 700.0f / total_time;

    // Main loop
    while (window.isOpen()) {
        // Handle events with std::optional
        while (std::optional<sf::Event> event = window.pollEvent()) {
            if (event->type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the window
        window.clear(sf::Color::White);

        // Draw Gantt bars
        float x = margin;
        for (const auto& process : processes) {
            // Calculate bar dimensions
            float bar_width = process.getBurstTime() * time_scale;

            // Draw process bar
            sf::RectangleShape bar(sf::Vector2f(bar_width, bar_height));
            bar.setPosition(sf::Vector2f(x, margin));
            bar.setFillColor(process.getColor());  // Use process-specific color
            window.draw(bar);

            // Draw process ID label
            sf::Text text("", font, 16);  // Initialize with font, string, and character size
            text.setString("P" + to_string(process.getId()));
            text.setFillColor(sf::Color::Black);
            text.setPosition(sf::Vector2f(x + 5, margin + 5));
            window.draw(text);

            // Update x position for the next bar
            x += bar_width + bar_spacing;
        }

        // Draw timeline
        sf::VertexArray timeline(sf::PrimitiveType::Lines, 2);
        timeline[0].position = sf::Vector2f(margin, margin + bar_height + 10);
        timeline[1].position = sf::Vector2f(margin + 700, margin + bar_height + 10);
        timeline[0].color = sf::Color::Black;
        timeline[1].color = sf::Color::Black;
        window.draw(timeline);

        // Draw time markers
        for (int t = 0; t <= total_time; t += 5) {
            float marker_x = margin + t * time_scale;

            // Draw marker line
            sf::VertexArray marker(sf::PrimitiveType::Lines, 2);
            marker[0].position = sf::Vector2f(marker_x, margin + bar_height + 5);
            marker[1].position = sf::Vector2f(marker_x, margin + bar_height + 15);
            marker[0].color = sf::Color::Black;
            marker[1].color = sf::Color::Black;
            window.draw(marker);

            // Draw time label
            sf::Text time_text("", font, 12);  // Initialize with font, string, and character size
            time_text.setString(to_string(t));
            time_text.setFillColor(sf::Color::Black);
            time_text.setPosition(sf::Vector2f(marker_x - 5, margin + bar_height + 20));
            window.draw(time_text);
        }

        // Display the window
        window.display();
    }
}

// FCFS Algorithm
void FCFS::schedule(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });

    int current_time = 0;
    for (auto& process : processes) {
        process.setWaitingTime(current_time - process.getArrivalTime());
        process.setTurnaroundTime(process.getWaitingTime() + process.getBurstTime());
        current_time += process.getBurstTime();
    }
}

void FCFS::printMetrics(const vector<Process>& processes) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    for (const auto& process : processes) {
        total_waiting_time += process.getWaitingTime();
        total_turnaround_time += process.getTurnaroundTime();
    }
    cout << "FCFS - Average Waiting Time: " << total_waiting_time / processes.size() << endl;
    cout << "FCFS - Average Turnaround Time: " << total_turnaround_time / processes.size() << endl;
}

void FCFS::visualizeGanttChart(const vector<Process>& processes, const string& title) {
    ::visualizeGanttChart(processes, title);
}

// SJF Algorithm
void SJF::schedule(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.getBurstTime() < b.getBurstTime();
    });

    int current_time = 0;
    for (auto& process : processes) {
        process.setWaitingTime(current_time - process.getArrivalTime());
        process.setTurnaroundTime(process.getWaitingTime() + process.getBurstTime());
        current_time += process.getBurstTime();
    }
}

void SJF::printMetrics(const vector<Process>& processes) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    for (const auto& process : processes) {
        total_waiting_time += process.getWaitingTime();
        total_turnaround_time += process.getTurnaroundTime();
    }
    cout << "SJF - Average Waiting Time: " << total_waiting_time / processes.size() << endl;
    cout << "SJF - Average Turnaround Time: " << total_turnaround_time / processes.size() << endl;
}

void SJF::visualizeGanttChart(const vector<Process>& processes, const string& title) {
    ::visualizeGanttChart(processes, title);
}

// Priority Scheduling Algorithm
void PriorityScheduling::schedule(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.getPriority() < b.getPriority();
    });

    int current_time = 0;
    for (auto& process : processes) {
        process.setWaitingTime(current_time - process.getArrivalTime());
        process.setTurnaroundTime(process.getWaitingTime() + process.getBurstTime());
        current_time += process.getBurstTime();
    }
}

void PriorityScheduling::printMetrics(const vector<Process>& processes) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    for (const auto& process : processes) {
        total_waiting_time += process.getWaitingTime();
        total_turnaround_time += process.getTurnaroundTime();
    }
    cout << "Priority Scheduling - Average Waiting Time: " << total_waiting_time / processes.size() << endl;
    cout << "Priority Scheduling - Average Turnaround Time: " << total_turnaround_time / processes.size() << endl;
}

void PriorityScheduling::visualizeGanttChart(const vector<Process>& processes, const string& title) {
    ::visualizeGanttChart(processes, title);
}

// Round Robin Scheduling Algorithm
RoundRobin::RoundRobin(int time_quantum) : time_quantum(time_quantum) {}

void RoundRobin::schedule(vector<Process>& processes) {
    queue<Process*> ready_queue;
    int current_time = 0;

    for (auto& process : processes) {
        process.setRemainingTime(process.getBurstTime());
        ready_queue.push(&process);
    }

    while (!ready_queue.empty()) {
        Process* process = ready_queue.front();
        ready_queue.pop();

        if (process->getRemainingTime() > time_quantum) {
            process->setRemainingTime(process->getRemainingTime() - time_quantum);
            current_time += time_quantum;
            ready_queue.push(process);
        } else {
            current_time += process->getRemainingTime();
            process->setWaitingTime(current_time - process->getBurstTime() - process->getArrivalTime());
            process->setTurnaroundTime(process->getWaitingTime() + process->getBurstTime());
            process->setRemainingTime(0);
        }
    }
}

void RoundRobin::printMetrics(const vector<Process>& processes) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    for (const auto& process : processes) {
        total_waiting_time += process.getWaitingTime();
        total_turnaround_time += process.getTurnaroundTime();
    }
    cout << "Round Robin - Average Waiting Time: " << total_waiting_time / processes.size() << endl;
    cout << "Round Robin - Average Turnaround Time: " << total_turnaround_time / processes.size() << endl;
}

void RoundRobin::visualizeGanttChart(const vector<Process>& processes, const string& title) {
    ::visualizeGanttChart(processes, title);
}