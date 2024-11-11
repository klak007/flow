#ifndef FLOW_SCHEDULE_H
#define FLOW_SCHEDULE_H

#include <vector>
#include <algorithm>
#include "Task.h"


struct Schedule {
    std::vector<std::vector<int>> startTimes; // startTimes[machine][task]
    int makespan; // Objective: minimize this

    // Function to calculate the makespan based on the task durations
    void calculateMakespan(const std::vector<Task>& tasks) {
        makespan = 0;  // Initialize makespan to zero

        // Iterate over each machine
        for (int machine = 0; machine < startTimes.size(); ++machine) {
            int machineFinishTime = 0;

            // Iterate over each task on this machine
            for (int task = 0; task < startTimes[machine].size(); ++task) {
                int startTime = startTimes[machine][task];
                int taskDuration = tasks[task].operationTimes[machine];
                int finishTime = startTime + taskDuration;

                // Update the machine's finish time to the latest finish time
                machineFinishTime = std::max(machineFinishTime, finishTime);
            }

            // Update the makespan with the maximum finish time across all machines
            makespan = std::max(makespan, machineFinishTime);
        }
    }
};

// Function declarations
Schedule generateInitialSchedule(const std::vector<Task>& tasks, const std::vector<int>& minGaps, const std::vector<int>& maxGaps);
int calculateMakespan(const Schedule& schedule, const std::vector<Task>& tasks);
bool isFeasible(const Schedule& schedule, const std::vector<Task>& tasks, const std::vector<int>& minGaps, const std::vector<int>& maxGaps);


#endif //FLOW_SCHEDULE_H
