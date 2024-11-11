#include "dataLoader.h"



bool loadTasks(const std::string& filename, std::vector<Task>& tasks, int& numMachines) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << std::endl;
        return false;
    }

    int numTasks;
    file >> numMachines >> numTasks;
    tasks.resize(numTasks, Task{std::vector<int>(numMachines)});

    for (int i = 0; i < numTasks; ++i) {
        for (int j = 0; j < numMachines; ++j) {
            file >> tasks[i].operationTimes[j];
        }
    }
    file.close();
    return true;
}

bool loadGaps(const std::string& filename, std::vector<int>& gaps) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << std::endl;
        return false;
    }

    int gap;
    while (file >> gap) {
        gaps.push_back(gap);
    }
    file.close();
    return true;
}
