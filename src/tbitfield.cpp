#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len <= 0)
    {
        throw ("Некорректное знач");
    }
    BitLen = len;
    MemLen = (BitLen + sizeof(int) * 8 - 1) / (sizeof(int) * 8);
    pMem = new TELEM [MemLen];
    for (int i = 0; i < MemLen; i++) 
    {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{ 
    MemLen = ( len + 15 ) >> 4; // в эл-те pМем 16 бит (TELEM==int)
    pMem   = new TELEM[MemLen];
    if ( pMem != NULL )
        for ( int i=0; i < MemLen; i++ ) pMem[i] = 0;
        {
            pMem[i] = 0;
        }
}

TBitField::~TBitField()
{ 
    delite[]pMem; 
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return (n / (sizeof(int) * 8));
    
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1 << (n & 15);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;  
}

void TBitField::SetBit(const int n) // установить бит
{
    if ( (n > -1) && (n < BitLen) )
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ( (n > -1) && (n < BitLen) )
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ( (n > -1) && (n < BitLen) )
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    BitLen = bf.BitLen;
    if (MemLen != bf.MemLen) 
    {
        MemLen = bf.MemLen;
        if (pMem != NULL) 
        {
            delete pMem;
        }
        pMem = new TELEM[MemLen];
    }
    if (pMem != NULL) 
    {
        for (int i = 0; i < MemLen; i++) 
        {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if ( BitLen != bf.BitLen ) res = 0;
  else
    for ( int i=0; i < MemLen; i++ )
      if ( pMem[i] != bf.pMem[i] ) { res = 0; break; 
  return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if ( BitLen != bf.BitLen ) res = 0;
  else
    for ( int i=0; i < MemLen; i++ )
      if ( pMem[i] != bf.pMem[i] ) { res = 0; break; 
  return res;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    if (this->BitLen != bf.BitLen) 
    {
        throw ("Ошибка");
    }
    TBitField res(*this);
    for (int i = 0; i < MemLen; i++)
    {
        res.pMem[i] |= bf.pMem[i];
    }
    return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    if (this->BitLen != bf.BitLen) 
    {
        throw ("Ошибка");
    }
    TBitField res(*this);
    for (int i = 0; i < MemLen; i++)
    {
        res.pMem[i] |= bf.pMem[i];
    }
    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    if (this->BitLen != bf.BitLen) 
    {
        throw ("Ошибка");
    }
    TBitField res(*this);
    for (int i = 0; i < MemLen; i++)
    {
        res.pMem[i] |= bf.pMem[i];
    }
    return res;
}

// ввод/вывод

    istream &operator>>(istream &istr, TBitField &bf) { // ввод
  // формат данных - последовательность из 0 и 1 без пробелов
  // начальные пробелы игнорируются
  // при получении не 0 или 1 - завершение ввода
  int i=0; char ch;
  // поиск {
  do { istr >> ch; } while (ch != ' ');
  // ввод элементов и включение в множество
  while (1) { istr >> ch;
    if ( ch == '0' ) bf.ClrBit(i++);
    else if ( ch == '1' ) bf.SetBit(i++); else break;
  }
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++) 
    {
        ostr << bf.GetBit(i);
    }
    return ostr;
}
