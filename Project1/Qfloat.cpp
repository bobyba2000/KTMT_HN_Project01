#include "Qfloat.h"

struct kQPhepChia {
	string thuong = "";
	int soDu = 0;
};

int getIBit(int x, int i)
{
	return (x >> (31 - i)) & 1;
}

void decToBin(int x, int *a)
{
	for (int i = 0; i < 32; i++)
		a[i] = getIBit(x, i);
}

int binToDec(int*a)
{
	int exp = 1;
	int kq = 0;
	for (int i = 0; i < 32; i++)
	{
		kq += exp * a[31 - i];
		exp *= 2;
	}
	return kq;
}

kQPhepChia chia2(string number)
{
	kQPhepChia kq;
	int nho = 0;
	for (int i = 0; i < number.length(); i++)
	{
		int x = nho * 10 + number[i] - '0';
		nho = x % 2;
		kq.thuong += (char)(x / 2 + '0');
	}
	kq.soDu = nho;
	return kq;
}

string nhan2(string number)
{
	string kq = "";
	int nho = 0;
	for (int i = number.length() - 1; i >= 0; i--)
	{
		int x = ((number[i] - '0') * 2 + nho) % 10 + '0';
		nho = ((number[i] - '0') * 2 + nho) / 10;
		kq = (char)x + kq;
	}
	if (nho != 0)
		kq = (char)(nho + '0') + kq;
	return kq;
}

Qfloat::Qfloat()
{
	for (int i = 0; i < _size; i++)
		_data[i] = 0;
}

void Qfloat::ScanQfloat()
{
	//Nhap so Qfloat duoi dang xau
	printf("Nhap so kieu Qfloat: ");
	string number = "";
	getline(cin, number);

	//Xu ly phan nhap
	string phanNguyen = "", phanThapPhan = "";
	int dau = 0, soBitDoi = 0;
	xacDinhPhanNguyenPhanThapPhan(number, phanNguyen, phanThapPhan, dau, soBitDoi);
	
	//Chuan hoa so va luu lai
	chuanHoaThapPhan(phanNguyen, phanThapPhan, dau, soBitDoi);
	chuyenVaLuu(phanNguyen, phanThapPhan, dau, soBitDoi);
}

void Qfloat::PrintQfloat()
{
	cout << "So Qfloat: " << convertToString();
}

void Qfloat::xacDinhPhanNguyenPhanThapPhan(string number, string & phanNguyen, string & phanThapPhan, int & dau, int & soBitDoi)
{
	int i = 0;
	if (number[i] == '-')
	{
		i++;
		dau = 1;
	}

	//Phan Nguyen
	for (; i < number.length(); i++)
		if (number[i] == '.')
			break;
		else if (number[i] == '*')
			break;
		else phanNguyen += number[i];
	if (phanNguyen == "") //Neu khong co thi gan = 0
		phanNguyen = "0";

	//Phan Thap Phan
	if (number[i] == '.')
		for (i = i + 1; i < number.length(); i++)
			if (number[i] == '*')
				break;
			else phanThapPhan += number[i];
	if (phanThapPhan == "")//Neu khong co thi gan = 0
		phanThapPhan = "0";

	//Phan mu
	if (i < number.length())
	{
		for (i = i + 1; i < number.length(); i++)
			if (number[i] == '^')
				break;

		if (number[i + 1] == '-' || number[i + 1] == '+')
		{
			i++;
			for (int j = i + 1; j < number.length(); j++)
				soBitDoi = soBitDoi * 10 + (number[j] - '0');
			if (number[i] == '-')
				soBitDoi = -soBitDoi;
		}
		else for (int j = i + 1; j < number.length(); j++)
			soBitDoi = soBitDoi * 10 + (number[j] - '0');
	}
}

bool isAll0(string number) //Kiem tra xem day so co toan la so 0 hay khong
{
	for (int i = 0; i < number.length(); i++)
		if (number[i] != '0') return false;
	return true;
}

