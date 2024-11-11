#ifndef FLOW_SAVERESULTS_H
#define FLOW_SAVERESULTS_H

#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <filesystem>
#include <iostream>

#include "Task.h"
#include "Schedule.h"
// Function to save results to a file in the results directory
void saveResults(const std::string& algorithm, int numTasks, int numMachines,
                 const Schedule& optimalSchedule, double duration, const std::vector<Task>& tasks);

#endif //FLOW_SAVERESULTS_H
