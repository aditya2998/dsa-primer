// C++ program to demostrate usage of mutex lock and mutex try_lock

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
mutex mutexUsingLock;
int counterUsingLock = 0;

mutex mutexUsingTryLock;
int counterUsingTryLock = 0;

void incrementCounterUsingLock()
{
    for(int i=0;i<100000;i++)
    {
        //current thread lock will wait until other thread releases lock
        mutexUsingLock.lock();
        counterUsingLock++;
        mutexUsingLock.unlock();
    }
}

void incrementCounterUsingTryLock()
{
    for(int i=0;i<100000;i++)
    {
        // mutex try_lock tries to lock the mutex and returns immediately
        // On successful lock acquisition return true, otherwise returns false;
        if(mutexUsingTryLock.try_lock())
        {
            counterUsingTryLock++;
            mutexUsingTryLock.unlock();
        }
    } 
}
int main() {
    thread t1(incrementCounterUsingLock);
    thread t2(incrementCounterUsingLock);
    
    t1.join();
    t2.join();
    
    // value of counterUsingLock should be 200000 always
    cout << "Counter value after using normal lock :" << counterUsingLock << "\n";
    
    thread t3(incrementCounterUsingTryLock);
    thread t4(incrementCounterUsingTryLock);
    t3.join();
    t4.join();
    
    // value of counterUsingTryLock might vary. (For example, 109858, 114799 etc)
    cout << "Counter value after using try_lock :" << counterUsingTryLock << "\n";
    return 0;
}
