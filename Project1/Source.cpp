#include"Qfloat.h"

int main()
{
	Qfloat number;
	number.PrintQfloat();
	cout << endl;
	
	Qfloat number2 = "3";
	number2.PrintQfloat();
	cout << endl;

	Qfloat a; 
	a = number / number2;
	a.PrintQfloat();

	int c = 0;
	cin >> c;
	return 0;
}