// Print even and odd numbers in increasing order using 2 threads

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

mutex m;
condition_variable cv;
bool isOdd = true;

void printEven()
{
    for(int i=2;i<=10;i+=2)
    {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [] {return !isOdd;});
        cout << "Even " << i << "\n";
        isOdd = true;
        cv.notify_one();
    }
}

void printOdd()
{
    for(int i=1;i<10;i+=2)
    {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [] {return isOdd;});
        cout << "Odd " << i << "\n";
        isOdd = false;
        cv.notify_one();
    }
}

int main() {
    thread evenThread(printEven);
    thread oddThread(printOdd);
    
    evenThread.join();
    oddThread.join();
    return 0;
}
