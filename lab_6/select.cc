#include <iostream>
#include <gtest/gtest.h>
#include <stack>
#include <algorithm>
#include <random>

using namespace std;

void generate_random_numbers(vector<int>& values) {
    for (int i = 0; i < values.size(); i++) {
		values[i] = i * 3;
	}
	auto rng = std::default_random_engine {};
	std::shuffle(std::begin(values), std::end(values), rng);
}

/*template <typename T>
int partition(vector<T>& a, int left, int right)
{
	int pivot = a.at(right);
	int p = 1;

	for(int x = 1; x < right; x++)
	{
		if(a.at(x) <= pivot)
		{
			swap (a.at(x), a.at(p));
			p++;
		}
	}

	swap(a.at(p), a.at(pivot));
	return pivot;
}

template <typename T>
void quickSort(vector<T> a, int left, int right, int k)
{
    if(k >= 0 && k < a.size())
    {
        int pivot = partition(a, left, right);

        if(k == pivot)
            return;
        else
            if(k < pivot)
               quickSort(a, left, pivot - 1, k);
            else
                quickSort(a, pivot + 1, right, k);
    }
}*/

template <typename T>
void selectionSort(vector<T>& a, int k)
{
    for(int x = 0; x <= k; x++)
    {
        int minVal = x;

        for(int y = x + 1; y < a.size(); y++)
        {
            if(a.at(y) < a.at(minVal))
            {
                minVal = y;
            }
        }

        swap(a.at(x), a.at(minVal));
    }
}


template <typename T>
T select(vector<T> a, int k) {
    //sort(a, a.begin(), a.end());
    //quickSort(a, 0, a.size() - 1, k);    Nice try
    selectionSort(a, k);

    return a[k];
}

template <typename T>
bool isCorrect(vector<T> a, int k, T kth) {
    int n = 0;
    for (T x : a) {
        if (x < kth)
            n++;
    }
    return n == k;
}

int main(){
    // Generate a list of random numbers
    int size = 100;
    vector<int> values(size);
    generate_random_numbers(values);
    
    // Some test values of k
    vector<int> ks = {0, 5, 20, 30};

    for (int k : ks) {
        int kth_value = select(values, k);
        EXPECT_TRUE(isCorrect(values, k, kth_value));
    }
    cout << "End of program" << endl;
	return 0;
}