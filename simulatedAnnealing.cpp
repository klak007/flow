#include "SimulatedAnnealing.h"


Schedule simulatedAnnealing(const std::vector<Task>& tasks, const std::vector<int>& minGaps, const std::vector<int>& maxGaps) {
    double temperature = 1000.0;
    double coolingRate = 0.995;
    int maxIterations = 10000;

    Schedule bestSchedule = generateInitialSchedule(tasks, minGaps, maxGaps);
    Schedule currentSchedule = bestSchedule;

    for (int iter = 0; iter < maxIterations; ++iter) {
        Schedule newSchedule = currentSchedule;

        // Small random adjustment to start times
        int machine = rand() % tasks[0].operationTimes.size();
        int task = rand() % tasks.size();
        int adjustment = (rand() % 3 - 1) * minGaps[machine];
        newSchedule.startTimes[machine][task] = std::max(0, newSchedule.startTimes[machine][task] + adjustment);

        if (isFeasible(newSchedule, tasks, minGaps, maxGaps)) {
            newSchedule.makespan = calculateMakespan(newSchedule, tasks);
            int delta = newSchedule.makespan - currentSchedule.makespan;

            if (delta < 0 || (exp(-delta / temperature) > (rand() / (RAND_MAX + 1.0)))) {
                currentSchedule = newSchedule;
                if (currentSchedule.makespan < bestSchedule.makespan) {
                    bestSchedule = currentSchedule;
                }
            }
        }
        temperature *= coolingRate;
    }
    return bestSchedule;
}

