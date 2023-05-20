#include "error_handler.h"

void Lox::report (int line, const std::string& where, const std::string& message)
{
  std::cerr << "[L[i]ne: " << line << "] - err[o]r " << where << " : " << message;
  hadError = true;
}

void Lox::error (int line, const std::string& message)
{
  report(line, "", message);
}
