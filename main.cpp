#include <cstdint>
#include <cstring>
#include <iostream>
using namespace std;

void number0(uint32_t x, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        cout << ((x >> i) & 1u);
    }
    cout << endl;
}

void number1() {
    cout << "bool: " << sizeof(bool) << endl;
    cout << "char: " << sizeof(char) << endl;
    cout << "short int: " << sizeof(short int) << endl;
    cout << "int: " << sizeof(int) << endl;
    cout << "long int: " << sizeof(long int) << endl;
    cout << "float: " << sizeof(float) << endl;
    cout << "double: " << sizeof(double) << endl;
    cout << "long double: " << sizeof(long double) << endl;
}

void number2(int u, int width) {
    for (int i = width - 1; i >= 0; --i) {
        if (i == width - 1)
            cout << " ";
        cout << ((u >> i) & 1);
        if ((width - 1 - i) % 8 == 7)
            cout << ' ';
    }
    cout << endl;
}


void number3Float(float f) {
    uint32_t bits;
    memcpy(&bits, &f, sizeof(bits));

    int sign     = (bits >> 31) & 1;
    int exponent = (bits >> 23) & 0xFF;
    int mantissa =  bits        & 0x7FFFFF;

    cout << f << endl;
    cout << "(sign) " << sign << " (exp) ";
    for (int i = 30; i >= 23; --i)
        cout << ((bits >> i) & 1);
    cout << " (mant) ";
    for (int i = 22; i >= 0; --i)
        cout << ((bits >> i) & 1);
    cout << endl;
    cout << "sign = " << sign << " exponent = " << exponent
         << " (bias 127, E = " << (exponent - 127) << ") mantissa = " << mantissa;
    cout << endl;
}

void number4Double(double d) {
    uint64_t bits;
    memcpy(&bits, &d, sizeof(bits));

    int sign              = (int)((bits >> 63) & 1);
    int exponent          = (int)((bits >> 52) & 0x7FF);
    unsigned long long mantissa = bits & 0xFFFFFFFFFFFFFULL;

    cout << d << endl;
    cout << "(sign) " << sign << " (exp) ";
    for (int i = 62; i >= 52; --i)
        cout << ((bits >> i) & 1);
    cout << " (mant) ";
    for (int i = 51; i >= 0; --i)
        cout << ((bits >> i) & 1);
    cout << endl;
    cout << "sign = " << sign << " exponent = " << exponent
         << " (bias 1023, E = " << (exponent - 1023) << ") mantissa = " << mantissa;
    cout << endl;
}

int main() {
    cout << "===================================" << endl;
    number1();
    cout << endl;

    cout << "===================================" << endl;
    cout << "Введите целое число (0-127): ";
    int32_t pos;
    cin >> pos;
    cout << "Введите отрицательное целое число (-128-0): ";
    int32_t neg;
    cin >> neg;
    cout << pos << "  ";
    number2((uint32_t)pos, 32);
    cout << neg << "  ";
    number2((uint32_t)neg, 32);
    cout << endl;

    cout << "=== float  ===" << endl;
    cout << "Введите дробное число: ";
    float num1;
    cin >> num1;
    number3Float(num1);
    cout << endl;
    cout << "Введите отрицательное дробное число: ";
    float num2;
    cin >> num2;
    number3Float(num2);
    cout << endl;

    cout << "=== double  ===" << endl;
    cout << "Введите дробное число: ";
    double num3;
    cin >> num3;
    number4Double(num3);
    cout << endl;
    cout << "Введите отрицательное дробное число: ";
    double num4;
    cin >> num4;
    number4Double(num4);
    cout << endl;


    uint32_t x;
    int command = 0;
    int bit = 0;

    cout << "Введите число: " << endl;
    cin >> x;

    cout << "Выберите операцию:" << endl;
    cout << "1 - Установить бит" << endl;
    cout << "2 - Сбросить бит" << endl;
    cout << "3 - Инвертировать бит" << endl;
    cout << "Ваш выбор: ";
    cin >> command;

        if (command >= 1 && command <= 3) {
            cout << "Введите номер бита (0-31): ";
            cin >> bit;

            if (bit < 0 || bit > 31) {
                cout << "Ошибка: номер бита должен быть от 0 до 31" << endl;
                return 1;
            }
        }

        cout << "До:    ";
        number0(x, 32);

        switch (command) {
            case 1:
                x |= (1u << bit);
                break;

            case 2:
                x &= ~(1u << bit);
                break;

            case 3:
                x ^= (1u << bit);
                break;

            default:
                cout << "Неизвестная команда!" << endl;
                return 1;
        }

        cout << "После: ";
        number0(x, 32);

        cout << "Результат: " << x << endl;

    cout << "=== изменение знакового бита у float и double ===" << endl;
    cout << "Введите дробное число, отличное от нуля: ";
    float num5;
    cin >> num5;
    if (num5 == 0) {
        cout << "Ошибка: вы ввели число 0" << endl;
        return 1;
    }
    uint32_t fb;
    memcpy(&fb, &num5, sizeof(fb));
    fb ^= (1u << 31);
    memcpy(&num5, &fb, sizeof(num5));
    cout << endl << num5 << " , инверсия бита 31:" << endl;
    number3Float(num5);

    cout << "Введите дробное число, отличное от нуля: ";
    double num6;
    cin >> num6;
    if (num6 == 0) {
        cout << "Ошибка: вы ввели число 0" << endl;
        return 1;
    }
    uint64_t db;
    memcpy(&db, &num6, sizeof(db));
    db ^= (1ull << 63);
    memcpy(&num6, &db, sizeof(num6));
    cout << endl << num6 << " , инверсия бита 63:" << endl;
    number4Double(num6);
    cout << endl;
    
    cout << "=== зануление старшего бита ===" << endl;
    cout << "Введите целое число: ";
    unsigned int y;
    cin >> y;
    cout << "До: " << bitset<8>(y) << endl;
    y &= ~(1u << 7);
    cout << "После: "<< bitset<8>(y);
    
    return 0;
}
