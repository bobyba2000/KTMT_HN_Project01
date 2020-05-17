#include "Qfloat.h"

struct kQPhepChia {
	string thuong = "";
	int soDu = 0;
};

bool soSanh(string&soA, string&soB)
{
	int max = soA.length() > soB.length() ? soA.length() : soB.length();
	for (int i = soA.length(); i < max; i++)
		soA = '0' + soA;
	for (int i = soB.length(); i < max; i++)
		soB = '0' + soB;
	return !(soA < soB);
}

//Lay bit thu I
int getIBit(int x, int i) 
{
	return (x >> (31 - i)) & 1;
}

//chuyen so x thanh day bit a
void decToBin(int x, int *a)
{
	for (int i = 0; i < 32; i++)
		a[i] = getIBit(x, i);
}

//chuyen day bit a va tra ve so
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

//thuc hien phep chia so number cho 2
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

//thuc hien phep nhan so number cho 2
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

//khoi tao
Qfloat::Qfloat()
{
	for (int i = 0; i < _size; i++)
		_data[i] = 0;
}

Qfloat::Qfloat(const char * a)
{
	*this = a;
}

Qfloat::Qfloat(string a)
{
	*this = a;
}

//yeu cau nhap so vao
void Qfloat::ScanQfloat()
{
	//Nhap so Qfloat duoi dang xau
	printf("Nhap so kieu Qfloat: ");
	string number = "";
	getline(cin, number);
	convertFromString(number);
}

//In so ra
void Qfloat::PrintQfloat()
{
	cout << "So Qfloat: " << convertToStringDec() << " hoac " << convertToStringDecClear() << endl;
}

//Xac dinh phan nguyen, phan thap phan, dau cua so number
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

//Xoa het cac so 0 o truoc phan nguyen
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

