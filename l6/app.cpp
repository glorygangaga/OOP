#include "app.h"
#include "CHttpUrl.h"

bool Application::Start()
{
  std::string url;
  while (std::getline(m_input, url))
  {
    try
    {
      CHttpUrl urlParser(url);
      m_output << urlParser.ToString() << '\n';
    }
    catch (const CUrlParsingError &e)
    {
      std::cerr << ERROR_PARSER << e.what() << '\n';
    }
    catch (const std::invalid_argument &e)
    {
      std::cerr << ERROR_INVALID_ARGUMENT << e.what() << '\n';
    }
    catch (const std::exception &e)
    {
      std::cerr << ERROR_APPLICATION << e.what() << '\n';
    }
  }

  return true;
}
