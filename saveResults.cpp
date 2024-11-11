#include "saveResults.h"


namespace fs = std::filesystem;

// Helper function to get current date and time as a string
std::string getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y%m%d_%H%M%S");
    return ss.str();
}

// Function to save the results to a file in the results directory
void saveResults(const std::string& algorithm, int numTasks, int numMachines,
                 const Schedule& optimalSchedule, double duration, const std::vector<Task>& tasks) {
    // Ensure the results directory exists
    std::string resultsDir = "results";
    fs::create_directories(resultsDir);

    // Construct the filename based on algorithm, tasks, machines, and current date and time
    std::string timestamp = getCurrentDateTime();
    std::string filename = resultsDir + "/" + algorithm + "_" + std::to_string(numTasks) + "tasks" +
                           std::to_string(numMachines) + "machines_" + timestamp + ".txt";

    // Open the file to save results
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    // Write information to the file
    outFile << "Algorithm: " << algorithm << "\n";
    outFile << "Dataset: " << numTasks << " tasks, " << numMachines << " machines\n";
    outFile << "Execution Time: " << duration << " seconds\n";
    outFile << "Makespan: " << optimalSchedule.makespan << "\n";
    outFile << "Optimized Schedule (Start Time, Duration, Gap):\n";

    // Write the schedule details for each machine
    for (int m = 0; m < numMachines; ++m) {
        outFile << "Machine " << m + 1 << ":\n";
        for (int t = 0; t < numTasks; ++t) {
            int startTime = optimalSchedule.startTimes[m][t];
            int duration = tasks[t].operationTimes[m];
            int gap = 0;

            // Calculate the gap only if this is not the last task
            if (t < numTasks - 1) {
                int nextStartTime = optimalSchedule.startTimes[m][t + 1];
                int endTime = startTime + duration;
                gap = nextStartTime - endTime;
            }

            outFile << "  Task " << t + 1 << ": "
                    << "Start Time = " << startTime << ", "
                    << "Duration = " << duration << ", "
                    << "Gap = " << gap << "\n";
        }
    }

    outFile.close();
    std::cout << "Results saved to " << filename << std::endl;
}
