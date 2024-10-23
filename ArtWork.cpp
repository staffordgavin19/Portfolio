#include <iostream>
#include <queue>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

queue<int> sharedQueue;

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

    // Join threads
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    return 0;
}

void* producer(void*) {
    while (true) {
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
    while (true) {
        pthread_mutex_lock(&mutex);

        while (sharedQueue.empty()) {
            pthread_cond_wait(&condConsumer, &mutex);
        }

        int number = sharedQueue.front();
        sharedQueue.pop();
        cout << "Consumed: " << number << endl;


        for (int i = 0; i < number; ++i) {
            int x = rand() % 80; // Random X position
            int y = rand() % 25; // Random Y position
            char character = rand() % 26 + 'A'; // Random character
            cout << "\033[" << y << ";" << x << "H" << character << flush; // Print at (x, y)
        }
        cout << endl;

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}