void chuanHoaPhanNguyen(string&phanNguyen)
{
	string kq = "";
	int i = 0;
	for (; i < phanNguyen.length(); i++)
		if (phanNguyen[i] != '0')
			break;
	if (i == phanNguyen.length())
	{
		phanNguyen = "0";
		return;
	}
	for (; i < phanNguyen.length(); i++)
		kq += phanNguyen[i];
	phanNguyen = kq;
}

void Qfloat::chuanHoaThapPhan(string&phanNguyen, string&phanThapPhan, int dau,int&soBitDoi)
{
	//Dua so nhap ve dang 1.f * 2^ x;
	chuanHoaPhanNguyen(phanNguyen);
	int dem = 0;
	if (phanNguyen == "1")
		return;

	if (phanNguyen > "1")
	{
		while (phanNguyen > "1")
		{
			if (chia2(phanNguyen).soDu == 1)
				phanThapPhan = '1' + phanThapPhan;
			kQPhepChia kqChia = chia2(phanThapPhan);
			if (kqChia.soDu == 1)
				phanThapPhan = kqChia.thuong + '5';
			else phanThapPhan = kqChia.thuong;
			if (chia2(phanNguyen).soDu == 1)
				phanThapPhan.erase(0, 1);

			phanNguyen = chia2(phanNguyen).thuong;

			dem++;
			chuanHoaPhanNguyen(phanNguyen);
		}
		soBitDoi += dem;
		return;
	}

	if (phanThapPhan == "0")
		return;

	while (phanNguyen < "1")
	{
		phanNguyen = nhan2(phanNguyen);
		if (nhan2(phanThapPhan).length() > phanThapPhan.length())
		{
			phanNguyen = "1";
			phanThapPhan = nhan2(phanThapPhan).erase(0, 1);
		}
		else phanThapPhan = nhan2(phanThapPhan);

		chuanHoaPhanNguyen(phanNguyen);
		dem--;
	}
	soBitDoi += dem;
	return;
}

bool * Qfloat::DecToBin(Qfloat x)
{
	bool*kq = new bool[128];
	int*dayBit = new int[128];
	x.convertToBit(dayBit);
	for (int i = 0; i < 128; i++)
		kq[i] = (bool)dayBit[i];
	return kq;
}

Qfloat Qfloat::BinToDec(bool * bit)
{
	int*dayBit = new int[128];
	for (int i = 0; i < 128; i++)
		dayBit[i] = (int)bit[i];
	Qfloat kq;
	kq.convertFromBit(dayBit);
	return kq;
}


void Qfloat::chuyenVaLuu(string phanNguyen, string phanThapPhan, int dau, int soBitDoi)
{
	//Khoi tao
	int *bitSo = new int[128];
	for (int i = 0; i < 128; i++)
		bitSo[i] = 0;

	//So 0
	if (phanNguyen == "0" && phanThapPhan == "0")
	{
		convertFromBit(bitSo);
		return;
	}

	//Gan bit dau
	bitSo[0] = dau; 

	//Xu ly so dang khong chuan
	if (soBitDoi <= _MINEXPTREN && soBitDoi >= _MINEXPDUOI)
	{
		phanThapPhan = '1' + phanThapPhan;
		kQPhepChia kqChia = chia2(phanThapPhan);
		if (kqChia.soDu == 1)
			phanThapPhan = kqChia.thuong + '5';
		else phanThapPhan = kqChia.thuong;
		phanThapPhan.erase(0, 1);

		for (soBitDoi = soBitDoi + 1; soBitDoi < _MINEXPTREN; soBitDoi++)
		{
			phanThapPhan = phanThapPhan;
			kQPhepChia kqChia = chia2(phanThapPhan);
			if (kqChia.soDu == 1)
				phanThapPhan = kqChia.thuong + '5';
			else phanThapPhan = kqChia.thuong;
		}
	}

	//Chuyen phan thap phan sang bit
	string dayBitPhanThapPhan = "";
	string kqNhan = "";
	do {
		kqNhan = nhan2(phanThapPhan);
		if (kqNhan.length() > phanThapPhan.length())
		{
			dayBitPhanThapPhan += '1';
			for (int i = 1; i < kqNhan.length(); i++)
				phanThapPhan[i - 1] = kqNhan[i];
		}
		else
		{
			dayBitPhanThapPhan += '0';
			phanThapPhan = kqNhan;
		}
	} while (!isAll0(phanThapPhan) && dayBitPhanThapPhan.length() < _bitSig);

	//Luu bit so mu
	int exp = 1;
	for (int i = 0; i < _bitExp - 1; i++)
		exp *= 2;
	int *bitExp = new int[32];
	decToBin(exp - 1 + soBitDoi, bitExp);
	for (int i = 0; i < _bitExp; i++)
		bitSo[i + 1] = bitExp[i + 32 - _bitExp];

	//Luu bit phan dinh tri
	for (int i = 0; i < dayBitPhanThapPhan.length(); i++)
		bitSo[_bitExp + 1 + i] = dayBitPhanThapPhan[i] - '0';
	
	//Luu lai
	convertFromBit(bitSo);
	delete[]bitSo;
	delete[]bitExp;
}

