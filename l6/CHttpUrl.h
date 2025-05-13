#ifndef CHTTPURL_H
#define CHTTPURL_H

#include <sstream>
#include <iostream>
#include <algorithm>
#include "CUrlParsingError.h"

class CHttpUrl
{
public:
  // выполняет парсинг строкового представления URL-а, в случае ошибки парсинга
  // выбрасывает исключение CUrlParsingError, содержащее текстовое описание ошибки
  CHttpUrl(std::string const &url);

  /* инициализирует URL на основе переданных параметров.
      При недопустимости входных параметров выбрасывает исключение
      std::invalid_argument
      Если имя документа не начинается с символа /, то добавляет / к имени документа
  */
  CHttpUrl(
      std::string const &domain,
      std::string const &document,
      Protocol protocol) : m_protocol(protocol), m_document(document), m_port(GetDefaultPort(protocol)), m_domain(GetValidDomain(domain)) {};

  /* инициализирует URL на основе переданных параметров.
      При недопустимости входных параметров выбрасывает исключение
      std::invalid_argument
      Если имя документа не начинается с символа /, то добавляет / к имени документа
  */
  CHttpUrl(
      std::string const &domain,
      std::string const &document,
      Protocol protocol,
      unsigned short port) : m_port(port), m_protocol(protocol), m_document(document), m_domain(GetValidDomain(domain)) {};

  // возвращает строковое представление URL-а. Порт, являющийся стандартным для
  // выбранного протокола (80 для http и 443 для https) в эту строку
  // не должен включаться
  std::string GetURL() const;

  // возвращает доменное имя
  std::string GetDomain() const noexcept;

  /*
      Возвращает имя документа. Примеры:
          /
          /index.html
          /images/photo.jpg
  */
  std::string GetDocument() const noexcept;

  // возвращает тип протокола
  Protocol GetProtocol() const noexcept;

  // возвращает номер порта
  unsigned short GetPort() const noexcept;
  std::string ToString() const;

private:
  unsigned short m_port;
  std::string m_domain;
  Protocol m_protocol;
  std::string m_document;

  std::string ToLowerCase(const std::string &str) const;
  std::string ProtocolToString() const;
  unsigned short GetDefaultPort(const Protocol &protocol) const noexcept;

  bool ParseUrl(std::istringstream &iss, SHttpUrl &httpElems) const;
  std::optional<unsigned short> ParsePort(std::istringstream &iss) const;
  std::string ParseDomain(std::istringstream &iss) const;
  Protocol ParseProtocol(std::istringstream &iss) const;
  std::string ParseDocument(std::istringstream &iss) const;

  std::optional<Protocol> GetProtocolByString(const std::string &str) const;

  std::string GetValidDomain(const std::string &domain) const;
};

#endif