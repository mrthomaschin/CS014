#include <iostream>
#include <gtest/gtest.h>
#include <algorithm>
#include <random>

using namespace std;

void generate_random_numbers(vector<int>& values) {
    for (int i = 0; i < values.size(); i++) {
		values[i] = i;
	}
	auto rng = std::default_random_engine {};
	std::shuffle(std::begin(values), std::end(values), rng);
}

/// Traverse the array k times and select the minimum each time
template <typename T>
T select1(vector<T> a, int k) {
    int minIndex;

	for(int x = 0; x <= k; x++)
	{
		minIndex = x;

		for(int y = minIndex; y < a.size(); y++)
		{
			if(a.at(y) <= a.at(minIndex))
			{
				minIndex = y;
			}
		}

		swap(a.at(x), a.at(minIndex));
    }

    return a.at(k);
}

/// Sort the array and return the item at position k
template <typename T>
T select2(vector<T> a, int k) {

    sort(a.begin(), a.end());
    
    return a.at(k);
}

/// Select the kth element using a heap
template <typename T>
T select3(vector<T> a, int k) 
{
    make_heap(a.begin(), a.end(), greater <int>());

    for(int x = 0; x < k; x++)
    {
        pop_heap(a.begin(), a.end(), greater <int>());
        a.pop_back();
    }

    return a.front();
}

template <typename T>
int partition(vector<T>& a, int left, int right)
{
	int pivot = right - 1;
	int p = left;

	for(int x = left; x < right; x++)
	{
		if(a.at(x) < a.at(pivot))
		{
			swap (a.at(x), a.at(p));
			p++;
		}
	}

	swap(a.at(p), a.at(pivot));
	return p;
}


/// Use a quick-sort-like algorithm to select the kth element
template <typename T>
T select4(vector<T>& a, int k) {

    int left = 0;
    int right = a.size();

    while(left < right)
    {
        int index = partition(a, left, right);

        if(index > k)
            right = index;
        else
            if(index < k)
                left = index;
            else
                return a.at(k);
    }
            
    return a.at(k);
}

template <typename T>
bool isCorrect(vector<T> a, int k, T kth) {
    int n = 0;
    for (T x : a) {
        if (x < kth)
            n++;
    }
    EXPECT_EQ(k, n);
    return n == k;
}

int main(){
    // Generate a list of random numbers
    int size = 100;
    vector<int> values(size);
    // Some test values of k
    vector<int> ks = {0, 5, 20, 30};
    
    generate_random_numbers(values);

    for (int k : ks) {
        vector<int> temp = values;
        int kth_value = select1(temp, k);
        EXPECT_TRUE(isCorrect(values, k, kth_value));
        
        temp = values;
        kth_value = select2(temp, k);
        EXPECT_TRUE(isCorrect(values, k, kth_value));
        
        temp = values;
        kth_value = select3(temp, k);
        EXPECT_TRUE(isCorrect(values, k, kth_value));
        
        temp = values;
        kth_value = select4(temp, k);
        EXPECT_TRUE(isCorrect(values, k, kth_value));
    }
    
    // Measure the running times
	cout << right
	     << setw(16)  << "k"
         << setw(16)  << "Select1"
         << setw(16)  << "Select2"
         << setw(16)  << "Select3"
         << setw(16)  << "Select4" << endl;

    size = 100000;
    values.resize(size);
    ks.clear(); ks.push_back(1); ks.push_back(10); ks.push_back(100);
    ks.push_back(1000); ks.push_back(5000);
    generate_random_numbers(values);
    for (int k : ks) {
        cout << setw(16) << k;
        
        vector<int> temp = values;
        clock_t begin = clock(); // Start the stopwatch
        int kth_value = select1(temp, k);
        clock_t end = clock(); // Stop the stopwatch
        double elapsed_time = double(end - begin) / CLOCKS_PER_SEC;
        cout << setw(16) << elapsed_time;

        temp = values;
        begin = clock(); // Start the stopwatch
        kth_value = select2(temp, k);
        end = clock(); // Stop the stopwatch
        elapsed_time = double(end - begin) / CLOCKS_PER_SEC;
        cout << setw(16) << elapsed_time;

        temp = values;
        begin = clock(); // Start the stopwatch
        kth_value = select3(temp, k);
        end = clock(); // Stop the stopwatch
        elapsed_time = double(end - begin) / CLOCKS_PER_SEC;
        cout << setw(16) << elapsed_time;

        temp = values;
        begin = clock(); // Start the stopwatch
        kth_value = select4(temp, k);
        end = clock(); // Stop the stopwatch
        elapsed_time = double(end - begin) / CLOCKS_PER_SEC;
        cout << setw(16) << elapsed_time;
        
        cout << endl;
    }
    
    cout << "-----------------" << endl;
    
    // Measure the running times
	cout << right
	     << setw(16)  << "n"
         << setw(16)  << "Select1"
         << setw(16)  << "Select2"
         << setw(16)  << "Select3"
         << setw(16)  << "Select4" << endl;

    vector<int> sizes = {100, 1000, 10000, 100000, 1000000};
    for (int size : sizes) {
        values.resize(size);
        generate_random_numbers(values);
        cout << setw(16) << size;

        int k = 1;        
        vector<int> temp = values;
        clock_t begin = clock(); // Start the stopwatch
        int kth_value = select1(temp, k);
        clock_t end = clock(); // Stop the stopwatch
        double elapsed_time = double(end - begin) / CLOCKS_PER_SEC;
        cout << setw(16) << elapsed_time;

        temp = values;
        begin = clock(); // Start the stopwatch
        kth_value = select2(temp, k);
        end = clock(); // Stop the stopwatch
        elapsed_time = double(end - begin) / CLOCKS_PER_SEC;
        cout << setw(16) << elapsed_time;

        temp = values;
        begin = clock(); // Start the stopwatch
        kth_value = select3(temp, k);
        end = clock(); // Stop the stopwatch
        elapsed_time = double(end - begin) / CLOCKS_PER_SEC;
        cout << setw(16) << elapsed_time;

        temp = values;
        begin = clock(); // Start the stopwatch
        kth_value = select4(temp, k);
        end = clock(); // Stop the stopwatch
        elapsed_time = double(end - begin) / CLOCKS_PER_SEC;
        cout << setw(16) << elapsed_time;
        
        cout << endl;
    }
    cout << "End of program" << endl;
	return 0;
}
