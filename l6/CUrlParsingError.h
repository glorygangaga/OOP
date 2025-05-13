#ifndef CURLPARSINGERROR_H
#define CURLPARSINGERROR_H

#include <stdexcept>
#include "Constants.h"

class CUrlParsingError : public std::invalid_argument
{
public:
  CUrlParsingError(const std::string &errorMessage) : std::invalid_argument(errorMessage) {};
};

#endif