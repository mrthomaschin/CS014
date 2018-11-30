#include <iostream>
#include <fstream>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<pair<string, unsigned int>> wordCount(string filename) {
    ifstream file(filename);
    string line;
    string separators = " \t,.";

    string substring;
    int indexA = 0;
    int indexB = 0;
    int total;
    size_t found;

    pair<string, unsigned int> count;
    vector<pair<string, unsigned int>> word_counts;
    unordered_map<string, int> umap;

    if (file.is_open()) {
        while (getline(file, line)) 
        {
            // TODO
            while(indexA < line.size())
            {
                indexB = line.find_first_of(separators, indexA);    //Get first word
                substring = line.substr(indexA, indexB);

                substring.at(0) = tolower(substring.at(0));

                if(umap.find(substring) == umap.end())  //Not found
                {
                    total = 1;

                    found = line.find(substring, indexB);
                    while(found != string::npos)
                    {
                        total++;
                        found = line.find(substring, found + 1);
                    }

                    umap.insert(make_pair(substring, total));
                    word_counts.push_back(make_pair(substring, total));
                }

                indexA = indexB + 1;

            }
        }
    }
    
    // TODO
    return word_counts;
}

int main(){
    auto counts = wordCount("quote.txt"); //SampleTextFile_10kb.txt
    for (auto i = counts.begin(); i != counts.end(); i++) {
        cout << i->first << "\t" << i->second << endl;
    }
    cout << "End of program" << endl;
	return 0;
}