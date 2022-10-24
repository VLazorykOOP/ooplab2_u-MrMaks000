#include <iostream>
#include <fstream>
using namespace std;
#include <clocale>
#include <string.h>
#include "EncryptionAndDecryption.h"



/*
Задано текст ASCII (текстовий рядок), який складається з 128 букв.
Написати функції шифрування та розшифрування заданого тексту.
Кожна при шифруванні буква тексту буде записана у елемент,
який складається з двох байтів та має структуру:
  -  у бітах 0-3 старша частина, тобто біти 4-7 ASCII - коду букви (4 біти) - СЧКБ,
  -  у бітах 4-10 позиція букви у рядку (7 біти) - ПБР,
  -  у бітах 11-14 молодша частина, тобто біти 0-3 ASCII - коду букви (4 біти) - МЧКБ,
  -  15 біт – біт парності отриманого запису (1 біт)  -БП.
  -    15  14 13 12 11  10 09 08 07 06 05 04  03 02 01 00
	  |БП| |  МЧКБ   |  |     ПБР          |  |   СЧКБ  |
*/
void EncryptionString(char InS[128], unsigned short OutCoding[128])
{
	unsigned char c;
	unsigned short r, t, i, b;
	short j;
	for (i = 0; i < 128; i++)            //
	{
		r = 0;                        // 0000 0000 0000 0000
		c = InS[i];                     // s - 0x73 = 0111 0011
		t = c;
		r |= t >> 4;                  // 0000 0000 0000 0111
		r |= i << 4;                  // 0000 0000 0101 0111  if i=5 -> 0000 0000 0000 0101
		t = c;
		t = c & 0x0f;
		r |= t << 11;                 // 0011 0000 0101 0111  if i=5 0000 0000 0000 0101
		t = 1;
		b = 0;
		for (j = 0; j < 15; j++)         // обчислення біта парності
		{
			if (r & t) {
				if (b == 0) b = 1; else b = 0;
			}
			t <<= 1;
		}
		r |= b << 15;                    // 0011 0000 0101 0111 if i=5 0000 0000 0000 0101
		OutCoding[i] = r;
	}
}
struct TextCode {
	unsigned short schkb : 4;
	unsigned short posrow : 7;	
	unsigned short mchkb : 4;
	unsigned short bitp : 1;

};
unsigned char bitp(unsigned char c)
{
	unsigned char t = 1, b = 0;
	for (int j = 0; j < 8; j++)         // обчислення біта парності
	{
		if (c & t) {
			if (b == 0) b = 1; else b = 0;
		}
		t <<= 1;
	}
	return b;
}
void EncryptionS(char InS[128], TextCode OutCoding[128])
{
	unsigned char c;
	unsigned short r, t, i;
	short j;
	for (i = 0; i < 128; i++)            //
	{
		c = InS[i];                     // s - 0x73 = 0111 0011
		OutCoding[i].schkb = c >> 4;
		OutCoding[i].mchkb = c & 0x0f;
		OutCoding[i].posrow = i;
		r = bitp(c);
		t = bitp(static_cast<unsigned char>(i));
		OutCoding[i].bitp = r ^ t;
	}
}

void DecryptionS(char InS[128], TextCode OutCoding[128])
{
	unsigned char c;
	unsigned short r, t, i;
	short j;
	for (int j = 0; j < 128; j++)            //
	{
		c = 0;
		c |= OutCoding[j].schkb << 4;
		c |= OutCoding[j].mchkb;
		i = OutCoding[j].posrow;
		r = bitp(c);
		t = bitp(static_cast<unsigned char>(i));
		if (OutCoding[j].bitp != r ^ t);

		InS[i] = c;		
	}
}



