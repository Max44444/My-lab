#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

void print_matrix(int **arr, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << arr[i][j] << '\t';
        cout << endl;
    }
}

int **creating_array(int n, int m) {
    int **arr = new int *[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[m];
        for (int j = 0; j < m; j++) arr[i][j] = 0;
    }
    return arr;
}

int **ajacency_matrix_org(int **graph, int n, int m) {
    int **arr = creating_array(n, n);
    for (int i = 0; i < m; i++) arr[graph[i][0] - 1][graph[i][1] - 1] = 1;
    return arr;
}

int **ajacency_matrix(int **graph, int n, int m) {
    int **arr = creating_array(n, n);
    for (int i = 0; i < m; i++) {
        arr[graph[i][0] - 1][graph[i][1] - 1] = 1;
        arr[graph[i][1] - 1][graph[i][0] - 1] = 1;
    }
    return arr;
}

int **matrix_mult(int **arr1, int **arr2, int n) {
    int **temp = creating_array(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) temp[i][j] += arr1[i][k] * arr2[k][j];
        }
    }
    return temp;
}

int **degree_matrix(int **matrix, int n, int step) {
    int **arr = creating_array(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) arr[i][j] = matrix[i][j];
    }
    while (step != 1) {
        arr = matrix_mult(arr, matrix, n);
        step--;
    }
    return arr;
}

int **distance_matrix(int **matrix, int n) {
    int **arr = creating_array(n, n), **arr1;
    bool temp = 0;
    int step = 0;
    do {
        temp = 1;
        step++;
        arr1 = degree_matrix(matrix, n, step);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && arr[i][j] == 0 && arr1[i][j] > 0 &&
                    arr1[i][j] <= step) {
                    arr[i][j] = step;
                    temp = 0;
                }
            }
        }
    } while (!temp);
    return arr;
}

int **reachability_matrix(int **matrix, int n) {
    int **arr = creating_array(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) arr[i][j] = matrix[i][j];
        arr[i][i] = 1;
    }
    arr = degree_matrix(arr, n, n - 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] < 1) arr[i][j] = 0;
            if (arr[i][j] >= 1) arr[i][j] = 1;
        }
    }
    return arr;
}

void metric_characteristics(int **matrix, int n) {
    int *arr = new int[n];
    for (int i = 0; i < n; i++) arr[i] = 0;
    for (int i = 0; i < n; i++) {
        arr[i] = matrix[i][0];
        for (int j = 0; j < n; j++)
            if (matrix[i][j] > arr[i]) arr[i] = matrix[i][j];
    }
    int max = arr[0];
    int min = arr[0];
    for (int i = 0; i < n; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    cout << "diametr : " << max << endl;
    cout << "radius : " << min << endl;
    for (int i = 0; i < n; i++)
        if (arr[i] == min) cout << "center : " << i + 1 << endl;
    cout << "enter a top : " << endl;
    int top;
    cin >> top;
    for (int i = 0; i < arr[top - 1] + 1; i++) {
        cout << '\n' << i << " cyrcle :" << endl;
        for (int j = 0; j < n; j++)
            if (matrix[top - 1][j] == i) cout << j + 1 << "  ";
    }
    cout << endl;
}

void typing_matrix(int **graph, int n, int m) {
    int **arr = reachability_matrix(ajacency_matrix(graph, n, m), n);
    int **arr1 = reachability_matrix(ajacency_matrix_org(graph, n, m), n);
    int result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr1[i][j] != 1) {
                if (arr1[j][i] != 1) {
                    if (arr[i][j] != 1) result = 4;
                    if (result < 3) result = 3;
                }
                if (result < 2) result = 2;
            }
            if (result < 1) result = 1;
        }
    }
    switch (result) {
        case 1:
            cout << "strong typing" << endl;
            break;
        case 2:
            cout << "one-sided typing" << endl;
            break;
        case 3:
            cout << "weak typing" << endl;
            break;
        case 4:
            cout << "has no typing" << endl;
            break;
    }
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
    fin.close();
    return graph;
}
int main() {
    int n{}, m{};
    int **graph = read_file(n, m);
    bool answer{};
    while (!answer) {
        system("clear");
        cout << "Enter a graph type :\n"
             << "\t1) Graph;\n"
             << "\t2) Orgraph;\n";
        int g;
        cin >> g;
        system("clear");
        cout << "Enter operation :\n"
             << "\t1) Distance matrix;\n"
             << "\t2) Reachability matrix;\n";
        if (g == 1) cout << "\t3) Metric characteristics;\n";
        if (g == 2) cout << "\t3) Typing of graph;\n";
        cout << "\t4) Exit;\n";
        int temp;
        cin >> temp;
        system("clear");
        switch (temp) {
            case 1:
                cout << "Distance matrix\n\n";
                print_matrix(
                    distance_matrix(g == 1 ? ajacency_matrix(graph, n, m)
                                           : ajacency_matrix_org(graph, n, m),
                                    n),
                    n, n);
                cout << endl;
                break;
            case 2:
                cout << "Reachabilety matrix\n\n";
                print_matrix(reachability_matrix(
                                 g == 1 ? ajacency_matrix(graph, n, m)
                                        : ajacency_matrix_org(graph, n, m),
                                 n),
                             n, n);
                cout << endl;
                break;
            case 3:
                if (g == 1)
                    metric_characteristics(
                        distance_matrix(ajacency_matrix(graph, n, m), n), n);
                if (g == 2) typing_matrix(graph, n, m);
                cout << endl;
                break;
            case 4:
                answer = 1;
                break;
            default:
                cout << "Erorr operation\n";
                break;
        }
        if (answer != 1) {
            cout << "Proceed?\n"
                 << "\t1)Yes;\n"
                 << "\t2)No;\n";
            int r;
            cin >> r;
            r == 1 ? answer = 0 : answer = 1;
        }
    }
    return 0;
}
