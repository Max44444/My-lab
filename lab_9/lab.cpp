#include "spliting.h"

using namespace std;

int main(){
        setlocale(LC_ALL, ".866");
        cout << "Введіть строку :\n";
        string str;
        getline(cin, str);
        delete_even_words(word_spliting(str), str);
        return 0;
}
