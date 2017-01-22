//File stringopr.cpp

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

//Kamus Lokal
int np = 0; int nk = 0; int nt = 0;

//Inisialisasi
string strkurang (string str1, string str2);
string strkali(string str1, string str2, int n, bool neg);

bool negatif(string str) {
//Menentukan apakah string merupakan integer positif atau bukan
	return (str[0] == '-');
}

bool lebihbesar (string str1, string str2) {
//Mengembalikan true jika str1 > str2
//Precondition str1 != str2
	bool bigger = true;
	if (negatif(str1) && !negatif(str2)) {
		bigger = false;
	}
	else if (!negatif(str1) && negatif(str2)) {
		bigger = true;
	}
	else if (str1.length() > str2.length()) {
		bigger = true;
	}
	else if (str1.length() < str2.length()) {
		bigger = false;
	}
	else {
		unsigned int i = 0;
		if (negatif(str1)) {
			i++;
		}
		while ((i < str1.length()) && (str1[i] == str2[i])) {
			i++;
		}
		if (i == str1.length()) {
			bigger = true;
		}
		else {
			if ((str1[i] - '0') < (str2[i] - '0')) {
				bigger = false;
			}
		}
	}
	return bigger;
}

string buangminus (string str)
//Mengembalikan string tanpa tanda '-'
{
	string sh;
	if (!negatif(str)) {
		sh = str;
	}
	else {
		sh = str.substr(1, str.length()-1);
	}
	return sh;
}

string isinol (string str, int dif)
//Menambahkan nol sejumlah dif pada string
{
	string temp;
	if (negatif(str)) {
		int len = str.length() - 1;
		temp = str.substr(1, len);
		for (int j = 0; j < dif; j++) {
			temp = "0" + temp;
		}
		temp = "-" + temp;
	}
	else {
		temp = str;
		for (int j = 0; j < dif; j++) {
			temp = "0" + temp;
		}
	}
	return temp;
}

string buangnol (string str)
//Menghilangkan nol di awal agar saat dikembalikan nilainya tidak ada nol di depan
{
	unsigned int i = 0;
	string shasil;
	bool tadiminus = false;
	//Jika nilainya minus, dihilangkan terlebih dahulu
	if (str[0] == '-') {
		tadiminus = true;
		str = buangminus(str);
	}
	if (str[0] == '0') 	{
		while (str[i] == '0') {
			i++;
		}
		if (i == str.length()) {
			shasil = "0";
		}
		else {
			shasil = str.substr(i, str.length()-1);
		}
	}
	else {
		shasil = str;
	}
	if (tadiminus) {
		shasil = "-" + shasil;
	}
	return shasil;
}


string strjumlah(string str1, string str2) {
//Mengembalikan hasil str1 + str2
	string shasil;
	bool tadinyaminus = false;

	//St1 dan st2 untuk menentukan apakah panjang string sama atau tidak
	string st1 = buangminus(str1);
	string st2 = buangminus(str2);
	if (st1.length() != st2.length())
	{
		if(st1.length() < st2.length())
		{
			int lendif = st2.length() - st1.length();
			str1 = isinol(str1, lendif);
		}
		else
		{
			int lendif = st1.length() - st2.length();
			str2 = isinol(str2, lendif);
		}
	}

	int temp;
	string stemp;
	int sisa = 0;
	//Jika keduanya negatif, dihilangkan minusnya untuk dijumlahkan
	//Tanda minus akan ditambahkan di akhir proses
	if (negatif(str1) && negatif(str2)) {
		str1 = str1.substr(1,str1.length()-1);
		str2 = str2.substr(1,str2.length()-1);
		tadinyaminus = true;
	}

    //Jika tanda keduanya sama
	if (!negatif(str1) && !negatif(str2)) {
		for(int i = str1.length()-1; i >= 0; i--) {
			temp = (str1[i]-'0') + (str2[i]-'0') + sisa;
			sisa = 0;
			if ((temp >= 10)) {
				sisa = 1;
				temp -= 10;
			}
			stemp = temp + '0';
			if ((sisa > 0) && (i == 0)) {
                stemp = "1" + stemp;
			}
			shasil = stemp + shasil;
			np++;
		}
	}
	else //Jika salah satu string adalah bilangan negatif
	{
	    //Jika str1 > str2, atau str2 adalah minus
		if(lebihbesar(str1,str2)) {
			string s2;
			s2 = str2.substr(1, str2.length()-1);
			shasil = strkurang(str1, s2);
		}
		else {  //jika minus di str1
			string s1;
			s1 = str1.substr(1, str1.length()-1);
			shasil = strkurang(str2, s1);
		}
	}

	//Menambahkan minus jika sebelumnya nilai keduanya negatif
	if (tadinyaminus) {
		shasil = "-" + shasil;
	}
	shasil = buangnol(shasil);
	return shasil;
}

