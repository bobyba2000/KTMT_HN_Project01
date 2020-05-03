#pragma once
#include<string>
#include<iostream>
using namespace std;
const int _size = 4;
const int _bitExp = 15;
const int _bitSig = 112;
const int _MINEXPDUOI = -16495;
const int _MINEXPTREN = -16383;

class Qfloat
{
private:
	int _data[4];

public:
	Qfloat();

	void ScanQfloat();
	void PrintQfloat();

	void xacDinhPhanNguyenPhanThapPhan(string number, string&phanNguyen, string&phanThapPhan, int&dau, int&soBitDoi);

	void chuyenVaLuu(string phanNguyen, string phanThapPhan, int dau, int soBitDoi);
	void chuanHoaThapPhan(string&phanNguyen, string&phanThapPhan, int dau, int&soBitDoi);

	void convertFromBit(int*dayBit);
	void convertToBit(int*&dayBit);
	string convertToString();

	static bool*DecToBin(Qfloat x);
	static Qfloat BinToDec(bool*bit);

	~Qfloat();
};

