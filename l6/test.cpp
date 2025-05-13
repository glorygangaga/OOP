#include <gtest/gtest.h>
#include <sstream>
#include "app.h"
#include "Constants.h"

const std::string GetResult(const std::string &str)
{
  std::istringstream input(str);
  std::ostringstream output;

  Application app(input, output);
  app.Start();

  return output.str();
}

const std::string GetInvalidResult(const std::string &str)
{
  std::istringstream input(str);
  std::ostringstream output;

  Application app(input, output);

  std::streambuf *oldCerr = std::cerr.rdbuf();
  std::ostringstream errStream;

  std::cerr.rdbuf(errStream.rdbuf());
  app.Start();
  std::cerr.rdbuf(oldCerr);

  return errStream.str();
}

TEST(ApplicationTest, InvalidUrlFallsBackToDirectParse)
{
  const std::string result = GetResult("https://example.com/docs");
  EXPECT_NE(result.find("Url: https://example.com/docs"), std::string::npos);
}

TEST(ApplicationTest, InvalidUrlFallsBackToDirectParseWithPort)
{
  const std::string result = GetResult("https://example.com/docs:423");
  EXPECT_NE(result.find("Url: https://example.com/docs:423"), std::string::npos);
  EXPECT_NE(result.find("Port: 423"), std::string::npos);
}

TEST(ApplicationTest, EmptyString)
{
  const std::string errors = GetInvalidResult("\n");
  EXPECT_NE(errors.find(INVALID_INPUT), std::string::npos);
  EXPECT_NE(errors.find(ERROR_PARSER), std::string::npos);
}

TEST(ApplicationTest, PortOutOfRange)
{
  const std::string errors = GetInvalidResult("https://site.com/:423523");
  EXPECT_NE(errors.find(PORT_GET_OUT_OF_RANGE), std::string::npos);
  EXPECT_NE(errors.find(ERROR_PARSER), std::string::npos);
}

TEST(ApplicationTest, InvalidPort)
{
  const std::string errors = GetInvalidResult("https://site.com/:ferge");
  EXPECT_NE(errors.find(INVALID_PORT_CHAR), std::string::npos);
  EXPECT_NE(errors.find(ERROR_PARSER), std::string::npos);
}

TEST(ApplicationTest, InvalidDomain)
{
  const std::string errors = GetInvalidResult("https:///");
  EXPECT_NE(errors.find(CANT_READ_DOMAIN), std::string::npos);
  EXPECT_NE(errors.find(ERROR_PARSER), std::string::npos);
}

TEST(ApplicationTest, InvalidDomainSyntaxDot)
{
  const std::string errors = GetInvalidResult("https://sreijgjs/");
  EXPECT_NE(errors.find(INVALID_SYNTAX_DOT), std::string::npos);
  EXPECT_NE(errors.find(ERROR_INVALID_ARGUMENT), std::string::npos);
}

TEST(ApplicationTest, InvalidProtocol)
{
  const std::string errors = GetInvalidResult("httpo//site.com/");
  EXPECT_NE(errors.find(INVALID_PROTOCOL), std::string::npos);
  EXPECT_NE(errors.find(ERROR_PARSER), std::string::npos);
}

TEST(ApplicationTest, InvalidProtocolText)
{
  const std::string errors = GetInvalidResult("://site.com/");
  EXPECT_NE(errors.find(CANT_READ_PROTOCOL), std::string::npos);
  EXPECT_NE(errors.find(ERROR_PARSER), std::string::npos);
}

TEST(ApplicationTest, InvalidSyntaxUrl)
{
  const std::string errors = GetInvalidResult("https:/site.com/");
  EXPECT_NE(errors.find(INVALID_SYNTAX_BETWEEN_PR_DOM), std::string::npos);
  EXPECT_NE(errors.find(ERROR_PARSER), std::string::npos);
}
