#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;

const int maxPhilosophers = 5;
vector<mutex> forks(maxPhilosophers);
vector<thread> philosophers;


void philosopher(int id)
{
    cout << "Entered function for id :" << id << "\n";
    int left_fork = id;
    int right_fork = (id+1)%maxPhilosophers;
    
    // To avoid deadlock, the last philosopher picks the forks in reverse direction
    if(id == maxPhilosophers-1)
    {
        swap(left_fork, right_fork);
    }
    
    while(true)
    {
        //Thinking
        cout << "Philosopher " << id << " is thinking.\n";
        this_thread::sleep_for(chrono::milliseconds(2000));
        
        // Hungry, trying to pick up forks
        unique_lock<mutex> left_lock(forks[left_fork]);
        unique_lock<mutex> right_lock(forks[right_fork]);
        
        //Eating
        cout << "Philosopher " << id << " is eating.\n";
        this_thread::sleep_for(chrono::milliseconds(1000));

        //Finished eating, releasing forks
        cout << "Philosopher " << id << " finished eating.\n";
    }
}

int main() {
    for(int i=0;i<maxPhilosophers;i++)
    {
        philosophers.emplace_back(philosopher, i);
    }
    for(auto &thread : philosophers)
    {
        thread.join();
    }
    return 0;
}
