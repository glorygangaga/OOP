#include "CHttpUrl.h"

CHttpUrl::CHttpUrl(std::string const &url)
    : CHttpUrl([&]() -> CHttpUrl
               {
  if (url.empty())
    throw CUrlParsingError(INVALID_INPUT);
  std::istringstream iss(url);
  SHttpUrl httpElems;

  bool hasPort = ParseUrl(iss, httpElems);
  auto [protocol, domain, document, port] = httpElems;

  if (hasPort)
      return CHttpUrl(domain, document, protocol, port);
  return CHttpUrl(domain, document, protocol); }()) {};

std::string CHttpUrl::GetURL() const
{
  std::string port;
  if (GetDefaultPort(GetProtocol()) != GetPort())
    port += COLON + std::to_string(GetPort());

  return ProtocolToString() + PROTOCOL_SPASH + GetDomain() + GetDocument() + port;
}

std::string CHttpUrl::GetDomain() const noexcept
{
  return m_domain;
}

std::string CHttpUrl::GetDocument() const noexcept
{
  return m_document;
}

Protocol CHttpUrl::GetProtocol() const noexcept
{
  return m_protocol;
}

unsigned short CHttpUrl::GetPort() const noexcept
{
  return m_port;
}

std::string CHttpUrl::ToLowerCase(const std::string &str) const
{
  std::string lowerStr;
  lowerStr.reserve(str.size());

  for (const unsigned char ch : str)
    lowerStr += std::tolower(ch);
  return lowerStr;
}

std::string CHttpUrl::ToString() const
{
  const std::string url = PRINT_URL + GetURL() + '\n';
  const std::string domain = PRINT_DOMAIN + GetDomain() + '\n';
  const std::string document = PRINT_DOCUMENT + GetDocument() + '\n';
  const std::string protocol = PRINT_PROTOCOL + ProtocolToString() + '\n';
  const std::string port = PRINT_PORT + std::to_string(GetPort());
  return url + protocol + domain + document + port;
}

std::string CHttpUrl::ProtocolToString() const
{
  auto it = PROTOCOLS.find(GetProtocol());
  if (it == PROTOCOLS.end())
    return EMPTY_STRING;
  return it->second;
}

unsigned short CHttpUrl::GetDefaultPort(const Protocol &protocol) const noexcept
{
  switch (protocol)
  {
  case Protocol::HTTPS:
    return HTTPS_DEFAULT_PORT;
  default:
    return HTTP_DEFAULT_PORT;
  }
}

bool CHttpUrl::ParseUrl(std::istringstream &iss, SHttpUrl &httpElems) const
{
  httpElems.protocol = ParseProtocol(iss);
  httpElems.domain = ParseDomain(iss);
  httpElems.document = ParseDocument(iss);
  auto port = ParsePort(iss);

  if (port.has_value())
  {
    httpElems.port = port.value();
    return true;
  }
  return false;
}

std::optional<unsigned short> CHttpUrl::ParsePort(std::istringstream &iss) const
{
  std::string str;
  char ch;
  while (iss >> ch)
  {
    if (std::isdigit(ch))
      str += ch;
    else
      throw CUrlParsingError(INVALID_PORT_CHAR);
  }

  if (!str.empty())
  {
    int port = std::stoi(str);
    if (port < MIN_PORT_NUMBER || port > MAX_PORT_NUMBER)
      throw CUrlParsingError(PORT_GET_OUT_OF_RANGE);
    return static_cast<unsigned short>(port);
  }
  else
    return std::nullopt;
}

std::string CHttpUrl::ParseDomain(std::istringstream &iss) const
{
  std::string str;
  getline(iss, str, SLASH);
  if (str.empty())
    throw CUrlParsingError(CANT_READ_DOMAIN);

  return str;
}

Protocol CHttpUrl::ParseProtocol(std::istringstream &iss) const
{
  std::string str;
  Protocol protocolValue;
  getline(iss, str, COLON);
  if (str.empty())
    throw CUrlParsingError(CANT_READ_PROTOCOL);

  auto protocol = GetProtocolByString(str);
  if (protocol.has_value())
    protocolValue = protocol.value();
  else
    throw CUrlParsingError(INVALID_PROTOCOL);

  char slashes[SLASH_COUNT] = {};
  iss.read(slashes, SLASH_COUNT);
  if (slashes[0] != SLASH || slashes[1] != SLASH)
    throw CUrlParsingError(INVALID_SYNTAX_BETWEEN_PR_DOM);

  return protocolValue;
}

std::string CHttpUrl::ParseDocument(std::istringstream &iss) const
{
  std::string str;
  char ch;
  while (iss >> ch && ch != COLON)
    str += ch;

  return SLASH + str;
}

std::optional<Protocol> CHttpUrl::GetProtocolByString(const std::string &str) const
{
  const std::string lowerStr = ToLowerCase(str);

  const auto it = std::find_if(PROTOCOLS.begin(), PROTOCOLS.end(), [&lowerStr](const std::pair<Protocol, std::string> &pair)
                               { return pair.second == lowerStr; });

  if (it != PROTOCOLS.end())
    return it->first;
  return std::nullopt;
}

std::string CHttpUrl::GetValidDomain(const std::string &domain) const
{
  if (domain.find(DOT) == std::string::npos)
    throw std::invalid_argument(INVALID_SYNTAX_DOT);

  return domain;
}
