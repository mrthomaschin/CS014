#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

void generate_random_numbers(vector<int>& values) {
    for (auto& x : values) {
      x = rand();
    }
}

void bubblesort(vector<int>& list)
{
    for(int x = 0; x < list.size(); x++)
    {
        for(int y = x; y < list.size() - 1; y++)
        {
            if(list.at(y) > list.at(y + 1))
                swap(list.at(y), list.at(y + 1));
        }
    }
}

void insertionsort(vector<int>& values) {
    // TODO: Convert the pseudo code shown in class to C++
    int y;
    int key;

    for(int x = 0; x < values.size(); x++)
    {
        key = values.at(x);
        y = x - 1;

        while(y > 0 && values.at(y) > key)
        {  
            values.at(y + 1) = values.at(y);
            y--;
        }

        values.at(y + 1) = key;
    }
}

int main() {
    srand(0);
    vector<int> sizes = {10, 100, 1000, 10000, 100000, 1000000, 10000000};
    for (auto size : sizes) {
      vector<int> values(size);
      generate_random_numbers(values);
      int toFind = rand();
      std::sort(values.begin(), values.end());

      clock_t begin = clock(); // Start the stopwatch

      //std::find(values.begin(), values.end(), toFind);
      //insertionsort(values);
      //std::binary_search(values.begin(), values.end(), toFind);
      bubblesort(values);

      clock_t end = clock(); // Stop the stopwatch

      double elapsed_time = double(end - begin) / CLOCKS_PER_SEC;
      std::cout << "Size " << size << ": Total time " << elapsed_time << " secs" << std::endl;
    }
}