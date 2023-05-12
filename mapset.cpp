
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>

using namespace std;

string to_lower_word(string word){
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    return word;
}

int main(){
    set<string> stop_words;
    ifstream other_file;
    other_file.open("stopwords.txt"); 
    transform(istream_iterator<string>(other_file), istream_iterator<string>(), inserter(stop_words, stop_words.end()), [](string word){return to_lower_word(word);});
    other_file.close();
    
    map<string, int> M;
    ifstream file;
    file.open("sample_doc.txt");
    for_each(istream_iterator<string>(file), istream_iterator<string>(), [& M, stop_words](string word){
        string lower = to_lower_word(word);
        if (!stop_words.count(lower)){
            ++M[lower];
        }});
    file.close();

    ofstream out("frequency.txt");
    for (const auto &word: M){
        out << word.first << " " << word.second << endl;
    }
    out.close();

    return 0;
};