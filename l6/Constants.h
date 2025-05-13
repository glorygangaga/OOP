#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <unordered_map>

const std::string HTTP_STRING = "http";
const std::string HTTPS_STRING = "https";

const char COLON = ':';
const char DOT = '.';
const std::string PROTOCOL_SPASH = "://";

const std::string PRINT_URL = "Url: ";
const std::string PRINT_DOMAIN = "Domain: ";
const std::string PRINT_DOCUMENT = "Document: ";
const std::string PRINT_PROTOCOL = "Protocol: ";
const std::string PRINT_PORT = "Port: ";

const std::string EMPTY_STRING = "";

const int MIN_PORT_NUMBER = 1;
const int MAX_PORT_NUMBER = 65535;

const std::string INVALID_INPUT = "Invalid input";
const std::string ERROR_PARSER = "(URL parser error) ";
const std::string ERROR_APPLICATION = "(Application parser error) ";
const std::string ERROR_INVALID_ARGUMENT = "(Application inavlid argument error) ";
const std::string PORT_GET_OUT_OF_RANGE = "Invalid port: Port get out of range: min (" + std::to_string(MIN_PORT_NUMBER) + "), max: (" + std::to_string(MAX_PORT_NUMBER) + ')';
const std::string INVALID_PORT_CHAR = "Invalid port: port need to be number";
const std::string CANT_READ_DOMAIN = "Invalid domain: Can't read domain from string";
const std::string INVALID_SYNTAX_DOT = "Invalid domain: Can't find dot in domain";
const std::string CANT_READ_PROTOCOL = "Invalid protocol: Can't read protocol from string";
const std::string INVALID_PROTOCOL = "Invalid protocol: Can't find valid protocol";
const std::string INVALID_SYNTAX_BETWEEN_PR_DOM = "Invalid syntax: Can't find '://' between protocol and domain";

const char SLASH = '/';
const short SLASH_COUNT = 2;

const unsigned short HTTP_DEFAULT_PORT = 80;
const unsigned short HTTPS_DEFAULT_PORT = 443;

enum class Protocol
{
  HTTP,
  HTTPS
};

const std::unordered_map<Protocol, std::string> PROTOCOLS = {
    {Protocol::HTTP, HTTP_STRING},
    {Protocol::HTTPS, HTTPS_STRING}};

struct SHttpUrl
{
  Protocol protocol;
  std::string domain, document;
  unsigned short port;
};

#endif