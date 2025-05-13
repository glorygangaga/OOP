#include <gtest/gtest.h>
#include "CComplex.h"
#include <sstream>

TEST(CComplexTest, GettersWorkCorrectly)
{
  CComplex c(3.0, 4.0);
  EXPECT_DOUBLE_EQ(c.Re(), 3.0);
  EXPECT_DOUBLE_EQ(c.Im(), 4.0);
}

TEST(CComplexTest, SettersWorkCorrectly)
{
  CComplex c;
  EXPECT_TRUE(c.Re(5.0));
  EXPECT_TRUE(c.Im(-2.0));
  EXPECT_DOUBLE_EQ(c.Re(), 5.0);
  EXPECT_DOUBLE_EQ(c.Im(), -2.0);
}

TEST(CComplexTest, GetMagnitudeReturnsCorrectValue)
{
  CComplex c(3.0, 4.0);
  EXPECT_DOUBLE_EQ(c.GetMagnitude(), 5.0);
}

TEST(CComplexTest, GetArgumentReturnsCorrectValue)
{
  CComplex c(0.0, 1.0);
  EXPECT_NEAR(c.GetArgument(), M_PI_2, 1e-10);
}

TEST(CComplexTest, AdditionWorksCorrectly)
{
  CComplex a(1, 2), b(3, 4);
  CComplex result = a + b;
  EXPECT_DOUBLE_EQ(result.Re(), 4.0);
  EXPECT_DOUBLE_EQ(result.Im(), 6.0);
}

TEST(CComplexTest, UnaryPlusReturnsSameValue)
{
  CComplex c(1, -2);
  CComplex result = +c;
  EXPECT_DOUBLE_EQ(result.Re(), 1.0);
  EXPECT_DOUBLE_EQ(result.Im(), -2.0);
}

TEST(CComplexTest, SubtractionWorksCorrectly)
{
  CComplex a(5, 7), b(2, 3);
  CComplex result = a - b;
  EXPECT_DOUBLE_EQ(result.Re(), 3.0);
  EXPECT_DOUBLE_EQ(result.Im(), 4.0);
}

TEST(CComplexTest, UnaryMinusInvertsSigns)
{
  CComplex c(1, -2);
  CComplex result = -c;
  EXPECT_DOUBLE_EQ(result.Re(), -1.0);
  EXPECT_DOUBLE_EQ(result.Im(), 2.0);
}

TEST(CComplexTest, MultiplicationWithComplexWorksCorrectly)
{
  CComplex a(1, 2), b(3, 4);
  CComplex result = a * b;
  EXPECT_DOUBLE_EQ(result.Re(), -5.0);
  EXPECT_DOUBLE_EQ(result.Im(), 10.0);
}

TEST(CComplexTest, MultiplicationWithDoubleWorksCorrectly)
{
  CComplex c(2, -3);
  CComplex result = c * 2.0;
  EXPECT_DOUBLE_EQ(result.Re(), 4.0);
  EXPECT_DOUBLE_EQ(result.Im(), -6.0);
}

TEST(CComplexTest, DivisionWithComplexWorksCorrectly)
{
  CComplex a(1, 2), b(3, 4);
  CComplex result = a / b;
  EXPECT_NEAR(result.Re(), 0.44, 0.01);
  EXPECT_NEAR(result.Im(), 0.08, 0.01);
}

TEST(CComplexTest, DivisionWithDoubleWorksCorrectly)
{
  CComplex c(4, 6);
  CComplex result = c / 2.0;
  EXPECT_DOUBLE_EQ(result.Re(), 2.0);
  EXPECT_DOUBLE_EQ(result.Im(), 3.0);
}

TEST(CComplexTest, DivisionByZeroComplexThrows)
{
  CComplex a(1, 1), zero(0, 0);
  EXPECT_THROW(a / zero, std::invalid_argument);
}

TEST(CComplexTest, DivisionByZeroDoubleThrows)
{
  CComplex c(1, 1);
  EXPECT_THROW(c / 0.0, std::invalid_argument);
}

TEST(CComplexTest, CompoundAdditionWorksCorrectly)
{
  CComplex a(1, 2), b(3, 4);
  a += b;
  EXPECT_DOUBLE_EQ(a.Re(), 4.0);
  EXPECT_DOUBLE_EQ(a.Im(), 6.0);
}

TEST(CComplexTest, CompoundSubtractionWorksCorrectly)
{
  CComplex a(5, 6), b(2, 1);
  a -= b;
  EXPECT_DOUBLE_EQ(a.Re(), 3.0);
  EXPECT_DOUBLE_EQ(a.Im(), 5.0);
}

TEST(CComplexTest, CompoundMultiplicationWorksCorrectly)
{
  CComplex a(1, 2), b(3, 4);
  a *= b;
  EXPECT_DOUBLE_EQ(a.Re(), -5.0);
  EXPECT_DOUBLE_EQ(a.Im(), 10.0);
}

TEST(CComplexTest, CompoundDivisionWorksCorrectly)
{
  CComplex a(1, 2), b(3, 4);
  a /= b;
  EXPECT_NEAR(a.Re(), 0.44, 0.01);
  EXPECT_NEAR(a.Im(), 0.08, 0.01);
}

TEST(CComplexTest, CompoundDivisionByZeroThrows)
{
  CComplex a(1, 1), b(0, 0);
  EXPECT_THROW(a /= b, std::invalid_argument);
}

TEST(CComplexTest, ComparisonWithDoubleWorksCorrectly)
{
  CComplex c(3.0, 0.0);
  EXPECT_TRUE(c == 3.0);
  EXPECT_FALSE(c != 3.0);
}

TEST(CComplexTest, ComparisonWithComplexWorksCorrectly)
{
  CComplex a(2.0, 3.0), b(2.0, 3.0), c(2.1, 3.0);
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a == c);
  EXPECT_TRUE(a != c);
}

TEST(CComplexTest, OutputOperatorFormatsCorrectly)
{
  CComplex c(1.5, -2.3);
  std::ostringstream oss;
  oss << c;
  EXPECT_EQ(oss.str(), "1.5-2.3i");
}

TEST(CComplexTest, InputOperatorParsesCorrectly)
{
  CComplex c;
  std::istringstream iss("3.2+4.1i");
  iss >> c;
  EXPECT_DOUBLE_EQ(c.Re(), 3.2);
  EXPECT_DOUBLE_EQ(c.Im(), 4.1);
}

TEST(CComplexTest, InputOperatorParsesRealOnly)
{
  CComplex c;
  std::istringstream iss("3.5");
  iss >> c;
  EXPECT_DOUBLE_EQ(c.Re(), 3.5);
  EXPECT_DOUBLE_EQ(c.Im(), 0.0);
}

TEST(CComplexTest, InputOperatorInvalidInputFails)
{
  CComplex c;
  std::istringstream iss("3.5#2.1i");
  iss >> c;
  EXPECT_TRUE(iss.fail());
}
