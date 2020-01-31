#include <ctime>
#include <iostream>

using namespace std;

float func(int arr[], int size) {
    int max = arr[0], min = arr[0], sum = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
        sum += arr[i];
    }
    return (float)(sum - max - min) / (size - 2);
}

int main() {
    setlocale(LC_ALL, "ukr");
    srand(time(NULL));
    int array_size;
    cout << "Введіть кількість оцінок" << endl;
    cin >> array_size;
    int arr[array_size];
    cout << endl;
    for (int i = 0; i < array_size; i++) {
        arr[i] = rand() % 10;
        cout << arr[i] << '\t';
    }
    cout << '\n' << func(arr, array_size) << endl;
    cout << endl;
    return 0;
}
