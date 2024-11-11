#include "generateData.h"


namespace fs = std::filesystem;

void printGeneratedData(const std::vector<Task>& tasks, const std::vector<int>& minGaps, const std::vector<int>& maxGaps) {
    std::cout << "Number of Machines: " << tasks[0].operationTimes.size() << ", Number of Tasks: " << tasks.size() << "\n\n";
    for (int i = 0; i < tasks.size(); ++i) {
        std::cout << "Task " << i + 1 << ": ";
        for (int time : tasks[i].operationTimes) {
            std::cout << time << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\nMin gaps:\n";
    for (int gap : minGaps) std::cout << gap << " ";
    std::cout << "\nMax gaps:\n";
    for (int gap : maxGaps) std::cout << gap << " ";
    std::cout << "\n\n";
}

void generateInstance(int numMachines, int numTasks, int minTime, int maxTime,
                      int minGap, int maxGap, const std::string& filename) {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    std::vector<Task> tasks;
    std::vector<int> minGaps, maxGaps; // Initialize minGaps and maxGaps here to ensure they are empty each time

    // Generate tasks and operation times
    for (int i = 0; i < numTasks; ++i) {
        Task task;
        for (int j = 0; j < numMachines; ++j) {
            int operationTime = minTime + rand() % (maxTime - minTime + 1);
            task.operationTimes.push_back(operationTime);
        }
        tasks.push_back(task);
    }

    // Generate time constraints for machines
    for (int i = 0; i < numMachines; ++i) {
        int minGapValue = minGap + rand() % (maxGap - minGap + 1);
        int maxGapValue = minGapValue + rand() % (maxGap - minGapValue + 1);
        minGaps.push_back(minGapValue);
        maxGaps.push_back(maxGapValue);
    }

    // **Consistency check**
    //std::cout << "After generation, minGaps size: " << minGaps.size() << ", maxGaps size: " << maxGaps.size() << "\n";
    if (minGaps.size() != numMachines || maxGaps.size() != numMachines) {
        std::cerr << "Error: Generated gap data does not match the number of machines." << std::endl;
        return;
    }
    //std::cout << "Consistency check passed\n";

    // Print to console (keeping your existing console output)
    //printGeneratedData(tasks, minGaps, maxGaps);

    // Write main data to file
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    try {
        // Write number of machines and tasks
        outFile << numMachines << " " << numTasks << "\n";
        if (outFile.fail()) throw std::runtime_error("Failed to write dimensions");

        // Write tasks
        for (const auto& task : tasks) {
            for (int time : task.operationTimes) {
                outFile << time << " ";
                if (outFile.fail()) throw std::runtime_error("Failed to write task times");
            }
            outFile << "\n";
        }

        outFile.close();
        std::cout << "Data successfully saved to " << filename << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error writing to file: " << e.what() << std::endl;
        outFile.close();
        return;
    }

    // Write min gaps to mingaps.txt
    std::ofstream minGapFile("mingaps.txt");
    if (!minGapFile.is_open()) {
        std::cerr << "Error: Could not open file mingaps.txt for writing." << std::endl;
        return;
    }

    try {
        for (int gap : minGaps) {
            minGapFile << gap << " ";
            if (minGapFile.fail()) throw std::runtime_error("Failed to write min gaps");
        }
        minGapFile << "\n";
        minGapFile.close();
        std::cout << "Min gaps successfully saved to mingaps.txt" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error writing min gaps to file: " << e.what() << std::endl;
        minGapFile.close();
        return;
    }

    // Write max gaps to maxgaps.txt
    std::ofstream maxGapFile("maxgaps.txt");
    if (!maxGapFile.is_open()) {
        std::cerr << "Error: Could not open file maxgaps.txt for writing." << std::endl;
        return;
    }

    try {
        for (int gap : maxGaps) {
            maxGapFile << gap << " ";
            if (maxGapFile.fail()) throw std::runtime_error("Failed to write max gaps");
        }
        maxGapFile << "\n";
        maxGapFile.close();
        std::cout << "Max gaps successfully saved to maxgaps.txt" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error writing max gaps to file: " << e.what() << std::endl;
        maxGapFile.close();
        return;
    }
}



void generateMultipleDatasets(int minMachines, int maxMachines, int minTasks, int maxTasks,
                              int minTime, int maxTime, int minGap, int maxGap,
                              const std::string& dataDirectory) {
    // Define directories for each file type
    std::string dataDir = dataDirectory + "/data";
    std::string minGapsDir = dataDirectory + "/mingaps";
    std::string maxGapsDir = dataDirectory + "/maxgaps";

    // Create directories if they don't exist
    fs::create_directories(dataDir);
    fs::create_directories(minGapsDir);
    fs::create_directories(maxGapsDir);

    // Systematically generate all unique combinations of machines and tasks within the specified ranges
    for (int numMachines = minMachines; numMachines <= maxMachines; ++numMachines) {
        for (int numTasks = minTasks; numTasks <= maxTasks; ++numTasks) {
            // Construct full file paths based on the number of tasks and machines
            std::string dataFilename = dataDir + "/data" + std::to_string(numTasks) + "tasks" + std::to_string(numMachines) + "machines.txt";
            std::string minGapsFilename = minGapsDir + "/mingaps" + std::to_string(numTasks) + "tasks" + std::to_string(numMachines) + "machines.txt";
            std::string maxGapsFilename = maxGapsDir + "/maxgaps" + std::to_string(numTasks) + "tasks" + std::to_string(numMachines) + "machines.txt";

            // Generate and save the dataset
            std::cout << "Generating dataset with " << numMachines
                      << " machines and " << numTasks << " tasks." << std::endl;
            generateInstance(numMachines, numTasks, minTime, maxTime, minGap, maxGap, dataFilename);

            // Rename mingaps.txt and maxgaps.txt to unique filenames in their directories
            std::rename("mingaps.txt", minGapsFilename.c_str());
            std::rename("maxgaps.txt", maxGapsFilename.c_str());
        }
    }
}
