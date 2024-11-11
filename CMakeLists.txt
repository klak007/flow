cmake_minimum_required(VERSION 3.25)
project(Flow)

set(CMAKE_CXX_STANDARD 23)

# Main application executable
add_executable(Flow main.cpp
        generateData.cpp
        schedule.cpp
        simulatedAnnealing.cpp
        bruteForce.cpp
        dataLoader.cpp
        saveResults.cpp
        greedyScheduling.cpp)

# Separate executable for data generation
add_executable(gen_data mainGenerateData.cpp
        generateData.cpp
        dataLoader.cpp)

# Link any necessary libraries here if needed
# target_link_libraries(Flow <library_name>)
# target_link_libraries(gen_data <library_name>)