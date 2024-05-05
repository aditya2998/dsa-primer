#include <iostream>
#include <thread>
#include <future>

using namespace std;
typedef long int ull;

ull findOddSum(ull start, ull end)
{
  cout << "Inside findOddSum function : thread ID : " << this_thread :: get_id() << "\n";
  ull oddSum = 0;
  for(int i=start;i<=end;i++)
  {
    if(i&1)
      oddSum += i;
  }
  return oddSum;
}

int main()
{
  ull start = 0;
  ull end = 1900000000;

  cout << "Main function thread ID : " << this_thread :: get_id() << "\n";
  
  cout << "Creating task using async\n";
  future <ull> oddSumFutureAsync = async(launch::async, findOddSum, start, end);

  cout << "Waiting for the result\n";

  cout << "OddSum : " << oddSumFutureAsync.get() << "\n";

  cout << "Creating task using deferred\n";
  future <ull> oddSumFutureDeferred = async(launch::deferred, findOddSum, start, end);

  cout << "Waiting for the result\n";
  cout << "OddSum : " << oddSumFutureDeferred.get() << "\n";
  cout << "Completed\n"; 
}
