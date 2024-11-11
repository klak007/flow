#include "generateData.h"
#include <iostream>

int main() {
    int minMachines = 40;          // Minimum number of machines
    int maxMachines = 50;          // Maximum number of machines
    int minTasks = 2;             // Minimum number of tasks
    int maxTasks = 20;             // Maximum number of tasks
    int minTime = 5;              // Minimum operation time
    int maxTime = 50;             // Maximum operation time
    int minGap = 1;               // Minimum gap between tasks on a machine
    int maxGap = 10;               // Maximum gap between tasks on a machine
    int numDatasets = 8;          // Number of datasets to generate
    std::string dataDirectory = "dataDirectory";  // Base directory for storing files

    // Generate multiple datasets with specified ranges for tasks and machines
    generateMultipleDatasets(minMachines, maxMachines, minTasks, maxTasks, minTime, maxTime, minGap, maxGap, dataDirectory);

    return 0;
}
