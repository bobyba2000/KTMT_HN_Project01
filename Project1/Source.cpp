#include"Qfloat.h"

int main()
{
	Qfloat number;
	number.ScanQfloat();
	number.PrintQfloat();
	
	bool*a = Qfloat::DecToBin(number);
	Qfloat b = Qfloat::BinToDec(a);

	int c = 0;
	cin >> c;
	return 0;
}