// C++ program to demonstrate multithreading using 5 different callables.
#include <iostream>
#include <thread>
using namespace std;

void functionPointer(int count)
{
    for(int i=0;i<count;i++)
    {
        cout << "Thread using function pointer as callable\n";
    }
}

class functionObject
{
public:
    void operator()(int count)
    {
        for(int i=0;i<count;i++)
        {
            cout << "Thread using function object as callable\n";
        }
    }
};

class Base {
public:
    //non static member function
    void nonStaticFunction(int count)
    {
        for(int i=0;i<count;i++)
        {
            cout << "Thread using non static member function as callable\n";
        }
    }
    //static member function
    static void staticFunction(int count)
    {
        for(int i=0;i<count;i++)
        {
            cout << "Thread using static member function as callable\n";
        }
    }
};

int main() {
    cout << "Program started\n";
    auto lambdaF = [](int count){
        for(int i=0;i<count;i++)
        {
            cout << "Thread using lamda expression as callable\n";
        }
    };
    Base bObj;
    
    cout << "Creating 5 threads\n";
    thread thread1(functionPointer, 3);
    thread thread2(functionObject(), 3);
    thread thread3(lambdaF, 3);
    thread thread4(&Base :: nonStaticFunction, &bObj, 3);
    thread thread5(&Base :: staticFunction, 3);
    
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    
    cout << "Program ended\n";
    return 0;
}
