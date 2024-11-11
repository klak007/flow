#include "greedyScheduling.h"
#include <algorithm>

Schedule greedyScheduling(const std::vector<Task>& tasks, const std::vector<int>& minGaps, const std::vector<int>& maxGaps) {
    int numMachines = tasks[0].operationTimes.size();
    int numTasks = tasks.size();

    Schedule schedule;
    schedule.startTimes.resize(numMachines, std::vector<int>(numTasks, 0));

    // Initialize an array to keep track of the earliest available time for each machine
    std::vector<int> machineAvailability(numMachines, 0);

    // Schedule each task in order
    for (int t = 0; t < numTasks; ++t) {
        int taskStart = 0; // This will keep track of the start time of each task as it goes through all machines

        for (int m = 0; m < numMachines; ++m) {
            // The start time for this task on the current machine must respect the machine's availability and minGaps
            taskStart = std::max(machineAvailability[m], taskStart);

            if (t > 0) {
                // Apply minGap constraint if this is not the first task on this machine
                int previousEndTime = schedule.startTimes[m][t - 1] + tasks[t - 1].operationTimes[m];
                taskStart = std::max(taskStart, previousEndTime + minGaps[m]);

                // Apply maxGap constraint: ensure task start time does not exceed the max gap
                int maxAllowedStart = previousEndTime + maxGaps[m];
                taskStart = std::min(taskStart, maxAllowedStart);
            }

            // Schedule the task on the current machine at the calculated start time
            schedule.startTimes[m][t] = taskStart;

            // Update the machine's availability after this task finishes, considering minGap
            machineAvailability[m] = taskStart + tasks[t].operationTimes[m];
            if (t < numTasks - 1) {
                machineAvailability[m] += minGaps[m];
            }
        }
    }

    // Calculate the makespan for the schedule
    schedule.makespan = calculateMakespan(schedule, tasks);

    return schedule;
}
