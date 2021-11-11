#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <bitset>
using namespace std;

typedef bitset<128> binary;

class QInt
{
public:
	binary bit;
public:
	QInt();
	QInt(const QInt& num);
	QInt(uint16_t mode, string s);

	//Converter
	string BinToDec();
	static string DecToBin(string dec);
	static string CheckEven(string number);
	static string DivideBy2(string dec);

	//Operator
		//Arithmetic
	QInt& operator=(QInt const& Qint);
	QInt operator+(const QInt& Qint2);
	QInt operator-(const QInt& Qint2);
	QInt operator*(const QInt& Qint2);
	QInt operator/(const QInt& Qint2);
	//Bitwise
	QInt operator&(const QInt& Qint2);
	QInt operator|(const QInt& Qint2);
	QInt operator^(const QInt& Qint2);
	QInt operator~();
	QInt operator>>(int step);
	QInt operator<<(int step);


	void printbit();
	string printAsMode(uint16_t mode);
	int* Addition(int* ResultArray, int* SaveNumber, int n, int i);
};

string normalize(string s) {
	int i = s.find_first_not_of("0");
	if (i == -1)
		return "0";
	return s.substr(i);
}

QInt::QInt()
{
	this->bit = QInt(2, "0").bit;
}

QInt::QInt(const QInt& num)
{
	this->bit = num.bit;
}

QInt::QInt(uint16_t mode, string s)
{
	if (mode == 2)
		this->bit = binary(s);

	else if (mode == 10) {
		bool isNegative = false;
		if (s[0] == '-')
		{
			isNegative = true;
			s = s.substr(1);
		}

		this->bit = binary(DecToBin(s));

		if (isNegative)
		{
			bit = ~bit;
			*this = *this + QInt(2, "1");
		}
	}
}

int* QInt::Addition(int* ResultArray, int* SaveNumber, int n, int bit) {
	int reminder = 0;

	if (bit == 1) {
		for (int i = n - 1; i >= 0; i--) {
			ResultArray[i] = ResultArray[i] + SaveNumber[i] + reminder;
			reminder = 0;
			if (ResultArray[i] >= 10) {
				ResultArray[i] = ResultArray[i] % 10;
				reminder++;
			}
		}
	}

	reminder = 0;
	for (int i = n - 1; i >= 0; i--) {
		SaveNumber[i] = SaveNumber[i] * 2 + reminder;
		reminder = 0;
		if (SaveNumber[i] >= 10) {
			SaveNumber[i] = SaveNumber[i] % 10;
			reminder++;
		}
	}
	return ResultArray;
}

string QInt::BinToDec()
{
	int check = ((*this).bit.to_string()).find_first_not_of("0");
	if (check == -1)
		return "0";
	string number = "";
	int n = 40;
	int* ResultArray = new int[n] { 0 };
	int* SaveNumber = new int[n] { 0 };
	SaveNumber[39] = 1;
	int negative = false;
	if ((*this).bit[127] == 1)
		negative = true;

	if (negative) {
		*this = *this - QInt(2, "1");
		*this = ~(*this);
	}

	for (int i = 0; i < (*this).bit.size(); i++) {
		ResultArray = Addition(ResultArray, SaveNumber, n, this->bit[i]);
	}
	for (int i = 0; i < n; i++) {
		number = number + to_string(ResultArray[i]);
	}

	number = normalize(number);

	if (negative) {
		number = "-" + number;
	}
	if (negative) {
		*this = ~(*this);
		*this = *this + QInt(2, "1");
	}
	delete[] ResultArray;
	delete[] SaveNumber;
	return number;
}

string QInt::CheckEven(string number) {
	string remainder;
	if (number[number.size() - 1] % 2 == 0) {
		remainder = "0";
	}
	else {
		remainder = "1";
	}
	return remainder;
}

string QInt::DivideBy2(string dec) {
	string ans;
	int idx = 0;
	int temp = dec[idx] - '0';
	if (dec.size() < 2 && temp < 2) {
		ans = "0";
		return ans;
	}
	while (temp < 2)

		temp = temp * 10 + (dec[++idx] - '0');
	while (dec.size() > idx)
	{
		ans += (temp / 2) + '0';
		temp = (temp % 2) * 10 + dec[++idx] - '0';
	}

	if (ans.length() == 0)
		return "0";
	return ans;
}

string QInt::DecToBin(string dec)
{
	bool isNegative = false;
	if (dec[0] == '-') {
		isNegative = true;
		dec = dec.substr(1);
	}


	if (dec == "0")
		return "0";
	string result = "";
	while (dec != "0") {
		result = CheckEven(dec) + result;
		dec = DivideBy2(dec);
	}

	if (isNegative) {
		QInt temp;
		temp.bit = binary(result);
		temp = ~temp;
		temp = temp + QInt(2, "1");
		result = temp.bit.to_string();
	}

	return result;
}

//Arithmetic
QInt& QInt::operator=(QInt const& Qint)
{
	this->bit = Qint.bit;
	return (*this);
}

QInt QInt::operator+(const QInt& Qint2)
{
	QInt result;
	int carry = 0;

	for (int i = 0; i < this->bit.size(); i++) {
		if (this->bit[i] == 0 && Qint2.bit[i] == 0) {
			result.bit[i] = 0 ^ carry;
			carry = 0;
		}
		else if ((this->bit[i] & Qint2.bit[i]) == 0) {
			if (carry == 1) {
				result.bit[i] = 0;
				carry = 0;
				carry++;
			}
			else if (carry == 0) {
				result.bit[i] = 1;
			}
		}
		else
		{
			result.bit[i] = (this->bit[i] ^ Qint2.bit[i]) ^ carry;
			carry = 0;
			carry++;
		}
	}
	return result;
}

