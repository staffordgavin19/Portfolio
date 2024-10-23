# Producer-Consumer-Project
Multithreaded Producer-Consumer system implemented in C++

# Multithreaded Producer-Consumer Simulation
This C++ program simulates a producer-consumer system using POSIX threads, mutexes, and condition variables. The producer generates random numbers, while the consumer processes them and outputs randomized characters to the terminal.

## Features
- Multithreading using POSIX threads
- Synchronization with mutexes and condition variables
- Randomized terminal output using ANSI escape codes

## How to Run
1. Clone the repository: `git clone https://github.com/staffordgavin19/Producer-Consumer-Project.git`
2. Navigate into the project folder: `cd Producer-Consumer-Project`
3. Compile the program: `g++ -pthread main.cpp -o producer_consumer`
4. Run the program: `./producer_consumer`
