#include <iostream>
#include <queue>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <atomic>

using namespace std;

queue<int> sharedQueue;
atomic<bool> running(true); // Atomic variable to control the running state

// Condition variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condProducer = PTHREAD_COND_INITIALIZER;
pthread_cond_t condConsumer = PTHREAD_COND_INITIALIZER;

void* producer(void*);
void* consumer(void*);

int main() {
    srand(time(0)); // Random Number

    // Producer and consumer threads
    pthread_t producerThread, consumerThread;
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    cout << "Press Enter to stop the program..." << endl;
    cin.get(); // Wait for user input to stop the program

    running = false; // Signal threads to stop

    pthread_cond_signal(&condConsumer); // Wake up consumer if it's waiting
    pthread_cond_signal(&condProducer); // Wake up producer if it's waiting

    // Join threads
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    cout << "Program terminated." << endl;
    return 0;
}

void* producer(void*) {
    while (running) {
        int number = rand() % 10 + 1;

        pthread_mutex_lock(&mutex);

        sharedQueue.push(number);
        cout << "Produced: " << number << endl;

        pthread_cond_signal(&condConsumer);

        pthread_mutex_unlock(&mutex);

        usleep((rand() % 1000 + 500) * 1000); // Sleep for a random interval
    }

    return NULL;
}

void* consumer(void*) {
    while (running || !sharedQueue.empty()) { // Check if there's work left
        pthread_mutex_lock(&mutex);

        while (sharedQueue.empty() && running) {
            pthread_cond_wait(&condConsumer, &mutex);
        }

        if (!sharedQueue.empty()) {
            int number = sharedQueue.front();
            sharedQueue.pop();
            cout << "Consumed: " << number << endl;

            for (int i = 0; i < number; ++i) {
                int x = rand() % 80; // Random X position
                int y = rand() % 25; // Random Y position
                char character = rand() % 26 + 'A'; // Random character
                cout << "\033[" << y << ";" << x << "H" << character << flush; // Print at (x, y)
            }
        }

        cout << endl;

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}