#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

void print_matrix(int **arr,int n,int m){
        for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++)
                        cout << arr[i][j] << '\t';
                cout << endl;
        }
}

int **creating_array(int n, int m){
        int **arr = new int*[n];
        for(int i = 0; i < n; i++){
                arr[i] = new int[m];
                for(int j = 0; j < m; j++)
                        arr[i][j] = 0;
        }
        return arr;
}

int **ajacency_matrix(int **graph, int n, int m){
        int **arr = creating_array(n, n);
        for(int i = 0; i < m; i++){
                arr[ graph[i][0] - 1 ][ graph[i][1] - 1 ] = 1;
                arr[ graph[i][1] - 1 ][ graph[i][0] - 1 ] = 1;
        }
        return arr;
}

bool checking_arr_null(int *arr, int n){
        for(int i = 0; i < n; i++)
                if(arr[i] == 0)
                        return 0;
        return 1;
}

void by_pass(int **matrix, int n, int m){
        int top;
        cout << "Оберіть вершину : " << endl;
        cin >> top;
        vector<int>status(n);
        vector<int> st;
        st.push_back(top);
        int t = 0;
        do {
                if(status[st.back()-1] != 1){
                        cout << "DFS : " << ++t
                             << "\t\tВершина : " << st.back() << "\tвміст стеку : ";
                        status[st.back()-1] = 1;
                        for(auto el : st)
                                cout << setw(3) << el;
                        cout << endl;
                }
                else{
                        cout << "DFS : -\t\tВершина : -\tвміст стеку : ";
                        for(auto el : st)
                                cout << setw(3) << el;
                        cout << endl;
                }
                for(int i = 0; i < n; i++){
                        if(matrix[st.back()-1][i] == 1 && status[i] == 0){
                                st.push_back(i+1);
                                break;
                        }
                        else if(i == n-1){
                                status[st.back()-1] = 2;
                                st.pop_back();
                        }
                }
        } while(!st.empty());
}

void wide_walk(int **matrix, int n){
        int top;
        cout << "Оберіть вершину : ";
        cin >> top;
        int *status = new int[n];
        for(int i = 0; i < n; i++)
                status[i] = 0;
        vector<int>qu;
        qu.push_back(top);
        status[top-1] = 1;
        int bfs = 0;
        cout << "BFS : " << ++bfs << " \tВершина : " << top << "\tЧерга : " << setw(3) << top << endl;
        while(!qu.empty()){
                for(int i = 0; i < n; i++){
                        if(matrix[qu.front()-1][i] == 1 && status[i] == 0){
                                qu.push_back(i+1);
                                status[i] = 1;
                                cout << "BFS : " << ++bfs << "\t\tВершина : " << i+1 << "\tЧерга : ";
                                for(auto el : qu)
                                        cout << setw(3) << el;
                                cout << endl;
                        }
                }
                qu.erase(qu.begin());
                cout << "BFS : - \tВершина : - \tЧерга : ";
                for(auto el : qu)
                        cout << setw(3) << el;
                cout << endl;
        }
}


int **read_file(int & n, int & m){
        int** graph;
        string path;
        cout << "Enter file adres\n";
        getline(cin, path);
        ifstream fin;
        fin.open(path);
        if(!fin.is_open()){
                cout << "Erorr opening file" << endl;
                assert(fin.is_open());
        }
        char ch;
        bool r = 0;
        while(fin.get(ch) && ch != '\n'){
                if(ch == ' '){
                        r = 1;
                        continue;
                }
                if(!r) n = n * 10 + int(ch) - 48;
                else m = m * 10 + int(ch) - 48;
        }
        graph = creating_array(m, 2);
        r = 0;
        int index = 0;
        while(fin.get(ch) && index != m){
                if(ch == '\n'){
                        index++;
                        r = 0;
                        continue;
                }
                if(ch == ' '){
                        r = 1;
                        continue;
                }
                
                if(!r) graph[index][0] = graph[index][0] * 10 + int(ch) - 48;
                else graph[index][1] = graph[index][1] * 10 + int(ch) - 48;
        }
        fin.close();
        return graph;
}
int main(){
        int n{}, m{};
        int **graph = read_file(n, m);
        cout << "\nОбхід вшир : " << endl;
        wide_walk(ajacency_matrix(graph, n, m), n);
        cout << "\nОбхід вглибину : " << endl;
        by_pass(ajacency_matrix(graph, n, m), n, m);
        return 0;
}
