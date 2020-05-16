#include"Qfloat.h"

int main()
{
	Qfloat a = "4.2";
	a.PrintQfloat();
	Qfloat b = "4.1";
	b.PrintQfloat();

	Qfloat c = a + b;
	c.PrintQfloat();
	int n;
	cin >> n;
	return 0;
}