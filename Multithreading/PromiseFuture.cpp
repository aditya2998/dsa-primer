#include <iostream>
#include <thread>
#include <future>

using namespace std;
typedef long int ull;

void findOddSum(promise<ull> &&oddSumPromise, ull start, ull end)
{
  ull oddSum = 0;
  for(int i=start;i<=end;i++)
  {
    if(i&1)
      oddSum += i;
  }
  oddSumPromise.set_value(oddSum);
}

int main()
{
  ull start = 0;
  ull end = 1900000000;

  promise<ull> oddSumPromise;
  future<ull> OddSumFuture = oddSumPromise.get_future();

  cout << "Thread created\n";
  thread obj(findOddSum, move(oddSumPromise), start, end);

  cout << "Waiting for the result\n";

  cout << "Odd sum : " << OddSumFuture.get() << "\n";
  cout << "Completed\n";

  obj.join();
}