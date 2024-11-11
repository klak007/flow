#ifndef FLOW_DATALOADER_H
#define FLOW_DATALOADER_H
#include <vector>
#include <string>
#include "Task.h"
#include <fstream>
#include <iostream>
// Function declarations for loading data
bool loadTasks(const std::string& filename, std::vector<Task>& tasks, int& numMachines);
bool loadGaps(const std::string& filename, std::vector<int>& gaps);
#endif //FLOW_DATALOADER_H