QInt QInt::operator-(const QInt& Qint2)
{
	QInt result, temp = Qint2;
	temp = ~temp;
	temp = temp + QInt(2, "1");
	result = *this + temp;
	return result;
}

QInt QInt::operator*(const QInt& Qint2)
{
	QInt result;
	for (int i = 0; i < Qint2.bit.size(); i++) {
		if (Qint2.bit[i] == 1) {
			result = result + *this;
		}
		this->bit = this->bit << 1;
	}
	return result;
}

QInt QInt::operator/(const QInt& Qint2) //Non-restore division
{
	int flag = 0;
	QInt Quotent = (*this);

	if (Quotent.bit[127] == 1)
	{
		Quotent = Quotent - QInt(2, "1");
		Quotent = ~Quotent;
		flag++;
	}

	QInt Divisor = Qint2;

	if ((Divisor).bit[127] == 1)
	{
		Divisor = Divisor - QInt(2, "1");
		Divisor = ~Divisor;
		flag++;
	}

	QInt Remainder;
	int n = Quotent.bit.size();

	while (n > 0) {
		bool carry = Quotent.bit[127];

		Remainder = Remainder << 1;
		Quotent = Quotent << 1;

		Remainder.bit[0] = carry;

		Remainder = Remainder - Divisor;

		if (Remainder.bit[127] == 1) {
			Quotent.bit[0] = 0;
			Remainder = Remainder + Divisor;
		}
		else
			Quotent.bit[0] = 1;

		n = n - 1;
	}

	if (flag == 1) {
		Quotent = ~Quotent;
		Quotent = Quotent + QInt(2, "1");
	}

	return Quotent;
}

//Bitwise
QInt QInt::operator&(const QInt& Qint2)
{
	QInt result;
	for (int i = 0; i < Qint2.bit.size(); i++) {
		if (this->bit[i] == 1 && Qint2.bit[i] == 1)
			result.bit[i] = 1;
		else
			result.bit[i] = 0;
	}
	return result;
}

QInt QInt::operator|(const QInt& Qint2)
{
	QInt result;
	for (int i = 0; i < Qint2.bit.size(); i++) {
		if (this->bit[i] == 0 && Qint2.bit[i] == 0)
			result.bit[i] = 0;
		else
			result.bit[i] = 1;
	}
	return result;
}

QInt QInt::operator^(const QInt& Qint2)
{
	QInt result;
	for (int i = 0; i < Qint2.bit.size(); i++) {
		if (this->bit[i] == Qint2.bit[i])
			result.bit[i] = 0;
		else
			result.bit[i] = 1;
	}
	return result;
}

QInt QInt::operator~()
{
	QInt result = *this;
	for (int i = 0; i < result.bit.size(); i++) {
		if (result.bit[i] == 0)
			result.bit[i] = 1;
		else if (result.bit[i] == 1)
			result.bit[i] = 0;
	}
	return result;
}

QInt QInt::operator>>(int step)
{
	QInt result = *this;
	if (step >= 127) {
		step = 127;
	}
	for (int i = step; i < 127; i++) {
		result.bit[i - step] = result.bit[i];
	}
	if (result.bit[127] == 1) {

		for (int i = 126; i > 126 - step; i--) {
			result.bit[i] = 1;
		}
	}
	else {
		for (int i = 126; i > 126 - step; i--) {
			result.bit[i] = 0;
		}
	}
	return result;
}

QInt QInt::operator<<(int step)
{
	QInt result = *this;
	if (step >= 128) {
		step = 128;
	}
	for (int i = 127 - step; i >= 0; i--) {
		result.bit[i + step] = result.bit[i];
	}
	for (int i = 0; i < step; i++) {
		result.bit[i] = 0;
	}
	return result;
}


void QInt::printbit()
{
	for (int i = (*this).bit.size() - 1; i >= 0; i--) {
		cout << (*this).bit[i];
	}
}

string QInt::printAsMode(uint16_t mode)
{
	string result;
	if (mode == 10)
		result = (*this).BinToDec();
	if (mode == 2)
	{
		result = (*this).bit.to_string();
		result = normalize(result);
	}
	return result;
}



string multiply(string num1_bit, string num2_bit) {
	int n = max(num1_bit.size(), num2_bit.size());
	if (n <= 8) {
		QInt num1(2, num1_bit);
		QInt num2(2, num2_bit);
		unsigned long long a = stoull(num1.BinToDec());
		unsigned long long b = stoull(num2.BinToDec());
		return to_string(a * b);
	}
	else {
		int fh = n / 2;
		int sh = (n - fh);

		string xL = num1_bit.substr(0, fh);
		string xR = num1_bit.substr(fh, sh);

		string yL = num2_bit.substr(0, fh);
		string yR = num2_bit.substr(fh, sh);

		QInt temp1 = QInt(2,xL) + QInt(2,xR);
		QInt temp2 = QInt(2, yL) + QInt(2, yR);

		string sum1 = temp1.printAsMode(2);
		string sum2 = temp2.printAsMode(2);

		string r = multiply(sum1,sum2);
		string p = multiply(xL,yL);
		string q = multiply(xR,yR);

		return to_string( stoull(p) * (1<<(2*sh)) + (stoull(r) - stoull(p) - stoull(q)) * (1 << sh) + stoull(q) );
	}
}


void main() {
	ifstream input("input_1.txt");
	string a, b;
	input >> a;
	input >> b;
	string num1_bit = QInt::DecToBin(a);
	string num2_bit = QInt::DecToBin(b);
	cout << multiply(num1_bit, num2_bit);
}

