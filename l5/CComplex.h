#ifndef CCOMPLEX_H
#define CCOMPLEX_H

#include <iostream>
#include <cmath>
#include <cfloat>
#include "constants.h"

class CComplex
{
public:
  // инициализация комплексного числа значениями действительной и мнимой частей
  CComplex(double real = 0, double image = 0) : m_real(real), m_image(image) {};

  // возвращает действительную часть комплексного числа
  double Re() const;

  // возвращает мнимую часть комплексного числа
  double Im() const;

  // возвращает модуль комплексного числа
  double GetMagnitude() const;

  // возвращает аргумент комплексного числа
  double GetArgument() const;

  bool Re(const double real);
  bool Im(const double image);

  CComplex operator+(const CComplex &complex) const;
  CComplex operator+() const;
  CComplex operator-(const CComplex &complex) const;
  CComplex operator-() const;
  CComplex operator*(const CComplex &complex) const;
  CComplex operator*(const double real) const;
  CComplex operator/(const CComplex &complex) const;
  CComplex operator/(const double real) const;

  CComplex &operator+=(const CComplex &complex);
  CComplex &operator-=(const CComplex &complex);
  CComplex &operator*=(const CComplex &complex);
  CComplex &operator/=(const CComplex &complex);

  bool operator==(const CComplex &complex) const;
  bool operator!=(const CComplex &complex) const;
  bool operator==(const double real) const;
  bool operator!=(const double real) const;

  friend std::ostream &operator<<(std::ostream &os, const CComplex &complex);
  friend std::istream &operator>>(std::istream &os, CComplex &complex);

private:
  double m_real, m_image;
};

#endif