string strkurang (string str1, string str2) {
//Mengambalikan nilai str1 - str2
	string shasil;
	//Untuk mengecek apakah lengthnya sama
	//Jika tidak, tambahkan nol di depan string yang
	//lengthnya lebih sedikit
	string st1 = buangminus(str1);
	string st2 = buangminus(str2);
	if (st1.length() != st2.length()) {
		if(st1.length() < st2.length()) {
			int lendif = st2.length() - st1.length();
			str1 = isinol(str1, lendif);
		}
		else {
			int lendif = st1.length() - st2.length();
			str2 = isinol(str2, lendif);
		}
	}

    //Jika kedua string nilainya sama, maka hasilnya nol
	if (str1 == str2) {
		shasil = "0";
	}
	//Jika keduanya negatif
	else if (negatif(str1) && negatif(str2)) {
		string s1, s2;
		s1 = str2.substr(1,str2.length()-1);
		s2 = str1.substr(1,str1.length()-1);
		shasil = strkurang(s1,s2);
	}
	//Jika keduanya positif
	else if (!negatif(str1) && !negatif(str2)) {
        //Jika str2 lebih besar
		if (!lebihbesar(str1, str2)) {
			shasil = "-" + strkurang(str2, str1);
		}
        //Jika str1 lebih besar
		else {
			int sisa = 0; //sisa pengurangan
			string stemp;
			int temp; //hasil pengurangan per digit

			for(int i = str1.length()-1; i >= 0; i--) {
				temp = (str1[i]-'0') - (str2[i]-'0') - sisa;
				sisa = 0;
				if (temp < 0) {
					sisa = 1;
					temp += 10;
				}
				stemp = temp + '0';
				shasil = stemp + shasil;
				nk++;
			}
		}
	}
	else { //salah satunya minus
        //Jika str1 lebih besar
		if (lebihbesar(str1, str2)) {
			string s2 = str2.substr(1, str2.length()-1);
			shasil = strjumlah(str1, s2);
		}
        //Jika str2 lebih besar
		else {
			string s2 = "-" + str2;
			shasil = strjumlah(str1, s2);
		}
	}
	shasil = buangnol(shasil);
	return shasil;
}

string divide(string x, int y){
//Membagi x dengan 10^y

//Kamus Lokal
    string s;

//Algoritma
    if (x.length() < (y + 1)) {
        s = "0";
    }
    else {
        for (int i = 0; i < y; i++){
            s = s + x[i];
        }
    }
    return s;
}

bool salahsatuneg (string s1, string s2)
{
	return ((negatif(s1) && !negatif(s2)) || (!negatif(s1) && negatif(s2)));
}


string modus(string x, int y){

//Mencari mod x jika dibagi 10^y
    string s;

//Algoritma
    if (x.length() < (y + 1)) {
        s = x;
    }
    else {
        for (int i = y; i < x.length(); i++){
            s = s + x[i];
        }
    }
    return s;
}

string nolblkg (string str, int n)
{
//Algoritma
    for(int j = 1; j <= n; j++)
    {
        str =  str + "0";
    }
    return str;
}

