#include <iostream>
using namespace std;
#include "Tasks.h"
//#include "Examples.h"
#include "EncryptionAndDecryption.h"

void MenuTask()
{
    cout << "     Menu Task   \n";
    cout << "    1.  Calculation of expressions using bitwise operations  \n";
    cout << "    2.  Data encryption using bitwise operations \n";
    cout << "    3.  Data encryption using structures with bit fields \n";
    cout << "    4.  The problem of using bitwise operations \n";
    cout << "    5.  Examples of problems using bitwise operations \n";
    cout << "    6.  Exit \n";
}

void task1() {
    // Обчислення виразів з використанням побітових операцій
    // Calculation of expressions using bitwise operations 
    cout << " Calculation of expressions using bitwise operations  \n";

    int a, b, c, d, x, y;

    cout << "An example of calculating an expression using only bitwise operations.\n";
    cout << "Expression : x = b * 37 + (d * 31 + a * 12) / 2048 - 65 * c + d * 14. \n";
    cout << " Input a  b  c  d";


    cin >> a >> b >> c >> d;
    auto st = cin.rdstate();
    if (st != cin.goodbit) { cin.clear(); cout << " error \n"; cin.get(); cin.get(); return; }
    x = ((b << 5) + (b << 2) + b) + ((((d << 5) - d) + ((a << 2) + (a << 3))) >> 11) - ((c << 6) + c) + ((d << 4) - (d << 1));
    y = b * 37 + (d * 31 + a * 12) / 2048 - 65 * c + d * 14;
    cout << "  x=" << x << "  y=" << y << " a=" << a << "  b=" << b << "  c=" << c << "  d=" << d << endl;
    cin.get();
    cin.get();
    return;
}

void task2()
{
    // Шифрування даних з використання побітових операцій 
    // Data encryption using bitwise operations
    cout << " Data encryption using bitwise operations  \n";
    SEncryption();
    SDecryption();

}

void task3()
{
    // Шифрування даних з використання стуктур з бітовими полями 
    // Data encryption using structures with bit fields
    cout << "  Data encryption using structures with bit fields \n";
    SEncryption2();
}


void task4()
{   // Задача із використання побітових операцій
    // The problem of using bitwise operations
    cout << " Data encryption using structures with bit fields \n";

    int x, y;
    double a, b;

    cout << "An example of calculating an expression using only bitwise operations.\n";
    cout << "Expression : a = (20 * y - x * 120) / 32 + (x + 32 * y) / 128 + (x + y)%16. \n";
    cout << " Input x  y  ";


    cin >> x >> y;
    auto st = cin.rdstate();
    if (st != cin.goodbit) { cin.clear(); cout << " error \n"; cin.get(); cin.get(); return; }
    a = ((((y << 4) + (y << 2)) - ((x << 7) - (x << 3))) >> 5) + ((x + (y << 5)) >> 7) + ((x + y) % 16) + 1;
    b = ((20 * y - x * 120) / 32) + ((x + 32 * y) / 128) + ((x + y) % 16);
    cout << "  x=" << x << "  y=" << y << " a=" << a << "  b=" << b << endl;
    cin.get();
    cin.get();
    return;
}


