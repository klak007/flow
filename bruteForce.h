#ifndef FLOW_BRUTEFORCE_H
#define FLOW_BRUTEFORCE_H

#include <vector>
#include "Task.h"
#include "Schedule.h"
#include <iostream>
#include <cmath>
// Function declaration for brute-force scheduling
Schedule bruteForce(const std::vector<Task>& tasks, const std::vector<int>& minGaps, const std::vector<int>& maxGaps);


#endif //FLOW_BRUTEFORCE_H
