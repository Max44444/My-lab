#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#define LINUX

using namespace std;

int **creating_array(int n, int m) {
    int **arr = new int *[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[m];
        for (int j = 0; j < m; j++) arr[i][j] = 0;
    }
    return arr;
}

void ajacency_matrix(int **graph, int **arr, int m) {
    for (int i = 0; i < m; i++) arr[graph[i][0] - 1][graph[i][1] - 1] = 1;
}

void incedence_matrix(int **graph, int **arr, int m) {
    for (int i = 0; i < m; i++) {
        arr[graph[i][0] - 1][i] = -1;
        arr[graph[i][1] - 1][i] = 1;
    }
}

void output_arr(int **arr, int n, int m) {
    cout << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << setw(4) << arr[i][j];
        }
        cout << endl;
    }
}

void output_steps(int **arr1, int *arr2, int n) {
    for (int i = 0; i < n; i++) {
        if (i == 0)
            cout << setw(11) << "Half-west:" << setw(15)
                 << "Half-way out:" << setw(15) << "total degree:" << endl;
        else
            cout << setw(12) << arr1[i][0] << setw(15) << arr1[i][1] << setw(15)
                 << arr2[i] << endl;
    }
}

void half_steps(int **arr, int *step, int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][0] += matrix[j][i];
            arr[i][1] += matrix[i][j];
        }
        step[i] = arr[i][0] + arr[i][1];
    }
}

bool homogeneity(int *arr, int n) {
    for (int i = 0; i < n - 1; i++)
        if (arr[i] != arr[i + 1]) return false;
    return true;
}

void homogeneity_graph(bool result, int *arr) {
    if (result)
        cout << "The graph is homogeneous, has a " << arr[0] << " step" << endl;
    else
        cout << "The graph is not homogeneous" << endl;
}

void hanging_tops(int *arr, int n) {
    bool result = 0;
    int count = 0;
    for (int i = 0; i < n; i++)
        if (arr[i] == 1) {
            result = true;
            count++;
        }
    if (!result)
        cout << "There is no hanging tops" << endl;
    else
        cout << "Henging tops : ";
    for (int i = 0, j = 0; i < n; i++)
        if (arr[i] == 1) {
            j++;
            cout << i + 1;
            j == count ? cout << ";\n" : cout << ", ";
        }
}

void isolated_tops(int *arr, int n) {
    bool result = 0;
    int count = 0;
    for (int i = 0; i < n; i++)
        if (arr[i] == 0) {
            result = true;
            count++;
        }
    if (!result)
        cout << "There is no isolated tops" << endl;
    else
        cout << "Isolated tops : ";
    for (int i = 0, j = 0; i < n; i++)
        if (arr[i] == 0) {
            j++;
            cout << i + 1;
            j == count ? cout << ";\n" : cout << ", ";
        }
    cout << endl;
}

int **read_file(int &n, int &m) {
    int **graph;
    string path;
    cout << "Enter file adres\n";
    getline(cin, path);

    ifstream fin;
    fin.open(path);

    if (!fin.is_open()) {
        cout << "Erorr opening file" << endl;
        assert(fin.is_open());
    }

    else {
        char ch;
        bool r = 0;
        while (fin.get(ch) && ch != '\n') {
            if (ch == ' ') {
                r = 1;
                continue;
            }
            if (!r)
                n = n * 10 + int(ch) - 48;
            else
                m = m * 10 + int(ch) - 48;
        }
        cout << n << m << endl;

        graph = creating_array(m, 2);

        r = 0;
        int index = 0;
        while (fin.get(ch) && index != m) {
            if (ch == '\n') {
                index++;
                r = 0;
                continue;
            }
            if (ch == ' ') {
                r = 1;
                continue;
            }

            if (!r)
                graph[index][0] = graph[index][0] * 10 + int(ch) - 48;

            else
                graph[index][1] = graph[index][1] * 10 + int(ch) - 48;
        }
    }
    fin.close();
    return graph;
}

void delete_arr(int **arr, int n) {
    for (int i = 0; i < n; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

int main() {
    int n = 0, m = 0;

    int **graph = read_file(n, m);
    int **arr2 = creating_array(n, n);
    int **arr1 = creating_array(n, m);
    int **steps = creating_array(n, 2);
    int *total_step = new int[n];

    ajacency_matrix(graph, arr2, m);
    incedence_matrix(graph, arr1, m);
    half_steps(steps, total_step, arr2, n);

    bool ex = 0;
    do {
#ifdef LINUX
        system("clear");
#endif
#ifndef LINUX
        system("cls");
#endif
        int choise, answer{};
        cout << "Choose an action : \n"
             << "\t1) Output the incidence matrix;\n"
             << "\t2) Output the ajency matrix;\n"
             << "\t3) Output the degree of vertices of graph\n"
             << "\t4) Identify all hanging and islated vertices\n"
             << "\t5) Exit;\n";
        cin >> choise;
#ifdef LINUX
        system("clear");
#endif
#ifndef LINUX
        system("cls");
#endif
        switch (choise) {
            case 1:
                cout << "Incidence matrix :\n\n";
                output_arr(arr1, n, m);
                cout << "\n";
                break;
            case 2:
                cout << "Ajency matrix :\n";
                output_arr(arr2, n, n);
                cout << "\n";
                break;
            case 3:
                output_steps(steps, total_step, n);
                cout << "\n";
                homogeneity_graph(homogeneity(total_step, n), total_step);
                cout << "\n";
                break;
            case 4:
                hanging_tops(total_step, n);
                cout << "\n";
                isolated_tops(total_step, n);
                break;
            case 5:
                ex = 1;
                break;
            default:
                cout << "Wrong operation\n";
                break;
        }
        if (choise != 5) {
            cout << "Continue?\n"
                 << "\t1) Yes;\n"
                 << "\t2) No;\n";
            cin >> answer;
            if (answer == 2) ex = 1;
        }
    } while (!ex);
    delete_arr(graph, m);
    delete_arr(arr1, n);
    delete_arr(arr2, n);
    delete_arr(steps, n);
    delete[] total_step;
    return 0;
}
