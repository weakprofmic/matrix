#include <exception>
#include <string>
#include <cstdio>
#include <sstream>
#include <iostream>

class NotImplementedException : public std::exception
{
public:
  NotImplementedException(char const *message = "Function not yet implemented") : error_message(message)
  {
  }

  /** Constructor which demands caller name */
  NotImplementedException(char const *function, char const *message)
  {
    std::ostringstream oss;
    oss << "Function not yet implemented" << " : " << function << std::endl
        << message;
    error_message = oss.str();

    /* error_message = std::string(message);
    error_message += " : ";
    error_message += function; */
  }

  virtual char const *what() const noexcept
  {
    return error_message.c_str();
  }

private:
  std::string error_message;
};
