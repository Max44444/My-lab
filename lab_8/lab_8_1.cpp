#include <iostream>
#include <ctime>

using namespace std;

int** create_matrix(const int size) 
{
        int** arr = new int*[size];
        for(int i = 0; i < size; i++)
        {
                arr[i] = new int[size];
        }
        return arr;
}

void random(int **arr, int size)
{
        for(int i = 0; i < size; i++)
        {
                for(int j = 0; j < size; j++)
                {
                        arr[i][j] = rand() % 100;
                }
        }
}

void array_output(int **arr, int size)
{
        cout << "====================================" << endl;
        for(int i = 0; i < size; i++)
        {
                for(int j = 0; j < size; j++)
                {
                        cout << arr[i][j] << '\t';
                }
                cout << "\n\n";
        }
        cout << "====================================" << endl;
}

void sort_diagonals(int **arr, int n)
{
        for(int i = 0; i < n; i++)
        {
                int min = arr[i][i];
                int index = i;
                for(int j = i; j < n; j++)
                {
                        if(arr[j][j] < min)
                        {
                                min = arr[j][j];
                                index = j;
                        }
                }
                swap(arr[i][i], arr[index][index]);
        }
}

void swap_diagonals(int** arr_1, int** arr_2, int size)
{
        for(int i = 0; i < size; i++)
        {
                swap(arr_1[i][i], arr_2[i][i]);
        }
}

int main()
{
        setlocale(LC_ALL, "ukr");
        srand(time(NULL));
        int n;
        cin >> n;
        int **arr_1 = create_matrix(n);
        int **arr_2 = create_matrix(n);

        random(arr_1, n);
        random(arr_2, n);

        array_output(arr_1, n);
        array_output(arr_2, n);

        sort_diagonals(arr_1, n);
        sort_diagonals(arr_2, n);
        
        swap_diagonals(arr_1, arr_2, n); 

        array_output(arr_1, n);
        array_output(arr_2, n);
        return 0;
}
