#ifndef FLOW_GREEDYSCHEDULING_H
#define FLOW_GREEDYSCHEDULING_H

#include <vector>
#include "Task.h"
#include "Schedule.h"

Schedule greedyScheduling(const std::vector<Task>& tasks, const std::vector<int>& minGaps, const std::vector<int>& maxGaps);

#endif //FLOW_GREEDYSCHEDULING_H