int DecryptionString(char OutS[128], unsigned short InCoding[128]) {

	unsigned char c;
	unsigned short r, t, i, b, p, w;
	short j;
	for (i = 0; i < 128; i++)            //
	{
		r = InCoding[i];
		t = r & 0b0111111111111111;      //  0xf7ff			0111 1111 1111 1111
		p = r & 0b1000000000000000;      //  0x0800			1000 0000 0000 0000
		w = 1;
		b = 0;
		for (j = 0; j < 15; j++)         // обчислення біта парності
		{
			if (t & w) {
				if (b == 0) b = 1; else b = 0;
			}
			w <<= 1;
		}
		p >>= 15;
		if (p != b)  return -i;
		t = r & 0b0111100000000000;  // 0xf000
		t >>= 11;
		w = r & 0b0000000000001111;  // 0x000f
		w <<= 4;
		t |= w;
		p = r & 0b0000011111110000;  // 0x07f
		p >>= 4;
		OutS[p] = (unsigned char)t;
	}
	return 1;
}
/*
* Приклад шифрування рядка в 128 байти
*
*/




void SEncryption() {
	char S[128];
	unsigned short Rez[128];
	unsigned short i, f;


	cout << " Input string from file press 1 <Enter>\n ";
	cin >> f;
	if (f == 1) {
		ifstream ifs("in.txt");
		if (!ifs) {
			cout << "File in.txt not open" << endl; f = 2;
		}
		else {
			ifs.get(S, 128);
			ifs.close();
		}
	}
	if (f != 1) {
		cin.get();
		cout << " Input string (size <=128) \n";
		cin.get(S, 128);
	}
	int n = strlen(S);
	for (int i = n; i < 128; i++) S[i] = '\0';





	EncryptionString(S, Rez);

	for (i = 0; i < 128; i++)
		cout << hex << Rez[i] << endl;


	ofstream ofsb("outb.bin", ios::out | ios::binary);
	if (!ofsb) {
		cout << "File outb.bin not open" << endl;
	}
	else {
		ofsb.write((char*)Rez, 128 * sizeof(unsigned short));
		ofsb.close();
		cout << "Data write to outb.bin " << endl;
		cout << S << endl;
	}
	cin.get();
}

void SDecryption() {
	char S[128];
	unsigned short InBin[128]{};

	ofstream ofs("out.txt");
	if (!ofs) {
		cout << "File out.txt not open" << endl;
		return;
	}
	ifstream ifsb("outb.bin", ios::in | ios::binary);
	if (!ifsb) {
		cout << "File outb.bin not open" << endl;
		return;
	}

	ifsb.read((char*)InBin, 128 * sizeof(unsigned short));
	ifsb.close();
	cout << "Data read from outb.bin " << endl;

	int r;
	r = DecryptionString(S, InBin);

	if (r < 1) {
		cout << "Error  read  " << r << " row " << endl;
	}
	cout << "String  " << S << endl;
	ofs << S << endl;
	cin.get();
}


void SEncryption2() {
	char S[129];
	TextCode Rez[128];
	unsigned short i, f;
	cout << " Input string from file press 1 <Enter>\n ";
	cin >> f;
	if (f == 1) {
		ifstream ifs("in.txt");
		if (!ifs) {
			cout << "File in.txt not open" << endl; f = 2;
		}
		else {
			ifs.get(S, 128);
			ifs.close();
		}
	}
	if (f != 1) {
		cin.get();
		cout << " Input string (size <=128) \n";
		cin.get(S, 128);
	}
	int n = strlen(S);
	for (int i = n; i < 128; i++) S[i] = '\0';

	EncryptionS(S, Rez);


	ofstream ofsb("outbs.bin", ios::out | ios::binary);
	if (!ofsb) {
		cout << "File outbs.bin not open" << endl;
	}
	else {
		ofsb.write((char*)Rez, 128 * sizeof(TextCode));
		ofsb.close();
		cout << "Data write to outbs.bin " << endl;
		cout << S << endl;
	}

	DecryptionS(S, Rez);
	cout << S << endl;

	cin.get();
}