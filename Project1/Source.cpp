#include"Qfloat.h"

int main()
{
	Qfloat number;
	number.ScanQfloat();
	number.PrintQfloat();
	cout << endl;
	
	Qfloat number2;
	number2.ScanQfloat();
	number2.PrintQfloat();
	cout << endl;

	Qfloat a = number * number2;
	a.PrintQfloat();

	int c = 0;
	cin >> c;
	return 0;
}