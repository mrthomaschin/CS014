//Thomas Chin: tchin006, 861290572
//Raeven Ruiz: rruiz014, 861280793

#include <iostream>
#include <gtest/gtest.h>
#include <algorithm>
#include <random>

using namespace std;

void generate_random_characters(vector<char>& values) {
    for (int i = 0; i < 26; i++) {
		values[i] = i + 'A';
		values[i+26] = i + 'a';
	}
	auto rng = std::default_random_engine {};
	std::shuffle(std::begin(values), std::end(values), rng);
}

struct CaseSensitiveLessThan {
    // Return ture if c1 is less than c2 (case sensitive comparison)
    bool operator()(char c1, char c2) 
    {
        if(c1 < c2)
            return true;

        return false;
    }
};

struct CaseInsensitiveLessThan {
    // Return ture if c1 is less than c2 (case insensitive comparison)
    bool operator()(char c1, char c2) 
    {
        if(c1 == c2 - 32)
            return true;

        if(c1 >= 97)
            c1 -= 32;

        if(c2 >= 97)
            c2 -= 32;
        
        if(c1 < c2)
            return true;

        return false;
    }
};

template <typename T, typename Comparator>
vector<int> indexedSort(const vector<T>& a, Comparator lessthan) 
{
    vector<int> indexes;

    for(int w = 0; w < a.size(); w++)
    {
        indexes.push_back(w);
    }

    for(int x = 0; x < a.size(); x++)
    {
        for(int y = 0; y < a.size() - 1; y++)
        {
            if(lessthan(a.at(indexes.at(y + 1)), a.at(indexes.at(y))))
                swap(indexes.at(y), indexes.at(y + 1));
        }
    }

    return indexes;
}

void testSorting() {
    // Test case insensitive comparator
    CaseInsensitiveLessThan cislt;
    EXPECT_TRUE(cislt('a', 'B'));
    EXPECT_FALSE(cislt('B', 'a'));
    EXPECT_TRUE(cislt('a', 'b'));
    EXPECT_FALSE(cislt('b', 'a'));
    EXPECT_TRUE(cislt('a', 'Z'));
    EXPECT_FALSE(cislt('Z', 'a'));
    EXPECT_TRUE(cislt('A', 'a'));
    EXPECT_FALSE(cislt('a', 'a'));

    // Test case sensitive comparator
    CaseSensitiveLessThan cslt;
    EXPECT_TRUE(cslt('B', 'a'));
    EXPECT_FALSE(cslt('a', 'B'));
    EXPECT_TRUE(cslt('A', 'B'));
    EXPECT_FALSE(cslt('B', 'A'));
    EXPECT_TRUE(cslt('Z', 'a'));
    EXPECT_FALSE(cslt('a', 'Z'));
    EXPECT_TRUE(cslt('A', 'a'));
    EXPECT_FALSE(cslt('a', 'A'));
    EXPECT_FALSE(cslt('a', 'a'));

    // Generate a list of random numbers
    int size = 26 * 2; //26
    vector<char> values(size);
    generate_random_characters(values);
    
    // Test case sensitive
    vector<char> temp = values;
    vector<int> indexes = indexedSort(values, cslt);
    // Test sorted
    for (int i = 1; i < indexes.size(); i++) {
        EXPECT_TRUE(cslt(values[indexes[i-1]], values[indexes[i]]));
    }
    // Test the array did not change
    for (int i = 0; i < indexes.size(); i++) {
        EXPECT_EQ(values[i], temp[i]);
    }
    
    // Test case insensitive
    temp = values;
    indexes = indexedSort(values, cislt);
    // Test sorted
    for (int i = 1; i < indexes.size(); i++) {
        EXPECT_TRUE(cislt(values[indexes[i-1]], values[indexes[i]]));
    }
    // Test the array did not change
    for (int i = 0; i < indexes.size(); i++) {
        EXPECT_EQ(values[i], temp[i]);
    }
}

int main(){
    testSorting();
    cout << "End of program" << endl;
	return 0;
}