void Qfloat::convertFromBit(int * dayBit)
{
	int *bit32 = new int[32];
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < 32; j++)
			bit32[j] = dayBit[i * 32 + j];
		_data[i] = binToDec(bit32);
	}
	delete[]bit32;
}

void Qfloat::convertToBit(int*&dayBit)
{
	delete[]dayBit;
	dayBit = new int[128];
	int *bit32 = new int[32];
	for (int i = 0; i < _size; i++)
	{
		decToBin(_data[i], bit32);
		for (int j = 0; j < 32; j++)
			dayBit[i * 32 + j] = bit32[j];
	}
	delete[]bit32;
}

string cong(string soA, string soB)
{
	int nho = 0;
	string kq = "";
	for (int i = soA.length() - 1; i >= 0; i--)
	{
		int x = soA[i] + soB[i] - '0' - '0' + nho;
		nho = x / 10;
		kq = (char)(x % 10 + '0') + kq;
	}
	if (nho > 0)
		kq = (char)(nho % 10 + '0') + kq;
	return kq;
}

string Qfloat::convertToString()
{
	int*bitSo = new int[128];
	convertToBit(bitSo);

	string kq = "";
	if (bitSo[0] == 1) kq += '-';

	//Xu ly so mu
	int*bitExp = new int[32];
	for (int i = 0; i < 32; i++)
		bitExp[i] = 0;
	int exp = 1;
	for (int i = 0; i < _bitExp; i++)
	{
		bitExp[i + 32 - _bitExp] = bitSo[i + 1];
		exp *= 2;
	}
	exp = binToDec(bitExp) - exp / 2 + 1;
	string soMu = "";
	if (exp < 0)
	{
		exp = -exp;
		while (exp > 0)
		{
			soMu = (char)(exp % 10 + '0') + soMu;
			exp /= 10;
		}
		soMu = '-' + soMu;
	}
	else while (exp > 0)
	{
		soMu = (char)(exp % 10 + '0') + soMu;
		exp /= 10;
	}
	delete[]bitExp;
	
	//Phan Thap Phan
	string phanThapPhan = "";
	for (int i = 0; i < _bitSig; i++)
		phanThapPhan += '0';
	string mu2 = "5";
	for (int i = 1; i < _bitSig; i++)
		mu2 += '0';
	for (int i = _bitExp + 1; i < 128; i++)
	{
		if (bitSo[i] == 1)
			phanThapPhan = cong(phanThapPhan, mu2);
		mu2 = chia2(mu2).thuong;
	}
	int dem = 0;
	for (int i = phanThapPhan.length() - 1; i >= 0; i--)
		if (phanThapPhan[i] != '0')
		{
			phanThapPhan = phanThapPhan.erase(i + 1, dem);
			break;
		}
		else dem++;
	if (phanThapPhan.length() == dem)
		phanThapPhan = "0";

	//so 0
	if (soMu == "-16383" && phanThapPhan == "0")
		return "0";

	//Gom lai ta thu duoc day so
	if (soMu != "-16383")
		kq = kq + "1." + phanThapPhan + "*2^" + soMu;
	else
		kq = kq + "0." + phanThapPhan + "*2^" + soMu;
	return kq;
}


Qfloat::~Qfloat()
{
}
