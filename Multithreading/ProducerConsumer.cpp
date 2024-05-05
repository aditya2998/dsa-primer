/*
Producer consumer problem

There will be MAX_THREADS number of threads created for generating data
and same number of threads created for processing data.

Here data is string. 
Each generator thread will create random string.
It will insert all permutation of string in one data structure.
Each processor thread will process all the strings from that data structure.

Here data structure used is queue.
*/

#include <iostream>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>
#include <cstdlib> 
#include <algorithm>

using namespace std;

#define MAX_THREADS 5
#define STRING_SIZE 5

bool generationDone = false;

class WorkQueue
{
private:
    string name;
    queue <string> internalQueue;
    size_t totalCapacity = 10;
    static WorkQueue *instancePtr;
    static mutex mx;
    condition_variable cvEmpty;
    condition_variable cvFull;

    WorkQueue(){}
public:
    WorkQueue(const WorkQueue &) = delete;
    WorkQueue& operator=(const WorkQueue &) = delete;

    static WorkQueue *getInstance()
    {
        if(instancePtr == NULL){
            //cout << this_thread :: get_id() << " - Acquiring lock for get instance call : ";
            unique_lock<mutex> lock(mx);
            if (instancePtr == NULL)
              instancePtr = new WorkQueue();
            //cout << this_thread :: get_id() << " - Releasing lock for get instance call : ";
        }
        return instancePtr;
    }

    void addToQueue(string str)
    {
        //cout << this_thread :: get_id() << " - Add string : " << str << " queue\n";
        unique_lock<mutex> lock(mx);
        //cout << this_thread :: get_id() << " - Acquiring lock in addToQueue\n";
        //cout << this_thread :: get_id() << " - size ; " << internalQueue.size() << "\n";
        while(internalQueue.size() == totalCapacity)
        {
            //cout << this_thread :: get_id() << " - Queue size full and waiting cvFull\n";
            cvFull.wait(lock);
        }
        internalQueue.push(str);
        cvEmpty.notify_one();
        //cout << this_thread :: get_id() << " - Releasing lock from addToQueue and notifying cvEmpty\n";
    }

    string removeFromQueue()
    {
        //cout << this_thread :: get_id() << " - remove from queue\n";
        //cout << this_thread :: get_id() << " - Acquiring lock in removeToQueue : 63\n";
        unique_lock<mutex> lock(mx);
        while(internalQueue.empty())
        {
            // wait
            //cout << this_thread :: get_id() << " - Queue size empty and waiting cvEmpty \n";
            if (generationDone)
              return "";
            cvEmpty.wait(lock);
        }
        if(internalQueue.empty())
          return "";
        string str = internalQueue.front();
        internalQueue.pop();
        cvFull.notify_one();
        //cout << this_thread :: get_id() << " - Releasing lock from removeToQueue and notifying cvFull\n";
        return str;
    }

    void notifyGenerationDone()
    {
      //cout << "In notifyGenerationDone\n";
      cvEmpty.notify_all();
      //cout << "Notification done\n";
    }
};

WorkQueue* WorkQueue :: instancePtr = NULL;
mutex WorkQueue :: mx;


void createStream(string str)
{
    WorkQueue *obj = WorkQueue :: getInstance();
    string original_str = str;
    
    cout << this_thread :: get_id() << " - Adding all permutation of string : " << original_str << "\n";
    sort(str.begin(), str.end());
    do{
        cout << this_thread :: get_id() << " - next string : " << str << "\n";
        obj->addToQueue(str);
    }while (next_permutation(str.begin(), str.end()));
    
    cout << this_thread :: get_id() << " - Added all permutation of string : " << original_str << "\n";
}
void generateStreams(vector<thread> &threadList)
{
    for(int i = 0;i < MAX_THREADS; i++)
    {
        string str = "";
        for(int j = 0;j < STRING_SIZE; j++)
        {
            str += 'a' + rand()%26;
        }
        //cout << "Creating generator thread : " << i << "\n";
        thread threadObj(createStream, str);
        threadList.push_back(move(threadObj));
        //cout << "Created generator thread : " << i << "\n";
    }
    
}
void processStream()
{
    WorkQueue *obj = WorkQueue :: getInstance();
    while (true)
    {
        string str = obj->removeFromQueue();
        if(str == "")
            break;
        cout << this_thread :: get_id() << " - Removed string :" << str << " from queue\n";
    }
    return;
}
void processStreams(vector<thread> &threadList)
{
    for(int i=0;i<MAX_THREADS;i++)
    {
        //cout << "Creating processor thread : " << i << "\n";
        thread threadObj(processStream);
        threadList.push_back(move(threadObj)); 
        //cout << "Created processor thread : " << i << "\n";
    }
}

void notifyGenerationDone()
{
  WorkQueue *obj = WorkQueue :: getInstance();
  obj->notifyGenerationDone();
}

int main() {
    
    vector<thread> generateThreadList;
    generateStreams(generateThreadList);
    
    vector<thread> processThreadList;
    processStreams(processThreadList);

    for(int i=0;i<MAX_THREADS;i++)
        generateThreadList[i].join();
    
    //cout << "Marking generation done to true\n";
    generationDone = true;
    notifyGenerationDone();

    for(int i=0;i<MAX_THREADS;i++)
        processThreadList[i].join();
    return 0;
}
