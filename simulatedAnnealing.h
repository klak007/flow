#ifndef FLOW_SIMULATEDANNEALING_H
#define FLOW_SIMULATEDANNEALING_H
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Schedule.h"
#include "Task.h"

// Function declaration
Schedule simulatedAnnealing(const std::vector<Task>& tasks, const std::vector<int>& minGaps, const std::vector<int>& maxGaps);

#endif //FLOW_SIMULATEDANNEALING_H
