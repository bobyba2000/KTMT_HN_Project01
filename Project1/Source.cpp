#include"Qfloat.h"

int main()
{
	Qfloat a = "1.3125*2^-4";
	a.PrintQfloat();
	Qfloat b = "-1.75*2^-4";
	b.PrintQfloat();

	Qfloat c = a * b;
	c.PrintQfloat();
	int n;
	cin >> n;
	return 0;
}