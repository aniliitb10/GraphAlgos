#pragma once

#include <string>

class Exception : public std::exception
{
public:
  explicit Exception(std::string msg_):
  _msg(std::move(msg_)){}

  ~Exception() override = default;
  const char *what() const noexcept override
  {
    return _msg.data();
  }

private:
  std::string _msg;
};

class InvalidInputException : public Exception
{
public:
  explicit InvalidInputException(std::string msg_):
    Exception(std::move(msg_)){}
};