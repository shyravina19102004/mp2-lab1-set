#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(-1)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(-1)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(-1)
{
}

TSet::operator TBitField()
{
    TBitField temp(this->BitField);
  return temp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    BitField = s.BitField;
  MaxPower = s.GetMaxPower();
  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return FAKE_INT;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet temp(BitField | s.BitField);
    return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    return FAKE_SET;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    return FAKE_SET;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet temp(BitField & s.BitField);
    return temp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet temp(~BitField);
    return temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    // формат данных - { i1, i2,.., in }
    int temp; char ch;
    // поиск {
    do { istr >> ch; } while (ch != '{');
    // ввод элементов и включение в множество
    do {
        istr >> temp; s.InsElem(temp);
        do { istr >> ch; } while ( ( ch != ',' ) && ( ch != '}' ) );
        } while (ch != '}');
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    // формат данных - { i1, i2,.., in }
    int i, n; char ch = ' ';
    ostr << "{";
    // вывод элементов
    n = s.GetMaxPower();
    for ( i=0; i < n; i++ ) {
        if ( s.IsMember(i) ) { ostr << ch << ' ' << i; ch = ','; }
  }
  ostr << " }";
  return ostr;
}
