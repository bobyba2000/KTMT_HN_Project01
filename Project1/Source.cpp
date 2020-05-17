#include"Qfloat.h"

int main()
{
	Qfloat a = "3124235345231334113";
	a.PrintQfloat();
	Qfloat b = "-1.75*2^-4";
	b.PrintQfloat();

	Qfloat c = a + b;
	c.PrintQfloat();
	int n;
	cin >> n;
	return 0;
}