//Dua so nhap ve dang 1.f * 2^ x;
void Qfloat::chuanHoaThapPhan(string&phanNguyen, string&phanThapPhan, int dau, int&soBitDoi)
{
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

//Chuyen so kieu Qfloat ve day cac bit
bool * Qfloat::DecToBin(Qfloat x)
{
	bool*kq = new bool[128];
	int*dayBit = new int[128];
	x.convertToBit(dayBit);
	for (int i = 0; i < 128; i++)
		kq[i] = (bool)dayBit[i];
	return kq;
}

//Chuyen day cac bit ve kieu Qfloat
Qfloat Qfloat::BinToDec(bool * bit)
{
	int*dayBit = new int[128];
	for (int i = 0; i < 128; i++)
		dayBit[i] = (int)bit[i];
	Qfloat kq;
	kq.convertFromBit(dayBit);
	return kq;
}

Qfloat Qfloat::Infinity()
{
	bool*bit = new bool[128];
	for (int i = 0; i < 128; i++)
		bit[i] = false;
	for (int i = 0; i < _bitExp; i++)
		bit[i + 1] = true;
	return BinToDec(bit);
}

bool Qfloat::isInfinity(Qfloat b)
{
	Qfloat a = Infinity();
	for (int i = 0; i < _size; i++)
		if (b._data[i] != a._data[i])
			return false;
	return true;
}

//chuyen cac so sang dang bit va luu lai vo bien _data
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

		for (soBitDoi = soBitDoi + 1; soBitDoi <= _MINEXPTREN; soBitDoi++)
		{
			phanThapPhan = phanThapPhan;
			kQPhepChia kqChia = chia2(phanThapPhan);
			if (kqChia.soDu == 1)
				phanThapPhan = kqChia.thuong + '5';
			else phanThapPhan = kqChia.thuong;
		}
		soBitDoi = _MINEXPTREN;
	}

	//so Infinity
	if (soBitDoi >= -_MINEXPTREN)
	{
		*this = Infinity();
		return;
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

//thuc hien phep cong trong he
string cong(string soA, string soB, int he)
{
	int nho = 0;
	string kq = "";
	for (int i = soA.length() - 1; i >= 0; i--)
	{
		int x = soA[i] + soB[i] - '0' - '0' + nho;
		nho = x / he;
		kq = (char)(x % he + '0') + kq;
	}
	if (nho > 0)
		kq = (char)(nho % he + '0') + kq;
	return kq;
}

string tru(string soA, string soB, int he)
{	int nho = 0;
	string kq = "";
	for (int i = soA.length() - 1; i >= 0; i--)
	{
		int x = soA[i] - soB[i] + nho + 2;
		nho = (x / he) - 1;
		kq = (char)(x % he + '0') + kq;
	}
	if (nho != 0)
		kq = '1' + kq;
	return kq;
}

string Qfloat::laySoMu()
{
	int*bitSo = new int[128];
	convertToBit(bitSo);

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
	if (soMu == "") soMu = "0";
	delete[]bitExp;
	delete[]bitSo;
	return soMu;
}

//Lay phan thap phan
string Qfloat::layPhanThapPhan()
{
	int*bitSo = new int[128];
	convertToBit(bitSo);

	string phanThapPhan = "";
	for (int i = 0; i < _bitSig; i++)
		phanThapPhan += '0';
	string mu2 = "5";
	for (int i = 1; i < _bitSig; i++)
		mu2 += '0';
	for (int i = _bitExp + 1; i < 128; i++)
	{
		if (bitSo[i] == 1)
			phanThapPhan = cong(phanThapPhan, mu2, 10);
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

	delete[]bitSo;
	return phanThapPhan;
}

//chuyen so Qfloat sang chuoi so kieu thap phan
string Qfloat::convertToStringDec()
{
	int*bitSo = new int[128];
	convertToBit(bitSo);
	

	string kq = "";
	if (bitSo[0] == 1) kq += '-';

	//Xu ly so mu
	string soMu = laySoMu();
	
	//Phan Thap Phan
	string phanThapPhan = layPhanThapPhan();

	//so 0
	if (soMu == "-16383" && phanThapPhan == "0")
		return "0";

	//so Infinity
	if (isInfinity(*this))
		return "Infinity";

	//Gom lai ta thu duoc day so
	if (soMu != "-16383")
		kq = kq + "1." + phanThapPhan + "*2^" + soMu;
	else
		kq = kq + "0." + phanThapPhan + "*2^" + "-16382";
	return kq;
}

string Qfloat::convertToStringDecClear()
{
	int*dayBitThis = NULL;
	convertToBit(dayBitThis);

	//xac dinh day cac bit cua cac so
	string dayBitExpThis = "", dayBitExpCong = "", dayBitExpBias = "";
	for (int i = 0; i < _bitExp; i++)
	{
		dayBitExpThis += (char)(dayBitThis[i + 1] + '0');
		dayBitExpCong += "0";
		dayBitExpBias += "1";
	}
	dayBitExpCong[_bitExp - 1] = '1';
	dayBitExpBias[0] = '0';
	string phanSigThis = layPhanThapPhan();

	string phanNguyenThis = "1", phanNguyenOther = "1";
	if (isAll0(dayBitExpThis))
		phanNguyenThis = "0";
	while (dayBitExpThis != dayBitExpBias)
	{
		if (dayBitExpThis > dayBitExpBias)
		{
			string kqNhan = nhan2(phanSigThis);
			phanNguyenThis = nhan2(phanNguyenThis);
			if (kqNhan.length() > phanSigThis.length())
			{
				string soA = "1";
				soSanh(soA, phanNguyenThis);
				phanNguyenThis = cong(soA, phanNguyenThis, 10);
				phanSigThis = kqNhan.erase(0, 1);
			}
			else phanSigThis = kqNhan;
			dayBitExpThis = tru(dayBitExpThis, dayBitExpCong, 2);
		}
		if (dayBitExpThis < dayBitExpBias)
		{
			bool check = false;
			if (chia2(phanNguyenThis).soDu == 1)
			{
				phanSigThis = '1' + phanSigThis;
				check = true;
			}
			phanNguyenThis = chia2(phanNguyenThis).thuong;
			kQPhepChia kqChia = chia2(phanSigThis);
			if (kqChia.soDu == 1)
				phanSigThis = kqChia.thuong + '5';
			else phanSigThis = kqChia.thuong;
			if (check)
				phanSigThis = phanSigThis.erase(0, 1);
			dayBitExpThis = cong(dayBitExpThis, dayBitExpCong, 2);
		}
	}
	if (dayBitThis[0] == 0)
		return phanNguyenThis + '.' + phanSigThis;
	return "-" + phanNguyenThis + '.' + phanSigThis;
}

Qfloat Qfloat::convertFromString(string number)
{
	string phanNguyen = "", phanThapPhan = "";
	int dau = 0, soBitDoi = 0;
	xacDinhPhanNguyenPhanThapPhan(number, phanNguyen, phanThapPhan, dau, soBitDoi);

	//Chuan hoa so va luu lai
	chuanHoaThapPhan(phanNguyen, phanThapPhan, dau, soBitDoi);
	chuyenVaLuu(phanNguyen, phanThapPhan, dau, soBitDoi);
	return*this;
}

void shiftRightString(string&a,string x)
{
	a.erase(a.length() - 1, 1);
	a.insert(0, x);
}

Qfloat Qfloat::soDoi()
{
	int*dayBit = NULL;
	convertToBit(dayBit);
	bool*bitSo = new bool[128];
	for (int i = 0; i < 128; i++)
		bitSo[i] = dayBit[i];
	bitSo[0] = !bitSo[0];
	Qfloat kq = BinToDec(bitSo);
	delete[]bitSo;
	return kq;
}

Qfloat Qfloat::operator+(Qfloat other)
{
	int*dayBitThis = NULL;
	convertToBit(dayBitThis);
	int*dayBitOther = NULL;
	other.convertToBit(dayBitOther);

	//neu hai so khac dau thi ta lay hai so tru nhau
	if (dayBitThis[0] != dayBitOther[0])
	{
		return *this - other.soDoi();
	}

	//neu 1 trong 2 so bang 0 thi tra ve so con lai
	if (this->convertToStringDec() == "0") return other;
	if (other.convertToStringDec() == "0") return *this;

	//neu 1 trong 2 so la infinity thi tra ve infinity
	if (isInfinity(*this) || isInfinity(other))
		return Infinity();

	//Xac dinh day bit cua cac so
	string dayBitExpThis = "", dayBitExpOther = "", dayBitExpCong = "";
	for (int i = 0; i < _bitExp; i++)
	{
		dayBitExpThis += (char)(dayBitThis[i + 1] + '0');
		dayBitExpOther += (char)(dayBitOther[i + 1] + '0');
		dayBitExpCong += "0";
	}
	dayBitExpCong[_bitExp - 1] = '1';
	string dayBitSigThis = "", dayBitSigOther = "";
	for (int i = 0; i < _bitSig; i++)
	{
		dayBitSigThis += (char)(dayBitThis[i + 1 + _bitExp] + '0');
		dayBitSigOther += (char)(dayBitOther[i + 1 + _bitExp] + '0');
	}

	//dua ve cung so mu
	string phanNguyenThis = "1", phanNguyenOther = "1";
	if (isAll0(dayBitExpThis))
	{
		phanNguyenThis = "0";
		dayBitExpThis = cong(dayBitExpThis, dayBitExpCong, 2);
	}
	if (isAll0(dayBitExpOther))
	{
		dayBitExpOther = cong(dayBitExpCong, dayBitExpOther, 2);
		phanNguyenOther = "0";
	}

	while (dayBitExpOther != dayBitExpThis)
	{
		if (dayBitExpOther < dayBitExpThis)
		{
			dayBitExpOther = cong(dayBitExpOther, dayBitExpCong, 2);
			shiftRightString(dayBitSigOther, phanNguyenOther);
			phanNguyenOther = "0";
			continue;
		}

		if (dayBitExpOther > dayBitExpThis)
		{
			dayBitExpThis = cong(dayBitExpThis, dayBitExpCong, 2);
			shiftRightString(dayBitSigThis, phanNguyenThis);
			phanNguyenThis = "0";
		}
	}

	//neu cach biet 2 so qua lon thi ta tra ve so lon hon
	if (isAll0(dayBitSigOther) && phanNguyenOther == "0")
		return *this;
	if (isAll0(dayBitSigThis) && phanNguyenThis == "0")
		return other;

	//thuc hien phep cong
	phanNguyenOther = "0" + phanNguyenOther;
	phanNguyenThis = "0" + phanNguyenThis;
	string kqSig = cong(dayBitSigThis, dayBitSigOther, 2);
	string kqNguyen = cong(phanNguyenOther, phanNguyenThis, 2);
	if (kqSig.length() > _bitSig)
	{
		kqNguyen = cong(kqNguyen, "01", 2);
		kqSig.erase(0, 1);
	}

	while (kqNguyen > "01")
	{
		if(kqNguyen[1]=='0')
			shiftRightString(kqSig, string("0"));
		else shiftRightString(kqSig, string("1"));
		dayBitExpThis = cong(dayBitExpCong, dayBitExpThis, 2);
		kqNguyen = tru(kqNguyen, "01", 2);
	}
	if (isAll0(dayBitExpThis) && kqNguyen == "01")
	{
		dayBitExpThis = cong(dayBitExpCong, dayBitExpThis, 2);
		kqSig.erase(0, 1);
	}
	kqNguyen = kqNguyen.erase(0, 1);

	string kq = kqNguyen + kqSig;
	if (!isAll0(dayBitExpThis))
	for (int i = 0; i < kq.length(); i++)
		if (kq[i] == '1')
		{
			kq.erase(0, i + 1);
			break;
		}
		else
		{
			dayBitExpThis = tru(dayBitExpThis, dayBitExpCong, 2);
			if (isAll0(dayBitExpThis))
			{
				kq.erase(0, i + 1);
				break;
			}
		}

	bool isInf = true;
	for (int i = 0; i < dayBitExpThis.length(); i++)
		if (dayBitExpThis[i] == '0')
		{
			isInf = false;
			break;
		}
	if (isInf)
		return Infinity();
	
	//tra ve ket qua
	bool*kqBit = new bool[128];
	kqBit[0] = dayBitThis[0];
	for (int i = 0; i < _bitExp; i++)
		kqBit[i + 1] = (bool)(dayBitExpThis[i] - '0');
	for (int i = 0; i < _bitSig; i++)
		kqBit[i + 1 + _bitExp] = (bool)(kqSig[i] - '0');

	delete[]dayBitThis;
	delete[]dayBitOther;
	return BinToDec(kqBit);
}



Qfloat Qfloat::operator-(Qfloat other)
{
	int*dayBitThis = NULL;
	convertToBit(dayBitThis);
	int*dayBitOther = NULL;
	other.convertToBit(dayBitOther);
	
	//neu 2 so khac dau thi ta cong voi so doi
	if (dayBitThis[0] != dayBitOther[0])
	{
		return *this + other.soDoi();
	}

	//neu 1 trong 2 so bang 0 thi tra ve so con lai
	if (this->convertToStringDec() == "0") return other.soDoi();
	if (other.convertToStringDec() == "0") return *this;

	//neu 1 trong 2 so la infinity thi tra ve infinity
	if (isInfinity(*this) || isInfinity(other))
		return Infinity();

	//xac dinh day cac bit cua cac so
	string dayBitExpThis = "", dayBitExpOther = "", dayBitExpCong = "";
	for (int i = 0; i < _bitExp; i++)
	{
		dayBitExpThis += (char)(dayBitThis[i + 1] + '0');
		dayBitExpOther += (char)(dayBitOther[i + 1] + '0');
		dayBitExpCong += "0";
	}
	dayBitExpCong[_bitExp - 1] = '1';
	string dayBitSigThis = "", dayBitSigOther = "";
	for (int i = 0; i < _bitSig; i++)
	{
		dayBitSigThis += (char)(dayBitThis[i + 1 + _bitExp] + '0');
		dayBitSigOther += (char)(dayBitOther[i + 1 + _bitExp] + '0');
	}

	//chuyen bit mu ve cung gia tri
	string phanNguyenThis = "1", phanNguyenOther = "1";
	if (isAll0(dayBitExpThis))
	{
		phanNguyenThis = "0";
		dayBitExpThis = cong(dayBitExpThis, dayBitExpCong, 2);
	}
	if (isAll0(dayBitExpOther))
	{
		dayBitExpOther = cong(dayBitExpCong, dayBitExpOther, 2);
		phanNguyenOther = "0";
	}

	while (dayBitExpOther != dayBitExpThis)
	{
		if (dayBitExpOther < dayBitExpThis)
		{
			dayBitExpOther = cong(dayBitExpOther, dayBitExpCong, 2);
			shiftRightString(dayBitSigOther, phanNguyenOther);
			phanNguyenOther = "0";
			continue;
		}

		if (dayBitExpOther > dayBitExpThis)
		{
			dayBitExpThis = cong(dayBitExpThis, dayBitExpCong, 2);
			shiftRightString(dayBitSigThis, phanNguyenThis);
			phanNguyenThis = "0";
		}
	}

	//neu cach biet 2 so qua lon thi ta tra ve so lon
	if (isAll0(dayBitSigOther) && phanNguyenOther == "0")
		return *this;
	if (isAll0(dayBitSigThis) && phanNguyenThis=="0")
		return other.soDoi();

	//thuc hien phep tru
	string kqNguyen = "";
	string kqSig = "";
	if (phanNguyenOther + dayBitSigOther < phanNguyenThis + dayBitSigThis)
	{
		string kqTru = tru(phanNguyenThis + dayBitSigThis, phanNguyenOther + dayBitSigOther, 2);
		kqNguyen = kqTru[0];
		kqSig = kqTru.erase(0, 1);
	}
	else if(phanNguyenOther + dayBitSigOther > phanNguyenThis + dayBitSigThis)
	{
		string kqTru = tru(phanNguyenOther + dayBitSigOther, phanNguyenThis + dayBitSigThis, 2);
		kqNguyen = kqTru[0];
		kqSig = kqTru.erase(0, 1);
		dayBitThis[0] = !dayBitThis[0];
	}
	else return Qfloat();

	//Dua so ve dang chuan hoac dang khong chuan
	string kq = kqNguyen + kqSig;
	if (!isAll0(dayBitExpThis))
	for (int i = 0; i < kq.length(); i++)
		if (kq[i] == '1')
		{
			kq.erase(0, i + 1);
			break;
		}
		else
		{
			dayBitExpThis = tru(dayBitExpThis, dayBitExpCong, 2);
			if (isAll0(dayBitExpThis))
			{
				kq.erase(0, i + 1);
				break;
			}
		}

	bool isInf = true;
	for(int i=0;i<dayBitExpThis.length();i++)
		if (dayBitExpThis[i] == '0')
		{
			isInf = false;
			break;
		}
	if (isInf)
		return Infinity();
	//gom lai va tra ve ket qua
	bool*kqBit = new bool[128];
	for (int i = 0; i < 128; i++)
		kqBit[i] = 0;
	kqBit[0] = dayBitThis[0];

	for (int i = 0; i < _bitExp; i++)
		kqBit[i + 1] = (bool)(dayBitExpThis[i] - '0');
	for (int i = 0; i < kq.length(); i++)
		kqBit[i + 1 + _bitExp] = (bool)(kq[i] - '0');

	delete[]dayBitThis;
	delete[]dayBitOther;
	return BinToDec(kqBit);
}

string nhan(string soA, string soB, int he)
{
	string kq = "";
	string kq1 = "";
	for (int i = 0; i < soB.length() - 1; i++)
		kq += "0";
	for (int i = 0; i < soA.length(); i++)
	{
		kq += '0';
		if (soA[i] != '0')
			kq = cong(kq, soB, 2);
		while (kq.length() >= soB.length())
			soB = "0" + soB;
	}
	return kq;
}

Qfloat Qfloat::operator*(Qfloat other)
{
	int*dayBitThis = NULL;
	convertToBit(dayBitThis);
	int*dayBitOther = NULL;
	other.convertToBit(dayBitOther);

	//neu 1 trong 2 so bang 0 thi tra ve so con lai
	if (this->convertToStringDec() == "0") return Qfloat();
	if (other.convertToStringDec() == "0") return Qfloat();

	//neu 1 trong 2 so la infinity thi tra ve infinity
	if (isInfinity(*this) || isInfinity(other))
		return Infinity();

	//xac dinh day cac bit cua cac so
	string dayBitExpThis = "", dayBitExpOther = "", dayBitExpCong = "", dayBitExpBias = "";
	for (int i = 0; i < _bitExp; i++)
	{
		dayBitExpThis += (char)(dayBitThis[i + 1] + '0');
		dayBitExpOther += (char)(dayBitOther[i + 1] + '0');
		dayBitExpCong += "0";
		dayBitExpBias += "1";
	}
	dayBitExpCong[_bitExp - 1] = '1';
	dayBitExpBias[0] = '0';
	string dayBitSigThis = "", dayBitSigOther = "";
	for (int i = 0; i < _bitSig; i++)
	{
		dayBitSigThis += (char)(dayBitThis[i + 1 + _bitExp] + '0');
		dayBitSigOther += (char)(dayBitOther[i + 1 + _bitExp] + '0');
	}

	string phanNguyenThis = "1", phanNguyenOther = "1";
	if (isAll0(dayBitExpThis))
		phanNguyenThis = "0";
	if (isAll0(dayBitExpOther))
		phanNguyenOther = "0";

	//Cong hai day bit Exp
	string kqExp = cong(dayBitExpOther, dayBitExpThis, 2);
	if (kqExp.length() > dayBitExpBias.length())
		dayBitExpBias = '0' + dayBitExpBias;
	kqExp = tru(kqExp, dayBitExpBias, 2);
	//Tran thi tra ve
	if (kqExp.length() > _bitExp && kqExp[0] == '1')
		return Qfloat::Infinity();
	if (dayBitExpThis[0] == '0' && dayBitExpOther[0] == '0' && kqExp[0] != '0')
		return Qfloat();
	if (kqExp.length() > _bitExp)
		kqExp = kqExp.erase(0, 1);
	dayBitExpThis = kqExp;
	
	//Nhan 2 day bit sig
	string kqNhan = nhan(phanNguyenThis + dayBitSigThis, phanNguyenOther + dayBitSigOther, 2);
	string kqNguyen = "";
	for (int i = 0; i < kqNhan.length() - 2 * _bitSig; i++)
		kqNguyen += kqNhan[i];
	string kqSig = kqNhan.erase(0, kqNguyen.length());
	kqSig = kqSig.erase(_bitSig, kqSig.length() - _bitSig);

	//dua so ve dang chuan hoac khong chuan
	if (kqNguyen.length() == 1)
		kqNguyen = '0' + kqNguyen;
	while (kqNguyen > "01")
	{
		if (kqNguyen[1] == '1')
			shiftRightString(kqSig, string("1"));
		else shiftRightString(kqSig, string("0"));
		dayBitExpThis = cong(dayBitExpCong, dayBitExpThis, 2);
		kqNguyen = tru(kqNguyen, "01", 2);
	}
	if (isAll0(dayBitExpThis) && kqNguyen == "01")
	{
		dayBitExpThis = cong(dayBitExpCong, dayBitExpThis, 2);
		kqSig.erase(0, 1);
	}
	kqNguyen = kqNguyen.erase(0, 1);

	string kq = kqNguyen + kqSig;
	if (!isAll0(dayBitExpThis))
		for (int i = 0; i < kq.length(); i++)
			if (kq[i] == '1')
			{
				kq.erase(0, i + 1);
				break;
			}
			else
			{
				dayBitExpThis = tru(dayBitExpThis, dayBitExpCong, 2);
				if (isAll0(dayBitExpThis))
				{
					kq.erase(0, i + 1);
					break;
				}
			}
	
	//gom lai va tra ve ket qua
	bool*kqBit = new bool[128];
	for (int i = 0; i < 128; i++)
		kqBit[i] = 0;
	kqBit[0] = (dayBitThis[0] + dayBitOther[0]) % 2;

	for (int i = 0; i < _bitExp; i++)
		kqBit[i + 1] = (bool)(dayBitExpThis[i] - '0');
	for (int i = 0; i < kq.length(); i++)
		kqBit[i + 1 + _bitExp] = (bool)(kq[i] - '0');

	delete[]dayBitThis;
	delete[]dayBitOther;
	return BinToDec(kqBit);
}


string chiaNhiPhan(string soA, string soB)
{
	string kq = "";
	int dem = 0;
	while (kq.length() <= _bitSig)
	{
		chuanHoaPhanNguyen(soA);
		chuanHoaPhanNguyen(soB);
		if (soSanh(soA, soB))
		{
			kq += "1";
			string kqTru = tru(soA, soB, 2);
			soA = kqTru;
			dem = 0;
		}
		else
		{
			soA += "0";
			if(dem>0)
				kq += "0";
			dem++;
		}
	}
	return kq;
}

Qfloat Qfloat::operator/(Qfloat other)
{
	int*dayBitThis = NULL;
	convertToBit(dayBitThis);
	int*dayBitOther = NULL;
	other.convertToBit(dayBitOther);

	//neu 1 trong 2 so bang 0
	if (this->convertToStringDec() == "0") return Qfloat();
	if (other.convertToStringDec() == "0") return Qfloat::Infinity();

	//neu this==infinity
	if (isInfinity(*this))
		return Infinity();

	//neu other==Infinity
	if (isInfinity(other))
		return Qfloat();

	//xac dinh day cac bit cua cac so
	string dayBitExpThis = "", dayBitExpOther = "", dayBitExpCong = "", dayBitExpBias = "";
	for (int i = 0; i < _bitExp; i++)
	{
		dayBitExpThis += (char)(dayBitThis[i + 1] + '0');
		dayBitExpOther += (char)(dayBitOther[i + 1] + '0');
		dayBitExpCong += "0";
		dayBitExpBias += "1";
	}
	dayBitExpCong[_bitExp - 1] = '1';
	dayBitExpBias[0] = '0';
	string dayBitSigThis = "", dayBitSigOther = "";
	for (int i = 0; i < _bitSig; i++)
	{
		dayBitSigThis += (char)(dayBitThis[i + 1 + _bitExp] + '0');
		dayBitSigOther += (char)(dayBitOther[i + 1 + _bitExp] + '0');
	}

	string phanNguyenThis = "1", phanNguyenOther = "1";
	if (isAll0(dayBitExpThis))
		phanNguyenThis = "0";
	if (isAll0(dayBitExpOther))
		phanNguyenOther = "0";

	//Chia 2 day bit sig
	string This = phanNguyenThis + dayBitSigThis;
	string this1 = This;
	string Other = phanNguyenOther + dayBitSigOther;
	string other1 = Other;
	int dem = 0;
	for (int i = 0; i < This.length(); i++)
		if (This[i] == '0')
		{
			this1.erase(0, 1);
			this1 += '0';
			dem--;
		}
		else
		{
			if (i != 0) dem++;
			break;
		}
	for (int i = 0; i < Other.length(); i++)
		if (Other[i] == '0')
		{
			other1.erase(0, 1);
			other1 += '0';
			dem++;
		}
		else {
			if (i != 0) dem--;
			break;
		}
	string kqChia = chiaNhiPhan(this1, other1);
	if (this1 < other1)
		dem--;

	//tru hai day bit exp
	string kqExp = dayBitExpBias;
	while (dem != 0)
	{
		if (dem < 0)
		{
			kqExp = tru(kqExp, dayBitExpCong, 2);
			dem++;
		}
		if (dem > 0)
		{
			kqExp = cong(kqExp, dayBitExpCong, 2);
			dem--;
		}
	}
	kqExp = cong(kqExp, dayBitExpThis, 2);
	if (soSanh(dayBitExpOther, kqExp))
	{
		while (soSanh(dayBitExpOther, kqExp))
		{
			shiftRightString(kqChia, "0");
			dayBitExpOther = tru(dayBitExpOther, dayBitExpCong, 2);
			if (isAll0(kqChia))
				return Qfloat();
		}
		kqExp = dayBitExpCong;
		if (kqChia[0] == '0')
			kqExp[kqExp.length() - 1] = '0';
	}
	else kqExp=tru(kqExp,dayBitExpOther,2);
	if (kqExp.length() > _bitExp) kqExp = kqExp.erase(0, 1);
	dayBitExpThis = kqExp;

	//gom lai va tra ve ket qua
	bool*kqBit = new bool[128];
	for (int i = 0; i < 128; i++)
		kqBit[i] = 0;
	kqBit[0] = (dayBitThis[0] + dayBitOther[0]) % 2;

	for (int i = 0; i < _bitExp; i++)
		kqBit[i + 1] = (bool)(dayBitExpThis[i] - '0');
	for (int i = 0; i < kqChia.length() - 1; i++)
		kqBit[i + 1 + _bitExp] = (bool)(kqChia[i + 1] - '0');

	delete[]dayBitThis;
	delete[]dayBitOther;
	return BinToDec(kqBit);
}

Qfloat & Qfloat::operator=(const char*a)
{
	convertFromString(string(a));
	return*this;
}

Qfloat & Qfloat::operator=(string a)
{
	convertFromString(a);
	return*this;
}

Qfloat & Qfloat::operator=(Qfloat a)
{
	for (int i = 0; i < _size; i++)
		_data[i] = a._data[i];
	return*this;
}

Qfloat::~Qfloat()
{
}