string perkalian(string str1, string str2, int n){
//Melakukan perkalian menggunakan prinsip algoritma divide and conquer
//Kamus Lokal
    string a, b, c, d, e, p, q, r, t, u, jum1, jum2, krg1, jum3;
    string h1, h2, h3, h4;
	int s=0, temp=0;
    ostringstream convert;

//Algoritma
    nt++;
    if((str1.length() % 2) == 1)
    {
        str1 = '0' + str1;
        str2 = '0' + str2;
    }
    //Karatsuba Algorithm
    if (n == 1) { //basis
        temp = (atoi(str1.c_str()))*(atoi(str2.c_str()));
        convert << temp;
        a = convert.str();
        return a;
    } else { //Rekurens
        s = str1.length() / 2;
        a = divide(str1, s);
        b = modus(str1, s);
        c = divide(str2, s);
        d = modus(str2, s);
        p = perkalian (a, c, s);
        q = perkalian(b, d, s);
        jum1 = strjumlah(a, b);
        jum2 = strjumlah(c, d);
        r = strkali(jum1, jum2, s, salahsatuneg(jum1, jum2));
        h1 = nolblkg(p, (2 * s));
        krg1 = strkurang(r,p);
        h2 = strkurang(krg1, q);
        h3 = nolblkg(h2, s);
        jum3 = strjumlah(h1, h3);
        h4 = strjumlah(jum3, q);
        return h4;
    }
}

string strkali(string str1, string str2, int n, bool neg){
//Mengembalikan hasil akhir dari perkalian
//Kamus lokal
    string s, x, y;

//Algoritma
    x = buangminus(str1); y = buangminus(str2);
    if (x.length() != y.length())
	{
		if(x.length() < y.length())
		{
			int lendif = y.length() - x.length();
			x = isinol(x, lendif);
		}
		else
		{
			int lendif = x.length() - y.length();
			y = isinol(y, lendif);
		}
	}
	s = perkalian(x, y, n);
    if ((neg) && (s != "0")){
        s = '-' + s;
    }
    s = buangnol(s);
    return s;
}

int main() {
    //Kamus
	string a, b, c, d, e;
	int n, t1, t2, t3, t4, t5, total;

    //Algoritma
	//Meminta input
	cout << "n : "; cin >> n;
	cout << "a : "; cin >> a;
	cout << "b : "; cin >> b;
	cout << endl;

	//Penjumlahan
	t1 = clock();
	c = strjumlah(a , b);
	t2 = clock(); t3 = t2 - t1;
	cout << "a + b = " << c << endl;
	if (np == 0){
        np = nk;
	}
	cout << "Jumlah operasi penjumlahan : " << np << " kali" << endl;
	cout << "Waktu Eksekusi : " << t3 << " ms" << endl << endl;

	//Pengurangan
	np = 0; nk = 0;
	t1 = clock();
	d = strkurang(a, b);
	t2 = clock(); t4 = t2 - t1;
	cout << "a - b = " << d << endl;
	if (nk == 0){
        nk = np;
	}
	cout << "Jumlah operasi pengurangan : " << nk << " kali" << endl;
	cout << "Waktu Eksekusi : " << t4 << " ms" << endl << endl;

	//Perkalian
	np = 0; nk = 0;
	t1 = clock();
	e = strkali(a, b, n, salahsatuneg(a, b));
	t2 = clock(); t5 = t2 - t1;
	cout << "a * b = " << e << endl;
	cout << "Jumlah operasi penjumlahan : " << np << " kali" << endl;
	cout << "Jumlah operasi pengurangan : " << nk << " kali" << endl;
	cout << "Jumlah operasi perkalian : " << nt << " kali" << endl;
	cout << "Waktu Eksekusi : " << t5 << " ms" << endl << endl;

	//Waktu Eksekusi Total
	total = t3 + t4 + t5;
	cout << "Waktu Eksekusi Total : " << total << " ms" << endl;

	return 0;
}
