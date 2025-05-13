#include "CComplex.h"

double CComplex::Re() const
{
  return m_real;
}

bool CComplex::Re(const double real)
{
  m_real = real;
  return true;
}

double CComplex::Im() const
{
  return m_image;
}

bool CComplex::Im(const double image)
{
  m_image = image;
  return true;
}

double CComplex::GetMagnitude() const
{
  return std::sqrt(std::pow(Re(), DEGREE) + std::pow(Im(), DEGREE));
}

double CComplex::GetArgument() const
{
  return std::atan2(Im(), Re());
}

CComplex CComplex::operator+(const CComplex &complex) const
{
  return CComplex(Re() + complex.Re(), Im() + complex.Im());
}

CComplex CComplex::operator+() const
{
  return *this;
}

CComplex CComplex::operator-(const CComplex &complex) const
{
  return CComplex(Re() - complex.Re(), Im() - complex.Im());
}

CComplex CComplex::operator-() const
{
  return CComplex(-Re(), -Im());
}

CComplex CComplex::operator*(const CComplex &complex) const
{
  double real = complex.Re() * Re() - complex.Im() * Im();
  double image = Re() * complex.Im() + complex.Re() * Im();
  return CComplex(real, image);
}

CComplex CComplex::operator*(const double real) const
{
  return CComplex(Re() * real, Im() * real);
}

CComplex CComplex::operator/(const CComplex &complex) const
{
  double denominator = std::pow(complex.Re(), DEGREE) + std::pow(complex.Im(), DEGREE);
  if (denominator == 0)
    throw std::invalid_argument(ERROR_DENOMINATOR_ZERO_VAL);
  double real = (Re() * complex.Re() + Im() * complex.Im()) / denominator;
  double image = (Im() * complex.Re() - Re() * complex.Im()) / denominator;
  return CComplex(real, image);
}

CComplex CComplex::operator/(const double real) const
{
  if (real == 0)
    throw std::invalid_argument(ERROR_REAL_ZERO_VAL);
  return CComplex(Re() / real, Im() / real);
}

CComplex &CComplex::operator+=(const CComplex &complex)
{
  m_real += complex.Re();
  m_image += complex.Im();
  return *this;
}

CComplex &CComplex::operator-=(const CComplex &complex)
{
  m_real -= complex.Re();
  m_image -= complex.Im();
  return *this;
}

CComplex &CComplex::operator*=(const CComplex &complex)
{
  *this = *this * complex;
  return *this;
}

CComplex &CComplex::operator/=(const CComplex &complex)
{
  if (complex.Re() == 0 && complex.Im() == 0)
    throw std::invalid_argument(ERROR_COMPLEX_ZERO_VAL);
  *this = *this / complex;
  return *this;
}

bool CComplex::operator==(const double real) const
{
  return (std::fabs(Re() - real) < DBL_EPSILON) && (std::fabs(Im()) < DBL_EPSILON);
}

bool CComplex::operator!=(const double real) const
{
  return !(*this == real);
}

bool CComplex::operator==(const CComplex &complex) const
{
  return (std::fabs(Re() - complex.Re()) < DBL_EPSILON) && (std::fabs(Im() - complex.Im()) < DBL_EPSILON);
}

bool CComplex::operator!=(const CComplex &complex) const
{
  return !(*this == complex);
}

std::ostream &operator<<(std::ostream &os, const CComplex &complex)
{
  os << complex.Re() << (complex.Im() >= 0 ? PLUS_SIGN : EMPTY_SIGN) << complex.Im() << IM_SIGN;
  return os;
}

std::istream &operator>>(std::istream &is, CComplex &complex)
{
  char ch, sign;
  double real, image;

  is >> real >> sign;
  if (!sign)
  {
    complex.Re(real);
    complex.Im(0);
    return is;
  }

  if (sign != MINUS_SIGN_CHAR && sign != PLUS_SIGN_CHAR)
  {
    is.setstate(std::ios::failbit);
    return is;
  }

  is >> image >> ch;
  if (ch != IM_SIGN)
  {
    is.setstate(std::ios::failbit);
    return is;
  }

  complex.Re(real);
  complex.Im(sign == PLUS_SIGN_CHAR ? image : -image);

  return is;
}
