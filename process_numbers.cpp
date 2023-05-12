#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>

using namespace std;

int main(){
    vector<int> V;

    ifstream file;
    file.open("rand_numbers.txt");
    copy(istream_iterator<int>(file), istream_iterator<int>(), back_inserter(V));
    sort(begin(V), end(V));
    file.close();

    ofstream evens_file;
    evens_file.open("evens.txt");
    copy_if(begin(V), end(V), ostream_iterator<int>(evens_file, "\n"), [](int i) {return i % 2 == 0;});
    evens_file.close();

    ofstream odds_file;
    odds_file.open("odds.txt");
    copy_if(begin(V), end(V), ostream_iterator<int>(odds_file, " "), [](int i){return i % 2 == 1;});
    odds_file << endl;
    odds_file.close();

    return 0;
};