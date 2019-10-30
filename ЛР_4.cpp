#include <iostream>
#include <cmath>

using namespace std;

void How_does_the_variable_X(float &x, float y, int i)
{
	x += y / pow(i, 2);
}

void How_does_the_variable_Y(float &y, float x, int i)
{
	y += x / i;
}

int main()
{
	setlocale(LC_ALL, "ukr");
	float x{1};
	float y{1};
	int n{};
	cout << "Введiть номер :" << '\n';
	cin >> n;
	
	int x1{};

	for (int i{ 2 }; i <= n; i++)
	{
		x1 = x;
		How_does_the_variable_X(x, y, i);
		How_does_the_variable_Y(y, x1, i);
	}
	cout << "Результат : " << x << '\n';
	return 0;
}