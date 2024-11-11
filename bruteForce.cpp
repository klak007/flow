#include "bruteForce.h"

// Recursive function to generate all valid schedules and calculate the minimum makespan
void generateSchedules(const std::vector<Task>& tasks, const std::vector<int>& minGaps, const std::vector<int>& maxGaps,
                       Schedule& currentSchedule, Schedule& bestSchedule, int machine, int task, int numMachines) {
    // Base case: if all tasks for all machines are scheduled
    if (machine == numMachines) {
        int makespan = calculateMakespan(currentSchedule, tasks);

        // Update the best schedule if the current one has a smaller makespan
        if (makespan < bestSchedule.makespan) {
            bestSchedule = currentSchedule;
            bestSchedule.makespan = makespan;
        }
        return;
    }

    // Move to the next machine after the last task on the current machine
    if (task == tasks.size()) {
        generateSchedules(tasks, minGaps, maxGaps, currentSchedule, bestSchedule, machine + 1, 0, numMachines);
        return;
    }

    // Determine the earliest feasible start time for the current task
    int startTime = 0;
    if (task > 0) {
        // Start time should respect the gap constraint from the previous task on the same machine
        int previousEndTime = currentSchedule.startTimes[machine][task - 1] + tasks[task - 1].operationTimes[machine];
        startTime = previousEndTime + minGaps[machine];
    }

    // Also consider dependency on the previous machine for the same task
    if (machine > 0) {
        int previousMachineEndTime = currentSchedule.startTimes[machine - 1][task] + tasks[task].operationTimes[machine - 1];
        startTime = std::max(startTime, previousMachineEndTime);
    }

    // Iterate over all feasible start times within the min and max gap constraints
    int maxStartTime = startTime + (task > 0 ? maxGaps[machine] : 0);
    for (int possibleStartTime = startTime; possibleStartTime <= maxStartTime; ++possibleStartTime) {
        currentSchedule.startTimes[machine][task] = possibleStartTime;
        generateSchedules(tasks, minGaps, maxGaps, currentSchedule, bestSchedule, machine, task + 1, numMachines);
    }
}

// Main brute-force scheduling function
Schedule bruteForce(const std::vector<Task>& tasks, const std::vector<int>& minGaps, const std::vector<int>& maxGaps) {
    int numMachines = tasks[0].operationTimes.size();
    int numTasks = tasks.size();

    // Initialize the best schedule with a high makespan value
    Schedule bestSchedule;
    bestSchedule.startTimes.resize(numMachines, std::vector<int>(numTasks, 0));
    bestSchedule.makespan = std::numeric_limits<int>::max();

    // Start with an empty current schedule
    Schedule currentSchedule;
    currentSchedule.startTimes.resize(numMachines, std::vector<int>(numTasks, 0));

    // Generate all valid schedules and find the one with the minimum makespan
    generateSchedules(tasks, minGaps, maxGaps, currentSchedule, bestSchedule, 0, 0, numMachines);

    return bestSchedule;
}
