#ifndef GEN_DATA_GENERATEDATA_H
#define GEN_DATA_GENERATEDATA_H

#include <string>
#include "task.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <filesystem>
#include <cstdio>

void generateInstance(int numMachines, int numTasks, int minTime, int maxTime,
                      int minGap, int maxGap, const std::string& filename);

void generateMultipleDatasets(int minMachines, int maxMachines, int minTasks, int maxTasks,
                              int minTime, int maxTime, int minGap, int maxGap,
                              const std::string& dataDirectory);
#endif //GEN_DATA_GENERATEDATA_H
