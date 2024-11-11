#include "Schedule.h"


int calculateMakespan(const Schedule& schedule, const std::vector<Task>& tasks) {
    int makespan = 0;
    int numMachines = schedule.startTimes.size();
    int numTasks = tasks.size();

    for (int m = 0; m < numMachines; ++m) {
        int lastTaskEnd = schedule.startTimes[m][numTasks - 1] + tasks[numTasks - 1].operationTimes[m];
        makespan = std::max(makespan, lastTaskEnd);
    }

    return makespan;
}

Schedule generateInitialSchedule(const std::vector<Task>& tasks, const std::vector<int>& minGaps, const std::vector<int>& maxGaps) {
    Schedule schedule;
    int numMachines = tasks[0].operationTimes.size();
    int numTasks = tasks.size();
    schedule.startTimes.resize(numMachines, std::vector<int>(numTasks, 0));

    for (int m = 0; m < numMachines; ++m) {
        int currentTime = 0;
        for (int t = 0; t < numTasks; ++t) {
            schedule.startTimes[m][t] = currentTime;
            currentTime += tasks[t].operationTimes[m];
            if (t < numTasks - 1) {
                currentTime += minGaps[m];
            }
        }
    }

    // Calculate and set the makespan for the initial schedule
    schedule.makespan = calculateMakespan(schedule, tasks);
    return schedule;
}

bool isFeasible(const Schedule& schedule, const std::vector<Task>& tasks, const std::vector<int>& minGaps, const std::vector<int>& maxGaps) {
    int numMachines = schedule.startTimes.size();
    for (int m = 0; m < numMachines; ++m) {
        for (int t = 0; t < tasks.size() - 1; ++t) {
            int gap = schedule.startTimes[m][t + 1] - (schedule.startTimes[m][t] + tasks[t].operationTimes[m]);
            if (gap < minGaps[m] || gap > maxGaps[m]) {
                return false;
            }
        }
    }
    return true;
}
