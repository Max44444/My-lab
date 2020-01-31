#include "spliting.h"

using namespace std;

vector<string> word_spliting(string str) {
    int counter = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ' ') continue;
        if (str[i + 1] == ' ' || i + 1 == str.size()) counter++;
    }
    vector<string> words(counter + 1);
    int j = str[0] == ' ' ? -1 : 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ' ') {
            if (str[i + 1] != ' ') j++;
            continue;
        }
        words[j] += str[i];
    }
    return words;
}
void delete_even_words(vector<string> words, string& str) {
    str.clear();
    string max = words[0];
    for (int i = 0; i < words.size(); i += 2) {
        if (max.size() < words[i].size()) max = words[i];
        str += words[i] + ' ';
    }
    cout << str << endl;
    cout << "Longer words : " << max << endl;
}
