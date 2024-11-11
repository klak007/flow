#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "Task.h"
#include "Schedule.h"
#include "SimulatedAnnealing.h"
#include "BruteForce.h"
#include "DataLoader.h"
#include "saveResults.h"


#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "Task.h"
#include "Schedule.h"
#include "SimulatedAnnealing.h"
#include "BruteForce.h"
#include "DataLoader.h"
#include "saveResults.h"
#include "greedyScheduling.h" // Include the new greedy scheduling algorithm header

int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <algorithm> <tasks> <machines>" << std::endl;
        std::cerr << "Available algorithms: sa (Simulated Annealing), bf (Brute Force), gs (Greedy Scheduling)" << std::endl;
        return 1;
    }

    std::string algorithm = argv[1];
    int numTasks = std::stoi(argv[2]);
    int numMachines = std::stoi(argv[3]);

    // Construct file names based on the number of tasks and machines
    std::string baseDir = "dataDirectory"; // Base directory for data
    std::string dataFile = baseDir + "/data/data" + std::to_string(numTasks) + "tasks" +
                           std::to_string(numMachines) + "machines.txt";
    std::string minGapsFile = baseDir + "/mingaps/mingaps" + std::to_string(numTasks) + "tasks" +
                              std::to_string(numMachines) + "machines.txt";
    std::string maxGapsFile = baseDir + "/maxgaps/maxgaps" + std::to_string(numTasks) + "tasks" +
                              std::to_string(numMachines) + "machines.txt";

    std::vector<Task> tasks;
    std::vector<int> minGaps, maxGaps;

    // Load tasks and gaps
    if (!loadTasks(dataFile, tasks, numMachines) ||
        !loadGaps(minGapsFile, minGaps) ||
        !loadGaps(maxGapsFile, maxGaps)) {
        std::cerr << "Error loading dataset files." << std::endl;
        return 1;
    }

    // Consistency check for gap sizes
    if (minGaps.size() != numMachines || maxGaps.size() != numMachines) {
        std::cerr << "Error: Gap data does not match the number of machines." << std::endl;
        return 1;
    }

    Schedule optimalSchedule;
    auto start = std::chrono::high_resolution_clock::now();  // Start time

    // Run the specified algorithm
    if (algorithm == "sa") {
        std::cout << "Running Simulated Annealing..." << std::endl;
        optimalSchedule = simulatedAnnealing(tasks, minGaps, maxGaps);
    } else if (algorithm == "bf") {
        std::cout << "Running Brute Force..." << std::endl;
        optimalSchedule = bruteForce(tasks, minGaps, maxGaps);
    } else if (algorithm == "gs") {
        std::cout << "Running Greedy Scheduling..." << std::endl;
        optimalSchedule = greedyScheduling(tasks, minGaps, maxGaps);
    } else {
        std::cerr << "Error: Unknown algorithm \"" << algorithm << "\"." << std::endl;
        std::cerr << "Available algorithms: sa (Simulated Annealing), bf (Brute Force), gs (Greedy Scheduling)" << std::endl;
        return 1;
    }

    auto end = std::chrono::high_resolution_clock::now();  // End time
    std::chrono::duration<double> duration = end - start;  // Calculate duration

    // Output the optimized schedule in the specified format
    std::cout << "Optimized Schedule (Start Time, Duration, Gap):\n";
    for (int m = 0; m < numMachines; ++m) {
        std::cout << "Machine " << m + 1 << ":\n";
        for (int t = 0; t < tasks.size(); ++t) {
            int startTime = optimalSchedule.startTimes[m][t];
            int duration = tasks[t].operationTimes[m];
            int gap = 0;

            // Calculate the gap only if this is not the last task
            if (t < tasks.size() - 1) {
                int nextStartTime = optimalSchedule.startTimes[m][t + 1];
                int endTime = startTime + duration;
                gap = nextStartTime - endTime;
            }

            std::cout << "  Task " << t + 1 << ": "
                      << "Start Time = " << startTime << ", "
                      << "Duration = " << duration << ", "
                      << "Gap = " << gap << "\n";
        }
    }
    std::cout << "Makespan: " << optimalSchedule.makespan << std::endl;

    // Output the time taken by the algorithm
    std::cout << "Algorithm execution time: " << duration.count() << " seconds." << std::endl;

    // Save results to file
    saveResults(algorithm, numTasks, numMachines, optimalSchedule, duration.count(), tasks);

    return 0;
}

