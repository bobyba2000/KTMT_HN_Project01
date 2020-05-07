#include"Qfloat.h"

int main()
{
	Qfloat number ="2*2^3";
	number.PrintQfloat();
	cout << endl;
	
	Qfloat number2 = "2*2^5";
	number2.PrintQfloat();
	cout << endl;

	Qfloat a; 
	a = number / number2;
	a.PrintQfloat();

	int c = 0;
	cin >> c;
	return 0;
}